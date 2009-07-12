/* Copyright © 2006-2008  Roger Leigh <rleigh@debian.org>
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

#include <sbuild/sbuild-chroot-file.h>

#include "test-helpers.h"
#include "test-sbuild-chroot.h"

#include <algorithm>
#include <set>

#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class chroot_file : public sbuild::chroot_file
{
public:
  chroot_file():
    sbuild::chroot_file()
  {}

  virtual ~chroot_file()
  {}
};

class test_chroot_file : public test_chroot_base<chroot_file>
{
  CPPUNIT_TEST_SUITE(test_chroot_file);
  CPPUNIT_TEST(test_file);
  CPPUNIT_TEST(test_chroot_type);
  CPPUNIT_TEST(test_setup_env);
  CPPUNIT_TEST(test_setup_env_source);
  CPPUNIT_TEST(test_session_flags);
  CPPUNIT_TEST(test_print_details);
  CPPUNIT_TEST(test_print_config);
  CPPUNIT_TEST_SUITE_END();

public:
  test_chroot_file():
    test_chroot_base<chroot_file>()
  {}

  void setUp()
  {
    test_chroot_base<chroot_file>::setUp();
    std::tr1::shared_ptr<sbuild::chroot_file> c = std::tr1::dynamic_pointer_cast<sbuild::chroot_file>(chroot);
    c->set_file("/srv/chroot/example.tar.bz2");
  }

  void
  test_file()
  {
    std::tr1::shared_ptr<sbuild::chroot_file> c = std::tr1::dynamic_pointer_cast<sbuild::chroot_file>(chroot);
    CPPUNIT_ASSERT(c);
    c->set_file("/srv/chroot-images/unstable.tar.gz");
    CPPUNIT_ASSERT(c->get_file() == "/srv/chroot-images/unstable.tar.gz");
  }

  void test_chroot_type()
  {
    CPPUNIT_ASSERT(chroot->get_chroot_type() == "file");
  }

  void test_setup_env()
  {
    sbuild::environment expected;
    setup_env_chroot(expected);
    expected.add("CHROOT_TYPE",            "file");
    expected.add("CHROOT_FILE",            "/srv/chroot/example.tar.bz2");
    expected.add("CHROOT_FILE_REPACK",     "false");
    expected.add("CHROOT_FILE_UNPACK_DIR", SCHROOT_FILE_UNPACK_DIR);
    expected.add("CHROOT_MOUNT_LOCATION",  "/mnt/mount-location");
    expected.add("CHROOT_PATH",            "/mnt/mount-location");
    expected.add("CHROOT_SESSION_CLONE",   "true");
    expected.add("CHROOT_SESSION_CREATE",  "true");
    expected.add("CHROOT_SESSION_PURGE",   "false");

    test_chroot_base<chroot_file>::test_setup_env(expected);
  }

  void test_setup_env_source()
  {
    std::tr1::shared_ptr<sbuild::chroot_file> c = std::tr1::dynamic_pointer_cast<sbuild::chroot_file>(chroot);

    std::tr1::shared_ptr<sbuild::chroot_source> cs =
      std::tr1::dynamic_pointer_cast<sbuild::chroot_source>(chroot);

    CPPUNIT_ASSERT(c->get_source_clonable() == true);

    sbuild::chroot::ptr source = cs->clone_source();
    std::tr1::shared_ptr<sbuild::chroot_source> s =
      std::tr1::dynamic_pointer_cast<sbuild::chroot_source>(source);

    CPPUNIT_ASSERT(s->get_source_clonable() == false);

    sbuild::environment expected;
    setup_env_chroot(expected);
    expected.add("CHROOT_TYPE",           "file");
    expected.add("CHROOT_NAME",           "test-name-source");
    expected.add("CHROOT_DESCRIPTION",    "test-description (source chroot)");
    expected.add("CHROOT_FILE",            "/srv/chroot/example.tar.bz2");
    expected.add("CHROOT_FILE_REPACK",     "true");
    expected.add("CHROOT_FILE_UNPACK_DIR", SCHROOT_FILE_UNPACK_DIR);
    expected.add("CHROOT_MOUNT_LOCATION",  "/mnt/mount-location");
    expected.add("CHROOT_PATH",            "/mnt/mount-location");
    expected.add("CHROOT_SESSION_CLONE",  "false");
    expected.add("CHROOT_SESSION_CREATE", "true");
    expected.add("CHROOT_SESSION_PURGE",  "false");

    sbuild::environment observed;
    source->setup_env(observed);

    test_chroot_base<chroot_file>::test_setup_env(observed, expected);
  }

  void test_session_flags()
  {
    CPPUNIT_ASSERT(chroot->get_session_flags() ==
		   (sbuild::chroot::SESSION_CREATE |
		    sbuild::chroot::SESSION_CLONE));
  }

  void test_print_details()
  {
    std::ostringstream os;
    os << chroot;
    // TODO: Compare output.
    CPPUNIT_ASSERT(!os.str().empty());
  }

  void test_print_config()
  {
    std::ostringstream os;
    sbuild::keyfile config;
    config << chroot;
    os << config;
    // TODO: Compare output.
    CPPUNIT_ASSERT(!os.str().empty());
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_chroot_file);
