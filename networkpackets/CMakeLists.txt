cmake_minimum_required (VERSION 2.6)
include("../common.cmake")

include_directories(".")

include_directories("../networkutils")

add_library(
    networkpackets
    networkpackets_arpfactory.cpp
    networkpackets_arpdecoder.cpp
    networkpackets_genericdecoder.cpp)