SET(COMPILE_FLAGS "-Wall -std=c++11 -pthread -g")
SET(LINK_FLAGS    "-std=c++11 -pthread -g")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")