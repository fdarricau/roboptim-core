# Copyright 2010, Thomas Moulard, LAAS-CNRS
#
# This file is part of roboptim-core.
# roboptim-core is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# roboptim-core is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Lesser Public License for more details.
# You should have received a copy of the GNU Lesser General Public License
# along with roboptim-core.  If not, see <http://www.gnu.org/licenses/>.

# Add Boost path to include directories.
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# Define the directory where plug-ins will be installed.
SET(PLUGINDIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME})

# Main library.
ADD_LIBRARY(roboptim-core SHARED
  ${HEADERS}
  debug.hh
  doc.hh
  alloc.cc
  finite-difference-gradient.cc
  generic-solver.cc
  indent.cc
  result-with-warnings.cc
  result.cc
  solver-error.cc
  solver-warning.cc
  solver.cc
  util.cc

  visualization/gnuplot.cc
  visualization/gnuplot-commands.cc
  visualization/gnuplot-differentiable-function.cc
  visualization/gnuplot-matrix.cc

  visualization/matplotlib.cc
  visualization/matplotlib-commands.cc
  visualization/matplotlib-matrix.cc
  )

IF(MSVC)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBUILDING_ROBOPTIM")
  PKG_CONFIG_APPEND_CFLAGS (-DBUILDING_ROBOPTIM)
ENDIF()

PKG_CONFIG_USE_DEPENDENCY(roboptim-core eigen3)
PKG_CONFIG_USE_DEPENDENCY(roboptim-core liblog4cxx)

TARGET_LINK_LIBRARIES(roboptim-core ltdl)
SET_TARGET_PROPERTIES(roboptim-core PROPERTIES SOVERSION 3 VERSION 3.1.0)
INSTALL(TARGETS roboptim-core DESTINATION ${CMAKE_INSTALL_LIBDIR})


# Dummy plug-in.
ADD_LIBRARY(roboptim-core-plugin-dummy MODULE dummy.cc)
ADD_DEPENDENCIES(roboptim-core-plugin-dummy roboptim-core)
PKG_CONFIG_USE_DEPENDENCY(roboptim-core-plugin-dummy liblog4cxx)
TARGET_LINK_LIBRARIES(roboptim-core-plugin-dummy roboptim-core)
SET_TARGET_PROPERTIES(roboptim-core-plugin-dummy PROPERTIES PREFIX "")

IF(NOT APPLE)
  SET_TARGET_PROPERTIES(roboptim-core-plugin-dummy
    PROPERTIES VERSION 3.1.0 SOVERSION 3)
ENDIF()
INSTALL(TARGETS roboptim-core-plugin-dummy DESTINATION ${PLUGINDIR})

# Dummy-laststate plug-in.
ADD_LIBRARY(roboptim-core-plugin-dummy-laststate MODULE dummy-laststate.cc)
ADD_DEPENDENCIES(roboptim-core-plugin-dummy-laststate roboptim-core)
PKG_CONFIG_USE_DEPENDENCY(roboptim-core-plugin-dummy-laststate liblog4cxx)
TARGET_LINK_LIBRARIES(roboptim-core-plugin-dummy-laststate roboptim-core)
SET_TARGET_PROPERTIES(roboptim-core-plugin-dummy-laststate PROPERTIES PREFIX "")

IF(NOT APPLE)
  SET_TARGET_PROPERTIES(roboptim-core-plugin-dummy-laststate
    PROPERTIES VERSION 3.1.0 SOVERSION 3)
ENDIF()
INSTALL(TARGETS roboptim-core-plugin-dummy-laststate DESTINATION ${PLUGINDIR})

# Dummy-laststate plug-in for differentiable sparse functions.
ADD_LIBRARY(roboptim-core-plugin-dummy-d-sparse-laststate MODULE dummy-d-sparse-laststate.cc)
ADD_DEPENDENCIES(roboptim-core-plugin-dummy-d-sparse-laststate roboptim-core)
PKG_CONFIG_USE_DEPENDENCY(roboptim-core-plugin-dummy-d-sparse-laststate liblog4cxx)
TARGET_LINK_LIBRARIES(roboptim-core-plugin-dummy-d-sparse-laststate roboptim-core)
SET_TARGET_PROPERTIES(roboptim-core-plugin-dummy-d-sparse-laststate PROPERTIES PREFIX "")

IF(NOT APPLE)
  SET_TARGET_PROPERTIES(roboptim-core-plugin-dummy-d-sparse-laststate
    PROPERTIES VERSION 3.1.0 SOVERSION 3)
ENDIF()
INSTALL(TARGETS roboptim-core-plugin-dummy-d-sparse-laststate DESTINATION ${PLUGINDIR})

# Dummy-td plug-in.
ADD_LIBRARY(roboptim-core-plugin-dummy-td MODULE dummy-td.cc)
ADD_DEPENDENCIES(roboptim-core-plugin-dummy-td roboptim-core)
PKG_CONFIG_USE_DEPENDENCY(roboptim-core-plugin-dummy-td liblog4cxx)
TARGET_LINK_LIBRARIES(roboptim-core-plugin-dummy-td roboptim-core)
SET_TARGET_PROPERTIES(roboptim-core-plugin-dummy-td PROPERTIES PREFIX "")

IF(NOT APPLE)
  SET_TARGET_PROPERTIES(roboptim-core-plugin-dummy-td
    PROPERTIES VERSION 3.1.0 SOVERSION 3)
ENDIF()
INSTALL(TARGETS roboptim-core-plugin-dummy-td DESTINATION ${PLUGINDIR})

IF(MSVC)
  INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}.pdb" DESTINATION ${CMAKE_INSTALL_LIBDIR} CONFIGURATIONS Debug)
  INSTALL(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Debug/" DESTINATION ${PLUGINDIR} CONFIGURATIONS Debug FILES_MATCHING PATTERN "${PROJECT_NAME}-plugin*.pdb")
ENDIF()
