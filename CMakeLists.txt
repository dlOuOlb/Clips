cmake_minimum_required(VERSION 3.0)
project(OuOClip)

set(CMAKE_CONFIGURATION_TYPES "Release")
set(CMAKE_BUILD_TYPE "Release")

# MemClip
add_library(memclip STATIC "./Sources/memclip.c")
target_include_directories(memclip PUBLIC "./Headers")

# PenClip
add_library(penclip STATIC "./Sources/penclip.c")
target_include_directories(penclip PUBLIC "./Headers")

# BitClip
add_library(bitclip STATIC "./Sources/bitclip.c")
target_include_directories(bitclip PUBLIC "./Headers")
