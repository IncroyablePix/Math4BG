cmake_minimum_required(VERSION 3.17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
project(ArcPosition)

set(CMAKE_CXX_STANDARD 17)
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

############ FICHIERS ############
set(SRC_FILES
        Program/main.cpp
        View/Window.cpp
        View/Window.h
        View/Screen.cpp
        View/Screen.h
        View/Renderer.cpp
        View/Renderer.h
        Transformers/Logic.cpp
        Transformers/Logic.h
        Program/Application.cpp
        Program/Application.h
        Transformers/Shapes.cpp
        Transformers/Shapes.h Transformers/LuaInterpreter.cpp Transformers/LuaInterpreter.h Program/Config/Config.cpp Program/Config/Config.h Transformers/World.cpp Transformers/World.h View/Error.cpp View/Error.h Transformers/MainManager.cpp Transformers/MainManager.h Transformers/Context.cpp Transformers/Context.h Transformers/Contexts.cpp Transformers/Contexts.h)

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
### SDL 2 ###
message("Linking SDL2...")
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_DIR}/x86_64-w64-mingw32/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_DIR}/x86_64-w64-mingw32/bin/SDL2.dll)

### LUA ###
message("Linking Lua...")
target_include_directories(${PROJECT_NAME} PUBLIC ${LUA_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LUA_DIR}/lua54.dll)

message("Done!")