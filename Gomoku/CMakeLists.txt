set(PROGRAM_NAME "Gomoku-ai")
PROJECT(${PROGRAM_NAME})
cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Dependecy Library Directory
add_subdirectory(Core core/)
add_subdirectory(Graphic graphic/)

include_directories(${OPENGL_INCLUDE_DIR})

ADD_EXECUTABLE(${PROGRAM_NAME}
	main.cpp
	)

target_link_libraries(${PROGRAM_NAME} core)
target_link_libraries(${PROGRAM_NAME} graphic)
