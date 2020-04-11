cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(project main.cpp p3dt_maths.h p3dt_objloader.h p3dt_texture.h)
target_link_libraries(project ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} sfml-graphics sfml-audio)
