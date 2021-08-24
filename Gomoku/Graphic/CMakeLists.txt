cmake_minimum_required(VERSION 3.16.0)

set(PROGRAM_NAME "graphic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_library(${PROGRAM_NAME} STATIC 
            lib/graphic.cpp
            )

# 해당 라이브러리 컴파일 시 사용할 헤더파일 경로
target_include_directories(${PROGRAM_NAME} PUBLIC include)

target_link_libraries(${PROGRAM_NAME} GLUT::GLUT)
target_link_libraries(${PROGRAM_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})	