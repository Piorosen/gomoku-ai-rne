set(PROGRAM_NAME "Gomoku-ai")
PROJECT(${PROGRAM_NAME})
cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_SOURCE_DIR}/ThirdParty/rapidjson.cmake)
include(${CMAKE_SOURCE_DIR}/ThirdParty/spdlog.cmake)
include(${CMAKE_SOURCE_DIR}/ThirdParty/stb.cmake)

MESSAGE(STATUS "RAPIDJSON PATH: " ${RAPIDJSON_INCLUDE_DIR})
MESSAGE(STATUS "SPDLOG PATH: " ${SPDLOG_INCLUDE_DIR})
MESSAGE(STATUS "STB PATH: " ${STB_INCLUDE_DIR})

# Add Dependecy Library Directory
ADD_EXECUTABLE(${PROGRAM_NAME}
	main.cpp
	)

add_subdirectory(Core core/)
add_subdirectory(Graphic graphic/)

target_link_libraries(${PROGRAM_NAME} core)
target_link_libraries(${PROGRAM_NAME} graphic)
