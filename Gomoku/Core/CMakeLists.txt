cmake_minimum_required(VERSION 3.16.0)
set(libCore "core")

include_directories(${SPDLOG_INCLUDE_DIR})

add_library(${libCore} STATIC 
            lib/core.cpp            
            )

add_dependencies(${libCore} spdlog)            
# add_dependencies(${libCore} rapidjson)

MESSAGE(STATUS "RAPIDJSON PATH: " ${RAPIDJSON_INCLUDE_DIR})
MESSAGE(STATUS "SPDLOG PATH: " ${SPDLOG_INCLUDE_DIR})

# 해당 라이브러리 컴파일 시 사용할 헤더파일 경로
# target_include_directories(${libCore} PUBLIC ${RAPIDJSON_INCLUDE_DIR})
target_link_libraries(${libCore} PUBLIC ${SPDLOG_INCLUDE_DIR})
target_include_directories(${libCore} PUBLIC include)