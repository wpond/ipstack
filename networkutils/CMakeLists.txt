cmake_minimum_required (VERSION 2.6)
include("../common.cmake")

include_directories(".")

# TODO: prune
include_directories("../networkadapter")
include_directories("../networkstack")

add_library(
    networkutils
    networkutils_byteoutputter.cpp
    networkutils_packet.cpp
    networkutils_macaddress.cpp
    networkutils_ipaddress.cpp)