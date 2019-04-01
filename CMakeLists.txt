cmake_minimum_required(VERSION 3.10)

project(CommeCOM VERSION 0.1 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS filesystem)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alexandru N. Onea")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Header-only library providing basic \
means for working with 'comme' (like) COM objects under all platforms.")

set(CPACK_PACKAGE_VENDOR "Alexandru N. Onea")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

include(CPack)

add_subdirectory(include)
add_subdirectory(examples)

