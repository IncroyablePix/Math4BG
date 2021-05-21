############ GENERAL ############
cmake_minimum_required(VERSION 3.17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
project(math4bg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

EXECUTE_PROCESS(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)

############ DEPENDENCIES ############
### SDL2 ###
message("Including SDL2...")
set(SDL2_DIR $ENV{SDL2})
message("SDL2 Directory : ${SDL2_DIR}")
include_directories(${SDL2_DIR}/x86_64-w64-mingw32/include)
message("Done!")
# find_package(SDL2)

### LUA ###
message("Including LUA...")
set(LUA_DIR $ENV{LUA64})
message("LUA Directory : ${LUA_DIR}")
include_directories(${LUA_DIR}/include)
message("Done!")

### GLEW ###
message("Including GLEW...")
set(GLEW_DIR $ENV{GLEW})
message("GLEW Directory : ${GLEW_DIR}")
include_directories(${GLEW_DIR}/include)
message("Done!")

### GLM ###
message("Including GLM")
set(GLM_DIR $ENV{GLM})
include_directories(${GLM_DIR})
message("Done!")

### DUKTAPE ###
message("Including DukType")
set(DUKTP_DIR $ENV{DUKTAPE64})
message("DUKTAPE Directory : ${DUKTP_DIR}")
include_directories(${DUKTP_DIR}/include)
message("Done!")

############ SOURCE ############
set(SRC_FILES
        Program/main.cpp
        View/Window.cpp
        View/Window.h
        View/Screen.cpp
        View/Screen.h
        View/Renderer/2D/Renderer2D.cpp
        View/Renderer/2D/Renderer2D.h
        Program/Application.cpp
        Program/Application.h
        View/Renderer/2D/Object/Point.cpp
        View/Renderer/2D/Object/Point.h
        Transformers/Interpreter/LuaInterpreter.cpp
        Transformers/Interpreter/LuaInterpreter.h
        Program/Config/Config.cpp
        Program/Config/Config.h
        Transformers/World.cpp
        Transformers/World.h
        View/Error.cpp
        View/Error.h
        Transformers/Context.cpp
        Transformers/Context.h
        Transformers/Contexts.cpp
        Transformers/Contexts.h
        View/Renderer/IRenderer.cpp
        View/Renderer/IRenderer.h
        Transformers/WorldType.h
        View/Renderer/3D/Renderer3D.cpp
        View/Renderer/3D/Renderer3D.h
        View/Renderer/3D/Shaders/ShaderProgramSource.cpp
        View/Renderer/3D/Shaders/ShaderProgramSource.h
        View/Renderer/3D/Shaders/Shader.cpp
        View/Renderer/3D/Shaders/Shader.h
        View/Renderer/3D/GL/GLMacros.h
        View/Renderer/3D/Vertices/VertexArray.cpp
        View/Renderer/3D/Vertices/VertexArray.h
        View/Renderer/3D/Vertices/VertexBuffer.cpp
        View/Renderer/3D/Vertices/VertexBuffer.h
        View/Renderer/3D/Vertices/VertexBufferLayout.cpp
        View/Renderer/3D/Vertices/VertexBufferLayout.h View/Renderer/3D/GL/GLMacros.cpp View/Renderer/3D/Object/Object3D.cpp View/Renderer/3D/Object/Object3D.h View/Renderer/3D/Vertices/IndexBuffer.cpp View/Renderer/3D/Vertices/IndexBuffer.h View/Renderer/Draw/IDrawable.cpp View/Renderer/Draw/IDrawable.h View/Renderer/2D/Object/Object2D.cpp View/Renderer/2D/Object/Object2D.h View/Renderer/2D/Object/Circle.cpp View/Renderer/2D/Object/Circle.h View/Renderer/2D/Object/Line.cpp View/Renderer/2D/Object/Line.h View/Renderer/2D/Object/SinglePixel.cpp View/Renderer/2D/Object/SinglePixel.h View/Renderer/2D/Object/Rectangle.cpp View/Renderer/2D/Object/Rectangle.h View/Renderer/3D/Object/Cube.cpp View/Renderer/3D/Object/Cube.h Output/IOutput.cpp Output/IOutput.h Output/Console/TerminalOutput.cpp Output/Console/TerminalOutput.h View/Renderer/3D/GL/GLUtils.cpp View/Renderer/3D/GL/GLUtils.h Utils/FileSplit.cpp Utils/FileSplit.h View/Renderer/3D/Camera/ICamera.cpp View/Renderer/3D/Camera/ICamera.h View/Renderer/3D/Camera/MainCamera.cpp View/Renderer/3D/Camera/MainCamera.h Input/KeyInput.cpp Input/KeyInput.h Input/MouseInput.cpp Input/MouseInput.h IO/IModelLoader.cpp IO/IModelLoader.h IO/OBJLoader.cpp IO/OBJLoader.h Transformers/Interpreter/ILanInterpreter.cpp Transformers/Interpreter/ILanInterpreter.h Transformers/Interpreter/JavascriptInterpreter.cpp Transformers/Interpreter/JavascriptInterpreter.h Physics/Transform.cpp Physics/Transform.h IO/ModelData.h View/Renderer/3D/Vertices/Vertex.cpp View/Renderer/3D/Vertices/Vertex.h View/Renderer/3D/Vertices/Mesh.cpp View/Renderer/3D/Vertices/Mesh.h View/Renderer/3D/Object/Pyramid.cpp View/Renderer/3D/Object/Pyramid.h IO/IMG/ImageLoaders.cpp IO/IMG/ImageLoaders.h View/Renderer/3D/Texture/Texture.cpp View/Renderer/3D/Texture/Texture.h View/Renderer/3D/Texture/BMPTexture.cpp View/Renderer/3D/Texture/BMPTexture.h)


# OS SPECIFICITIES
message("Compiling for : ")

if(WIN64 OR WIN32)
    list(APPEND SRC_FILES res.rc)
    message("Windows")
elseif(UNIX)
    message("UNIX")
elseif(APPLE)
    list(APPEND SRC_FILES ../../src/osx/carbon/wxmac.icns)
    message("MacOS")
endif()

message("${ARCHITECTURE}")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("64bits")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message("32bits")
endif()

############ EXECUTABLE ############
add_executable(${PROJECT_NAME} ${SRC_FILES})
message("Done!")

message("Linking...")
############ LINK ############
### Specificities ###
if(WIN64 OR WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC -lopengl32)
endif()

### SDL 2 ###
message("Linking SDL2...")
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_DIR}/x86_64-w64-mingw32/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_DIR}/x86_64-w64-mingw32/bin/SDL2.dll)

### LUA ###
message("Linking Lua...")
target_include_directories(${PROJECT_NAME} PUBLIC ${LUA_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LUA_DIR}/lua54.dll)

### GLEW ###
message("Linking GLEW...")
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLEW_DIR}/bin/Release/x64/glew32.dll)

### DUKTAPE ###
message("Linking DUKTAPE...")
target_include_directories(${PROJECT_NAME} PUBLIC ${DUKTP_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DUKTP_DIR}/lib/libduktape.dll)

message("Done!")