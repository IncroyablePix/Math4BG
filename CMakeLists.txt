############ GENERAL ############
cmake_minimum_required(VERSION 3.17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
project(math4bg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

EXECUTE_PROCESS(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)

### Platform ###
if(WIN64 OR WIN32)
    set(OS NT)
elseif(UNIX)
    set(OS UNIX)
elseif(APPLE)
    set(OS MAC)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS 64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(BITS 32)
endif()

############ DEPENDENCIES ############
### SDL2 ###
message("Including SDL2...")

if(NOT DEFINED     SDL2_ROOT  AND
NOT DEFINED $ENV{SDL2_ROOT})
    set(SDL2_ROOT "$ENV{SDL2}")
endif()

if(OS STREQUAL "NT")
    if (BITS MATCHES 64)
        set(SDL2_INCLUDE_DIRS "${SDL2_ROOT}/x86_64-w64-mingw32/include")
        set(SDL2_LIBRARIES "${SDL2_ROOT}/x86_64-w64-mingw32/bin/SDL2.dll")
    else (BITS MATCHES 32)
        set(SDL2_INCLUDE_DIRS "${SDL2_ROOT}/i686-w64-mingw32/include")
        set(SDL2_LIBRARIES "${SDL2_ROOT}/i686-w64-mingw32/bin/SDL2.dll")
    endif ()
elseif(OS STREQUAL "UNIX")
    find_package(SDL2 REQUIRED)
endif()

message("Done!")

### LUA ###
message("Including LUA...")

if(NOT DEFINED     LUA_ROOT  AND
        NOT DEFINED $ENV{LUA_ROOT})
    set(LUA_ROOT $ENV{LUA64})
endif()

if(OS STREQUAL "NT")
    set(LUA_INCLUDE_DIRS "${LUA_ROOT}/include")
    set(LUA_LIBRARIES "${LUA_ROOT}/lua54.dll")
elseif(OS STREQUAL "UNIX")
    find_package(LUA REQUIRED)
endif()

message("Done!")

### GLEW ###
message("Including GLEW...")

if(NOT DEFINED     GLEW_ROOT  AND
        NOT DEFINED $ENV{GLEW_ROOT})
    set(GLEW_ROOT $ENV{GLEW})
endif()

find_package(GLEW REQUIRED)
message("Done!")

### OpenGL ###

if(OS STREQUAL "UNIX")
    find_package(OpenGL REQUIRED)
endif()

### GLM ###
message("Including GLM")
set(GLM_DIR $ENV{GLM})
include_directories(${GLM_DIR})
message("Done!")

############ SOURCE ############
set(SRC_FILES
        Program/main.cpp
        View/Window.cpp
        View/Window.h
        View/Screen.cpp
        View/Screen.h
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
        View/Renderer/OG33RendererSDL.cpp
        View/Renderer/OG33RendererSDL.h
        Transformers/WorldType.h
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
        View/Renderer/3D/Vertices/VertexBufferLayout.h
        View/Renderer/3D/GL/GLMacros.cpp
        View/Renderer/3D/Object/Object3D.cpp
        View/Renderer/3D/Object/Object3D.h
        View/Renderer/3D/Vertices/IndexBuffer.cpp
        View/Renderer/3D/Vertices/IndexBuffer.h
        View/Renderer/Draw/IDrawable.cpp
        View/Renderer/Draw/IDrawable.h
        View/Renderer/2D/Object/Object2D.cpp
        View/Renderer/2D/Object/Object2D.h
        View/Renderer/2D/Object/Circle.cpp
        View/Renderer/2D/Object/Circle.h
        View/Renderer/2D/Object/Line.cpp
        View/Renderer/2D/Object/Line.h
        View/Renderer/2D/Object/Rectangle.cpp
        View/Renderer/2D/Object/Rectangle.h
        View/Renderer/3D/Object/Cube.cpp
        View/Renderer/3D/Object/Cube.h
        Output/IOutput.cpp
        Output/IOutput.h
        Output/Console/TerminalOutput.cpp
        Output/Console/TerminalOutput.h
        View/Renderer/3D/GL/GLUtils.cpp
        View/Renderer/3D/GL/GLUtils.h
        Utils/FileSplit.cpp
        Utils/FileSplit.h
        View/Renderer/3D/Camera/ICamera.cpp
        View/Renderer/3D/Camera/ICamera.h
        View/Renderer/3D/Camera/MainCamera.cpp
        View/Renderer/3D/Camera/MainCamera.h
        View/IMGUI/imconfig.h
        View/IMGUI/imgui.cpp
        View/IMGUI/imgui.h
        View/IMGUI/imgui_demo.cpp
        View/IMGUI/imgui_draw.cpp
        View/IMGUI/imgui_internal.h
        View/IMGUI/imgui_sdl.h
        View/IMGUI/imgui_sdl.cpp
        View/IMGUI/imgui_tables.cpp
        View/IMGUI/imgui_widgets.cpp
        View/IMGUI/imstb_rectpack.h
        View/IMGUI/imstb_textedit.h
        View/IMGUI/imstb_truetype.h
        View/IMGUI/imgui_impl_sdl.h
        View/IMGUI/imgui_impl_sdl.cpp
        View/IMGUI/imgui_impl_opengl3.h
        View/IMGUI/imgui_impl_opengl3.cpp
        View/IMGUI/imgui_impl_opengl3_loader.h
        View/IMGUI/TextEditor.h
        View/IMGUI/TextEditor.cpp
        View/IMGUI/ImGuiFileBrowser.h
        View/IMGUI/ImGuiFileBrowser.cpp
        View/IMGUI/Dirent/dirent.h
        Output/CircularQueue.h
        Input/KeyInput.cpp
        Input/KeyInput.h
        Input/MouseInput.cpp Input/MouseInput.h IO/IModelLoader.cpp IO/IModelLoader.h IO/OBJLoader.cpp IO/OBJLoader.h Transformers/Interpreter/ILanInterpreter.cpp Transformers/Interpreter/ILanInterpreter.h Physics/Transform.cpp Physics/Transform.h IO/ModelData.h View/Renderer/3D/Vertices/Vertex.cpp View/Renderer/3D/Vertices/Vertex.h View/Renderer/3D/Vertices/Mesh.cpp View/Renderer/3D/Vertices/Mesh.h View/Renderer/3D/Object/Pyramid.cpp View/Renderer/3D/Object/Pyramid.h IO/IMG/ImageLoaders.cpp IO/IMG/ImageLoaders.h View/Renderer/3D/Texture/Texture.cpp View/Renderer/3D/Texture/Texture.h View/Renderer/3D/Texture/BMPTexture.cpp View/Renderer/3D/Texture/BMPTexture.h View/Renderer/3D/Light/Light.cpp View/Renderer/3D/Light/Light.h View/Renderer/3D/Light/PointLight.cpp View/Renderer/3D/Light/PointLight.h Sound/Sound.cpp Sound/Sound.h Sound/WAVSound.cpp Sound/WAVSound.h View/Renderer/3D/Light/DirectionalLight.cpp View/Renderer/3D/Light/DirectionalLight.h View/Renderer/3D/Object/Plane.cpp View/Renderer/3D/Object/Plane.h Utils/ColorSwitch.cpp Utils/ColorSwitch.h View/Renderer/3D/Particles/Particle.cpp View/Renderer/3D/Particles/Particle.h View/Renderer/3D/Texture/FrameBuffer/FrameBufferObject.cpp View/Renderer/3D/Texture/FrameBuffer/FrameBufferObject.h View/Renderer/3D/Texture/FrameBuffer/RenderedTexture.cpp View/Renderer/3D/Texture/FrameBuffer/RenderedTexture.h View/Renderer/3D/PostProcessing/ViewportSquare.cpp View/Renderer/3D/PostProcessing/ViewportSquare.h
        View/IWindow.cpp
        View/IWindow.h View/Windowing/MainWindow.cpp View/Windowing/MainWindow.h View/Windowing/RenderWin.cpp View/Windowing/RenderWin.h View/Renderer/OG33Renderer.cpp View/Renderer/OG33Renderer.h Output/ImGuiConsole/ImGuiOutput.cpp Output/ImGuiConsole/ImGuiOutput.h View/IMGUI/Own/CodeEditor.cpp View/IMGUI/Own/CodeEditor.h View/IMGUI/Own/Docking/DockSpace.cpp View/IMGUI/Own/Docking/DockSpace.h View/IMGUI/Own/IGuiElement.h View/IMGUI/Own/Docking/MainDockSpace.cpp View/IMGUI/Own/Docking/MainDockSpace.h View/IMGUI/Own/GuiConsole.cpp View/IMGUI/Own/GuiConsole.h View/IMGUI/Own/Main/EditorView.cpp View/IMGUI/Own/Main/EditorView.h View/IMGUI/Own/FileTree/FileTree.cpp View/IMGUI/Own/FileTree/FileTree.h)


# OS SPECIFICITIES
message("Compiling for : ")

if(OS STREQUAL "NT")
    list(APPEND SRC_FILES res.rc)
    message("Windows")
elseif(OS STREQUAL "UNIX")
    message("UNIX")
elseif(OS STREQUAL "MAC")
    list(APPEND SRC_FILES ../../src/osx/carbon/wxmac.icns)
    message("MacOS")
endif()

if(BITS MATCHES 64)
    message("64bits")
elseif(BITS MATCHES 32)
    message("32bits")
endif()

############ EXECUTABLE ############
add_executable(${PROJECT_NAME} ${SRC_FILES})
message("Done!")

message("Linking...")
############ LINK ############
### Specificities ###
if(OS STREQUAL "NT")
    target_link_libraries(${PROJECT_NAME} PUBLIC -lopengl32)
elseif(OS STREQUAL "UNIX")
    target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES})
endif()

### SDL 2 ###
message("Linking SDL2...")
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})
include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})

### LUA ###
message("Linking Lua...")
target_include_directories(${PROJECT_NAME} PUBLIC ${LUA_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LUA_LIBRARIES})

### GLEW ###
message("Linking GLEW...")
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLEW_LIBRARIES})
