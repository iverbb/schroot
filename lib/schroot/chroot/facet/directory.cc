/* Copyright © 2005-2013  Roger Leigh <rleigh@codelibre.net>
 *
 * schroot is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * schroot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *********************************************************************/

#include <config.h>

#include <schroot/chroot/facet/directory.h>
#include <schroot/chroot/facet/factory.h>
#include <schroot/chroot/facet/fsunion.h>
#include <schroot/chroot/facet/session.h>
#include <schroot/chroot/facet/session-clonable.h>
#include <schroot/format-detail.h>
#include <schroot/util.h>

#include <cassert>
#include <cerrno>
#include <cstring>

#include <boost/format.hpp>

using boost::format;

namespace schroot
{
  namespace chroot
  {
    namespace facet
    {

      namespace
      {

        const factory::facet_info directory_info =
          {
            "directory",
            N_("Support for ‘directory’ chroots"),
            false,
            []() -> facet::ptr { return directory::create(); }
          };

        factory directory_register(directory_info);

      }

      directory::directory ():
        facet(),
        storage(),
        directory_()
      {
      }

      directory::~directory ()
      {
      }

      directory::directory (const directory& rhs):
        facet(rhs),
        storage(rhs),
        directory_(rhs.directory_)
      {
      }

#ifdef SCHROOT_FEATURE_BTRFSSNAP
      directory::directory (const btrfs_snapshot& rhs):
        facet(rhs),
        storage(rhs),
        directory_()
      {
        set_directory(rhs.get_source_subvolume());
      }
#endif // SCHROOT_FEATURE_BTRFSSNAP

      void
      directory::set_chroot (chroot& chroot,
                             bool    copy)
      {
        facet::set_chroot(chroot, copy);

        if (!copy && !owner->get_facet<session_clonable>())
          owner->add_facet(session_clonable::create());

#ifdef SCHROOT_FEATURE_UNION
        if (!copy && !owner->get_facet<fsunion>())
          owner->add_facet(fsunion::create());
#endif // SCHROOT_FEATURE_UNION
      }

      std::string const&
      directory::get_name () const
      {
        return directory_info.name;
      }

      directory::ptr
      directory::create ()
      {
        return ptr(new directory());
      }

#ifdef SCHROOT_FEATURE_BTRFSSNAP
      directory::ptr
      directory::create (const btrfs_snapshot& rhs)
      {
        return ptr(new directory(rhs));
      }
#endif // SCHROOT_FEATURE_BTRFSSNAP

      facet::ptr
      directory::clone () const
      {
        return ptr(new directory(*this));
      }

      std::string const&
      directory::get_directory () const
      {
        return this->directory_;
      }

      void
      directory::set_directory (const std::string& directory)
      {
        if (!is_absname(directory))
          throw chroot::error(directory, chroot::DIRECTORY_ABS);

        this->directory_ = directory;
      }

      std::string
      directory::get_path () const
      {
        return owner->get_mount_location();
      }

      void
      directory::setup_env (environment& env) const
      {
        env.add("CHROOT_DIRECTORY", get_directory());
      }

      void
      directory::setup_lock (chroot::setup_type type,
                             bool               lock,
                             int                status)
      {
        /* Create or unlink session information. */
        if ((type == chroot::SETUP_START && lock == true) ||
            (type == chroot::SETUP_STOP && lock == false && status == 0))
          {
            bool start = (type == chroot::SETUP_START);
            owner->get_facet_strict<session>()->setup_session_info(start);
          }
      }

      void
      directory::get_details (format_detail& detail) const
      {
        detail.add(_("Directory"), get_directory());
      }

      void
      directory::get_used_keys (string_list& used_keys) const
      {
        used_keys.push_back("directory");
        used_keys.push_back("location");
      }

      void
      directory::get_keyfile (keyfile& keyfile) const
      {
        keyfile::set_object_value(*this, &directory::get_directory,
                                  keyfile, owner->get_name(), "directory");
      }

      void
      directory::set_keyfile (const keyfile& keyfile)
      {
        // "directory" should be required, but we also accept "location" as
        // an alternative (but deprecated) variant.  Therefore, ensure by
        // hand that one of them is defined, but not both.

        bool directory_key = keyfile.has_key(owner->get_name(), "directory");
        bool location_key = keyfile.has_key(owner->get_name(), "location");

        keyfile::priority directory_priority = keyfile::PRIORITY_OPTIONAL;
        keyfile::priority location_priority = keyfile::PRIORITY_OBSOLETE;

        if (!directory_key && !location_key)
          throw keyfile::error(owner->get_name(), keyfile::MISSING_KEY_NL, "directory");

        // Using both keys is not allowed (which one is the correct one?),
        // so force an exception to be thrown when reading the old location
        // key.
        if (directory_key && location_key)
          location_priority = keyfile::PRIORITY_DISALLOWED;

        keyfile::get_object_value(*this, &directory::set_directory,
                                  keyfile, owner->get_name(), "directory",
                                  directory_priority);

        keyfile::get_object_value(*this, &directory::set_directory,
                                  keyfile, owner->get_name(), "location",
                                  location_priority);
      }


    }
  }
}
