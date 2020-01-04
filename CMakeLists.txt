cmake_minimum_required(VERSION 3.2)
project(Cdsp)
include("cmake/common.cmake")

set(Cnl_DESTDIR ${CMAKE_BINARY_DIR}/install)
file(MAKE_DIRECTORY ${Cnl_DESTDIR})

message("-- CXX COMPILER = ${CMAKE_CXX_COMPILER}")
message("-- C COMPILER = ${CMAKE_C_COMPILER}")
message("-- INT128 = ${INT128}")
message("-- STD = ${STD}")
message("-- EXCEPTIONS = ${EXCEPTIONS}")

add_definitions(-DINT128=${INT128} -DSTD=${STD} -DEXCEPTIONS=${EXCEPTIONS})
add_subdirectory(cnl)

# runs a suite of compile-time tests using `static_assert`
# and run-time tests using gtest
include(CTest)
add_subdirectory("test" EXCLUDE_FROM_ALL)

add_library(Cdsp INTERFACE)

install(DIRECTORY include/ DESTINATION include)

target_include_directories(
        Cdsp INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS Cdsp EXPORT CdspTargets)

install(EXPORT CdspTargets
    FILE CdspConfig.cmake
    NAMESPACE Cdsp::
    DESTINATION lib/cmake/cdsp)

install(DIRECTORY ${Cnl_DESTDIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX})
