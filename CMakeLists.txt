cmake_minimum_required (VERSION 2.6)
include("common.cmake")
project (SoftNetworkAdapter)

add_subdirectory("networkadapter")
add_subdirectory("networkstack")
add_subdirectory("networkpackets")
add_subdirectory("networkutils")

include_directories("${PROJECT_SOURCE_DIR}/networkadapter")
include_directories("${PROJECT_SOURCE_DIR}/networkstack")
include_directories("${PROJECT_SOURCE_DIR}/networkpackets")
include_directories("${PROJECT_SOURCE_DIR}/networkutils")

add_executable(SoftNetworkAdapter ${PROJECT_SOURCE_DIR}/main.cpp)
target_link_libraries(SoftNetworkAdapter networkadapter networkstack networkpackets networkutils)

add_custom_target(
    run
    COMMAND sudo ./SoftNetworkAdapter
    DEPENDS SoftNetworkAdapter)