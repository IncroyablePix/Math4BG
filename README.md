# Math4BG

## Synopsis
**Not** yet another game engine. 
To whom it may concern: This product is a small application with the idea that rendering was kind of hard to code for most people (including myself) and could be made easier. 
The ultimate goal is to help people who want to learn to code to be able to jump right into what people often want to learn to code for : 3D VIDEO GAMES. 
You may create a simple script (LUA only, currently), enjoy the easy-to-use functions provided by this software to create 2D or 3D scenes.

P.-S.: The camera movement currently uses the Z Q S D layout, not the W S A D one!

## Known bugs
* .OBJ loader does not support n-gons
* No materials supported
* No proper error catching on the args you can pass to the program through the lua script, which leads the program to crash if you give it too much crap to eat!

## In the future
In the future, the software should have those features : 
* Input manipulation through the script
* Multi-rendering API support (Vulkan)
* Sound playing
* Multiple scripting languages supported including Javascript and Python (Scratch?)
* A real GUI with a script editor, etc.
* All image formats supported (PNG, JPG, TIFF, GIF, .Whatever)
* Shadows (If I find back my courage)
* Spot lights
* Multi positionned light support
* Built-in physics?
* Some kind of eased-up shader coding

## Credits
Programming - IncroyablePix (Good luck to read this one)

## Libraries used
### SDL2 
The windowing library that's been used is **SDL2 2.0.12**.

### glew32
Even though 3D is currently unavailable, the current state of the code requires glew32. The exact version is **glew 2.1.0**

### lua54
The lua interpreter library is **lua 5.4.2**.

### GLM
You also need to import GLM, which has no need to be build before.

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

## Thanks to :
Maxime De Rycke for giving the wonderful name of "Math4BG"

