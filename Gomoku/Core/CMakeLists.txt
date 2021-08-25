cmake_minimum_required(VERSION 3.16.0)
set(libCore "core")

add_library(${libCore} STATIC 
            lib/core.cpp            
            )

add_dependencies(${libCore} spdlog)            
add_dependencies(${libCore} rapidjson)

# 해당 라이브러리 컴파일 시 사용할 헤더파일 경로
target_include_directories(${libCore} PRIVATE ${RAPIDJSON_INCLUDE_DIR})
target_include_directories(${libCore} PUBLIC ${SPDLOG_INCLUDE_DIR})
target_include_directories(${libCore} PUBLIC include)