cmake_minimum_required (VERSION 2.6)
include("../common.cmake")

include_directories(".")

# TODO: prune
include_directories("../networkstack")
include_directories("../networkutils")

add_library(
    networkadapter
    networkadapter_adapter.cpp
    networkadapter_observer.cpp
    networkadapter_reader.cpp
    networkadapter_writer.cpp)