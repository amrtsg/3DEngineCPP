# 3D Graphics Engine C++/OpenGL

## Final Render

![alt text](https://github.com/amrtsg/graphics-engine/blob/master/githubpics/OpenGLScene.gif?raw=true)

NOTE: Currently it takes a couple tries to run the project successfully, it has to do with memory when loading heightmaps.

### Build

Create a folder called "build" in the project folder, then create a VS solution using CMake

![alt text](https://github.com/amrtsg/graphics-engine/blob/master/githubpics/cmake.png?raw=true)

After opening the solution, be sure to set "src" as the startup project, and then do the following

 - ADD "assimp-vc140-mt.lib" to Linker -> Input -> Additional Dependencies
 - Copy the files in external/assimp/lib  - TO -> build/src

# Functionality

### Terrain

![alt text](https://github.com/amrtsg/graphics-engine/blob/master/githubpics/terrain.png?raw=true)

### Skybox

![alt text](https://github.com/amrtsg/graphics-engine/blob/master/githubpics/skybox.png?raw=true)

### .OBJ File rendering using ASSIMP

![alt text](https://github.com/amrtsg/graphics-engine/blob/master/githubpics/3dobj.png?raw=true)

### Water tiles
![alt text](https://github.com/amrtsg/graphics-engine/blob/master/githubpics/watertile.png?raw=true)

# Dependencies (All Included)

 - Assimp
 - OpenGL
 - GLFW
 - GLEW
 - GLM
 - STB_IMAGE

# Next Update

 - Fix memory bug when running project.
