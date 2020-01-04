include("../cmake/common.cmake")
add_subdirectory(googletest)
include(CTest)
include(GoogleTest)

# DSP tests
set(sample_cdsp_sources
        basic_math.cpp
        biquad.cpp
        biquad_cascade.cpp
        complex.cpp
        complex_vector.cpp
        fft.cpp
        stft.cpp
        trig.cpp
        virtual_float.cpp
        )
add_executable(Tests ${sample_cdsp_sources})
target_link_libraries(Tests gtest gtest_main)
target_include_directories(Tests
        PRIVATE
        ../include
        ../cnl/include
        )

gtest_discover_tests(Tests)

