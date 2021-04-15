############ GÉNÉRAL ############
cmake_minimum_required(VERSION 3.17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
project(math4bg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

EXECUTE_PROCESS(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)

############ DÉPENDANCES ############
### SDL2 ###
message("Including SDL2...")
set(SDL2_DIR E:/PRG/C-C++/Libraries/SDL2-2.0.14)
include_directories(${SDL2_DIR}/x86_64-w64-mingw32/include)
message("Done!")
# find_package(SDL2)

### LUA ###
message("Including LUA...")
set(LUA_DIR E:/PRG/C-C++/Libraries/lua-5.4.2_Win64_dllw6_lib)
include_directories(${LUA_DIR}/include)
message("Done!")

### GLEW ###
message("Including GLEW...")
set(GLEW_DIR E:/PRG/C-C++/Libraries/glew-2.1.0)
include_directories(${GLEW_DIR}/include)
message("Done!")

### GLM ###
message("Including GLM")
set(GLM_DIR E:/PRG/C-C++/Libraries/glm-0.9.9.7/glm)
include_directories(${GLM_DIR})
message("Done!")

############ FICHIERS ############
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
        Transformers/LuaInterpreter.cpp
        Transformers/LuaInterpreter.h
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
        View/Renderer/3D/Vertices/VertexBufferLayout.h View/Renderer/3D/GL/GLMacros.cpp View/Renderer/3D/Object/Object3D.cpp View/Renderer/3D/Object/Object3D.h View/Renderer/3D/Vertices/IndexBuffer.cpp View/Renderer/3D/Vertices/IndexBuffer.h View/Renderer/Draw/IDrawable.cpp View/Renderer/Draw/IDrawable.h View/Renderer/2D/Object/Object2D.cpp View/Renderer/2D/Object/Object2D.h View/Renderer/2D/Object/Circle.cpp View/Renderer/2D/Object/Circle.h View/Renderer/2D/Object/Line.cpp View/Renderer/2D/Object/Line.h View/Renderer/2D/Object/SinglePixel.cpp View/Renderer/2D/Object/SinglePixel.h)

# SPÉCIFICITÉS
message("Compiling for : ")

if(WIN64 OR WIN32)
    list(APPEND SRC_FILES res.rc)
    message("Windows")
elseif(UNIX)
    message("UNIX")
elseif(APPLE)
    # Add an icon for the apple .app file
    list(APPEND SRC_FILES ../../src/osx/carbon/wxmac.icns)
    message("MacOS")
endif()

message("${ARCHITECTURE}")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("64bits")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message("32bits")
endif()

############ EXÉCUTABLE ############
add_executable(${PROJECT_NAME} ${SRC_FILES})
message("Done!")

message("Linking...")
############ LINK ############
### Specificités ###
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

message("Done!")