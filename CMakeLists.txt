cmake_minimum_required (VERSION 3.8)

project ("EmbeddedLib")

include_directories("src")

# Include sub-projects.
add_subdirectory ("src")

add_executable(Main main.cpp ${srcs})