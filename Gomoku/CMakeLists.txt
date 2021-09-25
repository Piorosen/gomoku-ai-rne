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

if (WIN32)
set_property(TARGET ${PROGRAM_NAME}
        PROPERTY VS_PACKAGE_REFERENCES "nupengl.core_0.1.0.1"
    )
endif()
add_subdirectory(Core core/)
add_subdirectory(Graphic graphic/)

target_link_libraries(${PROGRAM_NAME} core)
target_link_libraries(${PROGRAM_NAME} graphic)
