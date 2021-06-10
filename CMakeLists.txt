cmake_minimum_required(VERSION 3.12)

project(urii VERSION 0.0.3 LANGUAGES CXX)


# Options
option(ENABLE_PCH   "Enable Precompiled Headers"  False)
option(ENABLE_TESTS "Enable tests"                False)

# Sources
set(SOURCES
    src/UriHandler.cpp
    )

#add_executable("${PROJECT_NAME}_runner" src/main.cpp)
add_library(${PROJECT_NAME} STATIC ${SOURCES})


## Compiler options
include(cmake/CompilerOptions.cmake)
set_project_options(${PROJECT_NAME})


## Setup Conan
# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP NO_OUTPUT_DIRS)


## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(fmt REQUIRED)

# ---
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE include)
#target_sources("${PROJECT_NAME}_runner" PUBLIC ${SOURCES} src/main.cpp)
#target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})


## Check custom options
if (ENABLE_PCH) # Since CMake 3.15
  set(PC_HEADERS <vector> <string> <map> <utility> <algorithm> <cctype> <ostream> <memory> <sstream> <gtest/gtest.h>)
  target_precompile_headers(${PROJECT_NAME} INTERFACE ${PC_HEADERS})
  message("Pre compiled headers enabled")
endif ()

if (ENABLE_TESTS)
  message(STATUS "Tests enabled")
  enable_testing() # Must be placed before add_subdirectory
  add_subdirectory(test)
endif ()


## Install commands
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "/opt/${PROJECT_NAME}"
    )

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Juan Jose Castellanos <juancho.312@hotmail.com>")
include(CPack)
