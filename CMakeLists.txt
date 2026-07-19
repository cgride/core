cmake_minimum_required(VERSION 3.22)

project(
  cgride-core
  VERSION 0.1.1
  DESCRIPTION "Core types, results, errors, events, paths and utilities for Cgride."
  HOMEPAGE_URL "https://github.com/cgride/core"
  LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(CGRIDE_CORE_BUILD_TESTS "Build Cgride core tests" ON)
option(CGRIDE_CORE_INSTALL "Install Cgride core" ON)

add_library(cgride_core
  src/error.cpp
  src/diagnostic.cpp
  src/event.cpp
  src/command.cpp
  src/platform.cpp
  src/path.cpp
  src/hash.cpp
  src/cancellation.cpp
)

add_library(cgride::core ALIAS cgride_core)

target_compile_features(cgride_core
  PUBLIC
    cxx_std_23
)

target_include_directories(cgride_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(cgride_core
  PROPERTIES
    OUTPUT_NAME cgride_core
    EXPORT_NAME core
    CXX_EXTENSIONS OFF
)

if(CGRIDE_CORE_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(CGRIDE_CORE_INSTALL)
  install(
    TARGETS cgride_core
    EXPORT cgride-core-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

  install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  install(
    EXPORT cgride-core-targets
    NAMESPACE cgride::
    FILE cgride-core-targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cgride-core
  )

  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cgride-core-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cgride-core-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cgride-core
  )

  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cgride-core-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/cgride-core-config.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/cgride-core-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cgride-core
  )
endif()
