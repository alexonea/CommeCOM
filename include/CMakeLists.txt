add_library(CCom INTERFACE)
target_sources(CCom INTERFACE
  CCom/Cast.hpp
  CCom/CInterfacePtr.hpp
  CCom/Dynamic.hpp
  CCom/Guid.hpp
  CCom/IUnknown.hpp
  CCom/Types.hpp
  CCom/Utils.hpp
)

target_include_directories(CCom INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/CCom>
  $<INSTALL_INTERFACE:include/CCom>
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/CCom DESTINATION include)

