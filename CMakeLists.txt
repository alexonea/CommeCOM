cmake_minimum_required(VERSION 3.10)

project(CommeCOM VERSION 0.1)

find_package(Boost REQUIRED COMPONENTS filesystem)

include_directories(include)

add_subdirectory(include)
add_subdirectory(demo)

