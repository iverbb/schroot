/* Copyright © 2005-2013  Roger Leigh <rleigh@debian.org>
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

#ifndef SBUILD_CHROOT_DIRECTORY_H
#define SBUILD_CHROOT_DIRECTORY_H

#include <sbuild/config.h>
#include <sbuild/chroot/chroot.h>
#ifdef SBUILD_FEATURE_BTRFSSNAP
#include <sbuild/chroot/btrfs-snapshot.h>
#endif

namespace sbuild
{
  namespace chroot
  {

    /**
     * A chroot located in the filesystem.
     *
     * It runs setup scripts and can provide multiple sessions
     * using the union facet.
     */
    class directory : public chroot
    {
    protected:
      /// The constructor.
      directory ();

      /// The copy constructor.
      directory (const directory& rhs);

#ifdef SBUILD_FEATURE_BTRFSSNAP
      /// The copy constructor.
      directory (const btrfs_snapshot& rhs);
#endif

      friend class chroot;
#ifdef SBUILD_FEATURE_BTRFSSNAP
      friend class btrfs_snapshot;
#endif

    public:
      /// The destructor.
      virtual ~directory ();
    };

  }
}

#endif /* SBUILD_CHROOT_DIRECTORY_H */

/*
 * Local Variables:
 * mode:C++
 * End:
 */
