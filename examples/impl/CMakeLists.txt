add_library(paper SHARED CPaper.cpp CDummy.cpp)
target_link_libraries(paper PRIVATE CCom)

