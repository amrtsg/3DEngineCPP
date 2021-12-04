cmake_minimum_required(VERSION 3.10)

project ("3DWorld")

#--- Load the common configuration
include(common/config.cmake)

#--- OpenGL configuration
include(common/OpenGL.cmake)
include(common/GLEW.cmake)
include(common/GLFW.cmake)

#---include directories-----
include_directories(external/glm)
include_directories(src/headers)
include_directories(src/water)
include_directories(external/stb_image)
include_directories(external/SOIL2)
include_directories(external/assimp/include)

#---Link directories--------
link_directories(external/assimp/lib)

add_subdirectory(src)