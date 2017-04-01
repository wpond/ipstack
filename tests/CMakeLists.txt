cmake_minimum_required (VERSION 2.6)
include("../common.cmake")
project (Tests)

add_subdirectory("../networkadapter" "networkadapter")
add_subdirectory("../networkstack" "networkstack")
add_subdirectory("../networkutils" "networkutils")

include_directories("../networkadapter")
include_directories("../networkstack")
include_directories("../networkutils")

add_executable(Tests
    ${PROJECT_SOURCE_DIR}/networkstack_packet.t.cpp)
target_link_libraries(
    Tests
    gtest_main
    gtest
    networkadapter
    networkstack
    networkutils)

add_custom_target(
    run
    COMMAND ./Tests
    DEPENDS Tests)