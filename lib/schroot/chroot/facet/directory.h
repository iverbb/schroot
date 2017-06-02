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

#ifndef SCHROOT_CHROOT_FACET_DIRECTORY_H
#define SCHROOT_CHROOT_FACET_DIRECTORY_H

#include <schroot/config.h>
#include <schroot/chroot/facet/facet.h>
#include <schroot/chroot/facet/storage.h>

namespace schroot
{
  namespace chroot
  {
    namespace facet
    {

      /**
       * A chroot located in the filesystem.
       *
       * It runs setup scripts and can provide multiple sessions
       * using the union facet.
       */
      class directory : public facet,
                        public storage
      {
      public:
        /// Exception type.
        typedef chroot::error error;

        /// A shared_ptr to a chroot facet object.
        typedef std::shared_ptr<directory> ptr;

        /// A shared_ptr to a const chroot facet object.
        typedef std::shared_ptr<const directory> const_ptr;

      protected:
        /// The constructor.
        directory ();

        /// The copy constructor.
        directory (const directory& rhs);

        void
        set_chroot (chroot& chroot,
                    bool    copy);

        friend class chroot;

      public:
        /// The destructor.
        virtual ~directory ();

        virtual std::string const&
        get_name () const;

        /**
         * Create a chroot facet.
         *
         * @returns a shared_ptr to the new chroot facet.
         */
        static ptr
        create ();

        virtual facet::ptr
        clone () const;

        /**
         * Get the directory containing the chroot.
         *
         * @returns the location.
         */
        std::string const&
        get_directory () const;

        /**
         * Set the directory containing the chroot.
         *
         * @param directory the directory.
         */
        void
        set_directory (const std::string& directory);

        virtual std::string
        get_path () const;

        virtual void
        setup_env (environment& env) const;

      protected:
        virtual void
        setup_lock (chroot::setup_type type,
                    bool               lock,
                    int                status);

        virtual void
        get_details (format_detail& detail) const;

        virtual void
        get_used_keys (string_list& used_keys) const;

        virtual void
        get_keyfile (keyfile& keyfile) const;

        virtual void
        set_keyfile (const keyfile& keyfile);

        /// The directory to use.
        std::string directory_;
      };

    }
  }
}

#endif /* SCHROOT_CHROOT_FACET_DIRECTORY_H */

/*
 * Local Variables:
 * mode:C++
 * End:
 */
