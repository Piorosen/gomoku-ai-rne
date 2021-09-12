cmake_minimum_required(VERSION 3.16.0)
set(libGraphic "graphic")

find_package(OpenGL REQUIRED)
if (WIN32) 
    
else()
    find_package(GLUT REQUIRED)
endif()

add_library(${libGraphic} STATIC 
            lib/graphic/application.cpp
            lib/graphic/utils/color.cpp
            lib/graphic/utils/imagecollect.cpp
            
            lib/graphic/components/imageview.cpp
            lib/graphic/components/view.cpp
            lib/graphic/components/button.cpp
            lib/graphic/components/imagebutton.cpp
            lib/graphic/components/gameBoard.cpp

            lib/graphic/viewcontroller/viewcontroller.cpp
            )

# ADD_LIBRARY(${libGraphic} SHARED ${VTI_SOURCES})

# add_dependencies(${libGraphic} spdlog)   
# add_dependencies(${libGraphic} stb)

if(WIN32)
    # add_dependencies(${libGraphic} freeglut)
    # target_include_directories(${libGraphic} PUBLIC ${FREEGLUT_INCLUDE_DIR})
    # target_link_directories(${libGraphic} PUBLIC ${FREEGLUT_LIBRARY_DIR})
else()

endif()

target_include_directories(${libGraphic} PUBLIC ${SPDLOG_INCLUDE_DIR})
target_include_directories(${libGraphic} PUBLIC ${STB_INCLUDE_DIR})
target_include_directories(${libGraphic} PUBLIC include)

if(WIN32)
    
else()
    target_link_libraries(${libGraphic} GLUT::GLUT)
endif()
target_link_libraries(${libGraphic} ${OPENGL_LIBRARIES})