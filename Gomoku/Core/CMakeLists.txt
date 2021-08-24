cmake_minimum_required(VERSION 3.16.0)
set(PROGRAM_NAME "core")

add_library(${PROGRAM_NAME} STATIC 
            lib/core.cpp            
            )

    
include(${CMAKE_SOURCE_DIR}/ThirdParty/rapidjson.cmake)
include_directories(${RAPIDJSON_INCLUDE_DIR})

# 해당 라이브러리 컴파일 시 사용할 헤더파일 경로
target_include_directories(${PROGRAM_NAME} PUBLIC include)