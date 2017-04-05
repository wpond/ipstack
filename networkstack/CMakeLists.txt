cmake_minimum_required (VERSION 2.6)
include("../common.cmake")

include_directories(".")

# TODO: prune
include_directories("../networkadapter")
include_directories("../networkutils")

add_library(
    networkstack
    networkstack_stack.cpp)