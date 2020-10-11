set(TEST_NAME ${PROJECT_NAME}_AllTests)

add_definitions(-DGTEST_LANGUAGE_CXX11)

add_executable(${TEST_NAME} )

add_test(${TEST_NAME} ${TEST_NAME})

message("Tests included")

# ---
# target instructions must be set after add_executable or add_library instructions

#target_compile_options(${TEST_NAME} INTERFACE ${PROJECT_OPTIONS})

# Get the sources
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.test.cpp)
target_sources(${TEST_NAME} PUBLIC ${TEST_SOURCES} ../src/URIHandler.cpp) # Todo remove URIHandler from here

# Get the headers
set(INCLUDES include)
include_directories(PUBLIC ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})


if (ENABLE_CONAN)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
  # Link googletest with the current project
  conan_target_link_libraries(${TEST_NAME} CONAN_PKG::gtest #[[CONAN_PKG::gmock]] )
endif ()
