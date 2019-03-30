cmake_minimum_required(VERSION 3.10)

project(experiment)

find_package(Boost REQUIRED COMPONENTS filesystem)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(core)
add_subdirectory(impl)

