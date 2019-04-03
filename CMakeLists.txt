cmake_minimum_required(VERSION 3.9)

project(CommeCOM VERSION 0.1.1 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 11)

set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES
  /.git
  /dist
  /.*build.*
  /\\\\.DS_Store
)

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alexandru N. Onea")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Header-only library providing basic \
means for working with 'comme' (like) COM objects under all platforms.")

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "Alexandru N. Onea")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

include(CPack)

option(WITH_EXAMPLES "Build the examples - requires libboost" OFF)
option(WITH_TESTS    "Enable and build tests"                 ON )

add_subdirectory(include)

if (WITH_TESTS)
  enable_testing ()
  add_subdirectory(tests)
endif ()

if(WITH_EXAMPLES)
  find_package(Boost REQUIRED COMPONENTS filesystem)
  add_subdirectory(examples)
endif ()

