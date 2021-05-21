# Math4BG

## Credits
Programming - IncroyablePix (Good luck to read this one)
Programming - Indirectly TheCherno, whose OpenGL code has been quite useful to me.

## Libraries used
### SDL2 
The windowing library that's been used is **SDL2 2.0.12**.

### glew32
Even though 3D is currently unavailable, the current state of the code requires glew32. The exact version is **glew 2.1.0**

### lua54
The lua interpreter library is **lua 5.4.2**.

### For all
All libs are dynamically linked and shall be placed in the same directory as the executable.

## Build
### Environment variables 
As a lazy guy, I used environment variables to point to my libs directories : 
Three environment variables have to be set up :
- SDL2 -> Pointing to the SDL2 directory
- LUA64 -> Pointing to the Lua directory
- GLEW -> Pointing to the glew32 directory

### CMake
The version of CMake that I've personally built the application with is **3.17**.

### Compiler
I have not tried to build on another OS yet but since all libraries are cross-platform, it should not be a big deal porting it.
I currently only built a Win64 release with the **MinGW64** compiler. 

## Installation
The installation requires some work of yours!
1. Create a whatever-named directory.
2. Put the executable and libraries into it.
3. Create both "shaders" and "scripts" directories
4. In the shaders directory, you may create shaders with a specific syntax explained further.
5. In the scripts directory, you can add your own Lua scripts, the documentation about it is provided in this git repo.
6. Create a **settings.cfg** file in the root directory.

### Settings
Two settings can currently be precised:
- **script**: You have to specify a script **without** the ".lua" extension for it to be loaded. (example: script = "test")
- **fpslimiter**: I'd recommend to feed it a "true" value. (example: fpslimiter = true)

### Shaders
As the 3D is not currently well developped, it has no real point to go further on this. However the syntax is the following (c.f. TheCherno):
- #shader vertex as a first line, followed by the vertex shader code
- #shader fragment in a second time, followed by the fragment shader code

## Thanks to :
TheCherno for his OpenGL tutorial.
The-One-Who-Does-Not-Want-To-Be-Mentionned who helped me out testing on different machines.
Maxime De Rycke for giving the wonderful name of "Math4BG"
