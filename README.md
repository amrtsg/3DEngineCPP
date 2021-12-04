# 3D Graphics Engine C++/OpenGL

## Final Render

![alt text](https://github.com/amrtsg/GameEngineCPP/blob/master/githubpics/OpenGLScene.gif?raw=true)

NOTE: Currently it takes a couple tries to run the project successfully, it has to do with memory when loading heightmaps.

### Build

Create a folder called "build" in the project file, then create a VS solution using CMake

![alt text](https://github.com/amrtsg/GameEngineCPP/blob/master/githubpics/cmake.png?raw=true)

After opening the solution, be sure to set "src" as the startup project, and then do the following

 - ADD "assimp-vc140-mt.lib" to Linker -> Input -> Additional Dependencies
 - Copy the files in external/assimp/lib  - TO -> build/src

NOTE: WILL CHANGE THE LINKS FROM ABSOLUTE TO RELATIVE NEXT PUSH, FOR NOW JUST CHANGE THEM YOURSELF

# Functionality

### Terrain

![alt text](https://github.com/amrtsg/GameEngineCPP/blob/master/githubpics/terrain.png?raw=true)

### Skybox

![alt text](https://github.com/amrtsg/GameEngineCPP/blob/master/githubpics/skybox.png?raw=true)

### .OBJ File rendering using ASSIMP

![alt text](https://github.com/amrtsg/GameEngineCPP/blob/master/githubpics/3dobj.png?raw=true)

### Water tiles
![alt text](https://github.com/amrtsg/GameEngineCPP/blob/master/githubpics/watertile.png?raw=true)

# Dependencies (All Included)

 - Assimp
 - OpenGL
 - GLFW
 - GLEW
 - GLM
 - STB_IMAGE

# Next Update

 - Fix memory bug when running project.
