add_library(CCom INTERFACE)

file(GLOB HEADERS
  CCom/Cast.hpp
  CCom/CInterfacePtr.hpp
  CCom/Dynamic.hpp
  CCom/Guid.hpp
  CCom/IUnknown.hpp
  CCom/Types.hpp
  CCom/Utils.hpp
)

target_sources(CCom INTERFACE ${HEADERS})

target_include_directories(CCom INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/CCom DESTINATION include)

