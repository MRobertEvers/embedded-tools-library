add_subdirectory("windows")

file(GLOB srcs *.cpp *.h)

add_library(lib ${srcs})