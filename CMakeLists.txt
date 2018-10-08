cmake_minimum_required(VERSION 3.4)
project(PhysicsLib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

IF (NOT TARGET gtest)
    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(../googletest)
ENDIF()

add_library(Physics STATIC
    world.hpp
    world.cpp
    sphere.hpp
    sphere.cpp
    vec3.hpp
    vec3.cpp
    )

set(TEST_NAME ${PROJECT_NAME}_UnitTest)

add_executable(${TEST_NAME}
       physics_unittests.cpp
    )

target_link_libraries(${TEST_NAME}
    Physics
    gtest
    gtest_main
)
