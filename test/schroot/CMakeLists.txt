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

include_directories(${PROJECT_SOURCE_DIR}/bin)

if(BUILD_PERSONALITY)
  set(personality_sources
    personality.cc)
endif(BUILD_PERSONALITY)

set(standard_sources
    environment.cc
    log.cc
    nostream.cc
    parse-value.cc
    ${personality_sources}
    regex.cc
    util.cc)

if (BUILD_TESTS)
  add_executable(standard ${standard_sources})
  target_link_libraries(standard
                        libschroot
                        ${Boost_FILESYSTEM_LIBRARY_RELEASE}
                        ${Boost_SYSTEM_LIBRARY_RELEASE}
                        ${REGEX_LIBRARY}
                        testmain
                        ${Intl_LIBRARIES})
  add_test(schroot/standard standard)
endif (BUILD_TESTS)

set(keyfile_sources
    keyfile.cc)

if (BUILD_TESTS)
  add_executable(keyfile ${keyfile_sources})
  target_link_libraries(keyfile libschroot testmain ${Intl_LIBRARIES})
  add_test(schroot/keyfile keyfile)
endif (BUILD_TESTS)

set(lock_sources
    lock.cc)

if (BUILD_TESTS)
  add_executable(lock ${lock_sources})
  target_link_libraries(lock libschroot testmain ${Intl_LIBRARIES})
  # lock is excluded, because it is timing dependent and can fail
  # randomly on slow or heavily-loaded systems.
endif (BUILD_TESTS)

set(run_parts_sources
    run-parts.cc)

if (BUILD_TESTS)
  add_executable(run-parts ${run_parts_sources})
  target_link_libraries(run-parts
                        libschroot
                        ${Boost_FILESYSTEM_LIBRARY_RELEASE}
                        ${Boost_SYSTEM_LIBRARY_RELEASE}
                        testmain
                        ${Intl_LIBRARIES})
  add_test(schroot/run-parts run-parts)
endif (BUILD_TESTS)
