add_executable (test_IID
  main.cpp
  UnitDef.cpp
  UnitDecl.cpp
)

target_link_libraries (test_IID PRIVATE CCom)

add_test (test_IID test_IID)

