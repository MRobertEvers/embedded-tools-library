cmake_minimum_required (VERSION 3.8)

project ("EmbeddedLib")

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

include_directories("src")

# Include sub-projects.
add_subdirectory ("src")

file(GLOB_RECURSE srcs src/*.cpp src/*.h)

add_executable(Main main.cpp ${srcs})