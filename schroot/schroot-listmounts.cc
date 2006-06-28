/* Copyright © 2005-2006  Roger Leigh <rleigh@debian.org>
 *
 * schroot is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * schroot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA  02111-1307  USA
 *
 *********************************************************************/

#include <config.h>

#include <sbuild/sbuild-i18n.h>
#include <sbuild/sbuild-log.h>
#include <sbuild/sbuild-types.h>

#include "schroot-listmounts-options.h"
#include "schroot-listmounts-main.h"

#include <cstdlib>

#include <boost/format.hpp>
#include <boost/program_options.hpp>


using std::endl;
using boost::format;
namespace opt = boost::program_options;

using namespace schroot_listmounts;

/**
 * Main routine.
 *
 * @param argc the number of arguments
 * @param argv argument vector
 *
 * @returns 0 on success, 1 on failure or the exit status of the
 * chroot command.
 */
int
main (int   argc,
      char *argv[])
{
  try
    {
      schroot_listmounts::options::ptr opts(new schroot_listmounts::options);
      schroot_listmounts::main kit(opts);
      exit (kit.run(argc, argv));
    }
  catch (std::exception const& e)
    {
      sbuild::log_error() << e.what() << endl;
      exit(EXIT_FAILURE);
    }
  catch (...)
    {
      sbuild::log_error() << _("An unknown exception occured") << endl;
      exit(EXIT_FAILURE);
    }
}

/*
 * Local Variables:
 * mode:C++
 * End:
 */
