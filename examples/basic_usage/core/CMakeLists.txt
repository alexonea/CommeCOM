add_executable(drawable_papler main.cpp)
target_link_libraries(drawable_papler PRIVATE dl ${Boost_LIBRARIES} CCom)
