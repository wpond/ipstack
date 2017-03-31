cmake_minimum_required (VERSION 2.6)
include("../common.cmake")

include_directories(".")

# TODO: prune
include_directories("../networkstack")
include_directories("../networkutils")

add_library(
    networkadapter
    basestation_networkadapter.cpp
    basestation_networkobserver.cpp
    basestation_networkreader.cpp
    basestation_networkwriter.cpp)