cmake_minimum_required(VERSION 3.16.0)
set(libGraphic "graphic")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_library(${libGraphic} STATIC 
            lib/graphic/application.cpp
            
            lib/graphic/components/view.cpp
            lib/graphic/components/button.cpp
            lib/graphic/components/window.cpp
            )

add_dependencies(${libGraphic} spdlog)   
add_dependencies(${libGraphic} stb)   

target_include_directories(${libGraphic} PUBLIC ${SPDLOG_INCLUDE_DIR})
target_include_directories(${libGraphic} PUBLIC ${STB_INCLUDE_DIR})

# 해당 라이브러리 컴파일 시 사용할 헤더파일 경로
target_include_directories(${libGraphic} PUBLIC include)

target_link_libraries(${libGraphic} GLUT::GLUT)
target_link_libraries(${libGraphic} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})	