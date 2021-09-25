set(PROGRAM_NAME "Gomoku-ai")
PROJECT(${PROGRAM_NAME})
cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# install(DIRECTORY resources/ DESTINATION "${CMAKE_BINARY_DIR}/resources")
if(WIN32)
	FILE(COPY ${CMAKE_SOURCE_DIR}/ThirdParty/freeglut/bin/ DESTINATION "${CMAKE_BINARY_DIR}")
	FILE(COPY ${CMAKE_SOURCE_DIR}/ThirdParty/glew/bin/ DESTINATION "${CMAKE_BINARY_DIR}")
	
endif()
FILE(COPY resources/ DESTINATION "${CMAKE_BINARY_DIR}/resources")
MESSAGE(STATUS "RESOURCE PATH : " ${CMAKE_BINARY_DIR}/resources)

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
if (WIN32)
	#message(STATUS ${PROGRAM_NAME})
	#target_include_directories(${PROGRAM_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/freeglut/include)
    #target_include_directories(${PROGRAM_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/glew/include)

    #target_link_directories(${PROGRAM_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/freeglut/lib)
    #target_link_directories(${PROGRAM_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/glew/lib)
endif()

target_link_libraries(${PROGRAM_NAME} core)
target_link_libraries(${PROGRAM_NAME} graphic)
