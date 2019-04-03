add_library (test_IID_UnitDef UnitDef.cpp)
target_link_libraries (test_IID_UnitDef PRIVATE CCom)

add_library (test_IID_UnitDecl UnitDecl.cpp)
target_link_libraries (test_IID_UnitDecl PRIVATE CCom)

add_executable (test_IID main.cpp)
target_link_libraries (test_IID
  PRIVATE CCom test_IID_UnitDef test_IID_UnitDecl
)

add_test (test_IID test_IID)
