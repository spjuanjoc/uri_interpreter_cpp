set(TEST_NAME ${PROJECT_NAME}_AllTests)

add_definitions(-DGTEST_LANGUAGE_CXX11)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.test.cpp)

add_executable(${TEST_NAME} ${TEST_SOURCES} ../src/URIHandler.cpp)
add_test(${TEST_NAME} ${TEST_NAME})

message("Tests included")

# Get the headers
set(INCLUDES include)
include_directories(PUBLIC ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

# Link googletest with the current project
if (ENABLE_CONAN)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
  conan_target_link_libraries(${TEST_NAME} CONAN_PKG::gtest CONAN_PKG::gmock )
endif ()
