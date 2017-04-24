cmake_minimum_required (VERSION 2.6)
include("../common.cmake")
project (Tests)

add_subdirectory("../networkadapter" "networkadapter")
add_subdirectory("../networkstack" "networkstack")
add_subdirectory("../networkpackets" "networkpackets")
add_subdirectory("../networkutils" "networkutils")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("../networkadapter")
include_directories("../networkstack")
include_directories("../networkpackets")
include_directories("../networkutils")

add_executable(Tests
    ${PROJECT_SOURCE_DIR}/tests_testadapter.cpp
    ${PROJECT_SOURCE_DIR}/tests_testadapter.t.cpp
    ${PROJECT_SOURCE_DIR}/networkutils_packet.t.cpp
    ${PROJECT_SOURCE_DIR}/networkutils_byteoutputter.t.cpp
    ${PROJECT_SOURCE_DIR}/networkstack_stack.t.cpp
    ${PROJECT_SOURCE_DIR}/networkpackets_arpfactory.t.cpp
    ${PROJECT_SOURCE_DIR}/networkpackets_arpdecoder.t.cpp)
target_link_libraries(
    Tests
    gtest_main
    gtest
    networkadapter
    networkstack
    networkpackets
    networkutils)

add_custom_target(
    run
    COMMAND ./Tests
    DEPENDS Tests)