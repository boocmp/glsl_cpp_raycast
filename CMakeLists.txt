cmake_minimum_required(VERSION 3.20)
project(RayCasting LANGUAGES CXX VERSION 1.0)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(dependencies)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h)

add_library(sources STATIC ${SOURCES} canvas.cpp canvas.h)
set_target_properties(sources PROPERTIES CXX_STANDARD 23)
target_link_libraries(sources PUBLIC ImGui-SFML::ImGui-SFML)
target_include_directories(sources PRIVATE "${gtest_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML sources)

file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(tests ${TEST_SOURCES})
set_target_properties(tests PROPERTIES CXX_STANDARD 23)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(tests PRIVATE gtest gmock gtest_main sources)
add_test(tests tests)
enable_testing()

include(GoogleTest)
gtest_discover_tests(tests)
