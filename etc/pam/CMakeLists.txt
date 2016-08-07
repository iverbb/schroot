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

if(BUILD_PAM)
  set(pam_data "${CMAKE_CURRENT_BINARY_DIR}/schroot")
  set(pam_dir "/etc/pam.d")

  if(PAM_TYPE STREQUAL "Linux-PAM")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/schroot-debian"
                   "${pam_data}"
                   COPYONLY)
  elseif(PAM_TYPE STREQUAL "OpenPAM")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/schroot-freebsd"
                   "${pam_data}"
                   COPYONLY)
    # For ports, we can use /usr/local/etc/pam.d.
    if(CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
      set(pam_dir "/usr/local/etc/pam.d")
    endif()
  else()
    message(FATAL_ERROR "Invalid PAM type \"${PAM_TYPE}\"")
  endif()

  install(FILES ${pam_data}
        DESTINATION ${pam_dir})
endif()
