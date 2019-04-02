add_executable (test_IID
  main.cpp
  Unit_1.cpp
  Unit_2.cpp
  Unit_3.cpp
)

target_link_libraries (test_IID PRIVATE CCom)

add_test (test_IID test_IID)

