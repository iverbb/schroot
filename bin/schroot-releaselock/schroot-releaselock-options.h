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

#ifndef SCHROOT_RELEASELOCK_OPTIONS_H
#define SCHROOT_RELEASELOCK_OPTIONS_H

#include <schroot-base/schroot-base-options.h>

#include <string>

namespace schroot_releaselock
{

  /**
   * schroot-releaselock command-line options.
   */
  class options : public schroot_base::options
  {
  public:
    /// A shared_ptr to an options object.
    typedef std::shared_ptr<options> ptr;

    /// Begin, run and end a session.
    static const action_type ACTION_RELEASELOCK;

    /// The constructor.
    options ();

    /// The destructor.
    virtual ~options ();

    /// The device to unlock.
    std::string device;
    /// The PID holding the lock.
    int         pid;

  protected:
    virtual void
    add_options ();

    virtual void
    add_option_groups ();

    virtual void
    check_options ();

    /// Lock options group.
    boost::program_options::options_description lock;
  };

}

#endif /* SCHROOT_RELEASELOCK_OPTIONS_H */

/*
 * Local Variables:
 * mode:C++
 * End:
 */
