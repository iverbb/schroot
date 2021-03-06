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

#include <schroot/chroot/facet/storage.h>

namespace schroot
{
  namespace chroot
  {
    namespace facet
    {

      storage::storage ()
      {
      }

      storage::~storage ()
      {
      }

      void
      storage::setup_lock([[maybe_unused]] chroot::setup_type type,
                          [[maybe_unused]] bool lock,
                          [[maybe_unused]] int  status)
      {
      }

    }
  }
}
