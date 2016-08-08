# Copyright © 2004-2013  Roger Leigh <rleigh@codelibre.net>
#
# schroot is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# schroot is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see
# <http://www.gnu.org/licenses/>.
#
#####################################################################

include_directories(${GTEST_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/bin)

if(BUILD_BTRFSSNAP)
  set(btrfssnap_sources
      btrfs-snapshot.cc)
endif(BUILD_BTRFSSNAP)

set(chroot_sources
    chroot.h
    chroot.cc
    custom.cc
    file.cc
    directory.cc
    ${btrfssnap_sources}
    facet/userdata.cc)

if (BUILD_TESTS)
  add_executable(chroot ${chroot_sources})
  target_link_libraries(chroot
                        libschroot
                        testmain
                        ${REGEX_LIBRARY}
                        ${Intl_LIBRARIES})
  add_test(schroot/chroot/chroot chroot)
endif (BUILD_TESTS)

set(config_sources
    config.cc)

if (BUILD_TESTS)
  add_executable(config ${config_sources})
  target_link_libraries(config libschroot testmain ${Intl_LIBRARIES})
  add_test(schroot/chroot/config config)
endif (BUILD_TESTS)
