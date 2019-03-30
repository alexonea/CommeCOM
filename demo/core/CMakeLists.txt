add_executable(experiment main.cpp)
target_link_libraries(experiment PRIVATE dl ${Boost_LIBRARIES} INTERFACE CCom)

