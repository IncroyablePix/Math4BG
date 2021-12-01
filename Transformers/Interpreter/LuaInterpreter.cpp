//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include <utility>
#include <chrono>
#include "LuaInterpreter.h"
#include "../../Output/IOutput.h"
#include "CodeException.h"

namespace Math4BG
{
    LuaInterpreter::LuaInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output) :
            m_luaState(nullptr, lua_close),
            ILanInterpreter(std::move(contexts), std::move(output))
    {
        m_luaState.reset(luaL_newstate());
        luaL_openlibs(m_luaState.get());

        RegisterFunctions();
    }

    void LuaInterpreter::ExecuteCommand(const std::string &cmd)
    {
        int out = luaL_dostring(m_luaState.get(), cmd.c_str());

        if (!CheckLua(out))
            ThrowLuaException();
    }

    void LuaInterpreter::ExecuteFile(const std::string &path)
    {
        int out = luaL_dofile(m_luaState.get(), path.c_str());

        if (!CheckLua(out))
            ThrowLuaException();
    }

    int LuaInterpreter::CallUpdateFunction(const double lag)
    {
        lua_getglobal(m_luaState.get(), "OnUpdate");
        if (lua_isfunction(m_luaState.get(), -1))
        {
            lua_pushnumber(m_luaState.get(), lag);

            int out = lua_pcall(m_luaState.get(), 1, 1, 0);
            if (!CheckLua(out))
                ThrowLuaException();

            return (int) lua_tonumber(m_luaState.get(), -1);
        }
        /*else
        {
            throw CodeException("Could not find \"OnUpdate\" function");
        }*/

        return -1;
    }

    int LuaInterpreter::CallOnInitFunction()
    {
        lua_getglobal(m_luaState.get(), "OnInit");
        if (lua_isfunction(m_luaState.get(), -1))
        {
            int out = lua_pcall(m_luaState.get(), 0, 1, 0);
            if (!CheckLua(out))
                ThrowLuaException();

            return (int) lua_tonumber(m_luaState.get(), -1);
        }
        else
        {
            throw CodeException("Could not find \"OnInit\" function");
        }

        return -1;
    }

    double LuaInterpreter::GetNumber(const std::string &var)
    {
        double val;

        lua_getglobal(m_luaState.get(), var.c_str());
        if (lua_isnumber(m_luaState.get(), -1))
        {
            val = lua_tonumber(m_luaState.get(), -1);
        } else
        {
            val = 0.0;
        }

        return val;
    }

    std::string LuaInterpreter::GetString(const std::string &var)
    {
        std::string val;
        lua_getglobal(m_luaState.get(), var.c_str());
        if (lua_isstring(m_luaState.get(), -1))
        {
            val = lua_tostring(m_luaState.get(), -1);
        } else
        {
            val = "";
        }

        return val;
    }

    bool LuaInterpreter::GetBool(const std::string &var)
    {
        bool val;
        lua_getglobal(m_luaState.get(), var.c_str());
        if (lua_isboolean(m_luaState.get(), -1))
        {
            val = lua_toboolean(m_luaState.get(), -1);
        } else
        {
            val = "";
        }

        return val;
    }

    bool LuaInterpreter::CheckLua(int r)
    {
        return (r == LUA_OK);
    }

    void LuaInterpreter::ThrowLuaException()
    {
        std::string error = lua_tostring(m_luaState.get(), -1);
        throw CodeException(error);
    }

    void LuaInterpreter::RegisterFunctions()
    {
        *static_cast<LuaInterpreter **>(lua_getextraspace(m_luaState.get())) = this;

        lua_register(m_luaState.get(), "print", &dispatch<&LuaInterpreter::Print>);

        lua_register(m_luaState.get(), "CreateCube", &dispatch<&LuaInterpreter::CreateCube>);
        lua_register(m_luaState.get(), "CreatePlane", &dispatch<&LuaInterpreter::CreatePlane>);
        lua_register(m_luaState.get(), "CreatePyramid", &dispatch<&LuaInterpreter::CreatePyramid>);

        lua_register(m_luaState.get(), "SetObjectPos", &dispatch<&LuaInterpreter::SetObjectPos>);
        lua_register(m_luaState.get(), "SetObjectColor", &dispatch<&LuaInterpreter::SetObjectColor>);
        lua_register(m_luaState.get(), "SetObjectPosOrigin", &dispatch<&LuaInterpreter::SetObjectPosOrigin>);
        lua_register(m_luaState.get(), "SetObjectOrigin", &dispatch<&LuaInterpreter::SetObjectOrigin>);
        lua_register(m_luaState.get(), "SetObjectRot", &dispatch<&LuaInterpreter::SetObjectRot>);
        lua_register(m_luaState.get(), "SetObjectScale", &dispatch<&LuaInterpreter::SetObjectScale>);
        lua_register(m_luaState.get(), "SetObjectTexture", &dispatch<&LuaInterpreter::SetObjectTexture>);

        lua_register(m_luaState.get(), "CreateCustomObject", &dispatch<&LuaInterpreter::CreateCustomObject>);

        lua_register(m_luaState.get(), "CreateShader", &dispatch<&LuaInterpreter::CreateShader>);
        lua_register(m_luaState.get(), "CreateModel", &dispatch<&LuaInterpreter::CreateModel>);
        lua_register(m_luaState.get(), "CreateTexture", &dispatch<&LuaInterpreter::CreateTexture>);

        lua_register(m_luaState.get(), "CreateContext", &dispatch<&LuaInterpreter::CreateContext>);
        lua_register(m_luaState.get(), "SetBackgroundColor", &dispatch<&LuaInterpreter::SetBackgroundColor>);

        lua_register(m_luaState.get(), "SetCameraPos", &dispatch<&LuaInterpreter::SetCameraPos>);
        lua_register(m_luaState.get(), "SetCameraRot", &dispatch<&LuaInterpreter::SetCameraRot>);

        lua_register(m_luaState.get(), "SetDirectionalLight", &dispatch<&LuaInterpreter::SetDirectionalLight>);

        lua_register(m_luaState.get(), "CreatePointLight", &dispatch<&LuaInterpreter::CreatePointLight>);
        lua_register(m_luaState.get(), "SetLightPos", &dispatch<&LuaInterpreter::SetLightPos>);
        lua_register(m_luaState.get(), "SetLightColor", &dispatch<&LuaInterpreter::SetLightColor>);

        lua_register(m_luaState.get(), "GetMillis", &dispatch<&LuaInterpreter::GetMillis>);
    }

    int LuaInterpreter::Print(lua_State *L)
    {
        int nargs = lua_gettop(L);
        std::stringstream ss;

        for (int i = 1; i <= nargs; i++)
        {
            if (lua_isstring(L, i))
                ss << lua_tostring(L, i);
            else if(lua_isnumber(L, i))
                ss << lua_tonumber(L, i);
        }

        PrintImplementation(ss.str());

        return 0;
    }

/*void LuaInterpreter::SetWorld(std::shared_ptr<IWorld> world)
{
    m_world = std::shared_ptr<IWorld>(std::move(world));
}*/

    int LuaInterpreter::CreateContext(lua_State *L)
    {
        std::string title = lua_tostring(L, 1);
        unsigned int width = lua_tonumber(L, 2);
        unsigned int height = lua_tonumber(L, 3);
        bool abstract = lua_toboolean(L, 4);

        lua_pushnumber(L, CreateContextImplementation(title, width, height, abstract));
        return 1;
    }

    int LuaInterpreter::SetCameraPos(lua_State *L)
    {
        int contextid = lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        SetCameraPosImplementation(contextid, x, y, z);

        return 1;
    }

    int LuaInterpreter::SetCameraRot(lua_State *L)
    {
        int contextid = lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);

        SetCameraRotImplementation(contextid, x, y);

        return 1;
    }

    int LuaInterpreter::CreateShader(lua_State *L)
    {
        std::string file = lua_tostring(L, 1);

        lua_pushstring(L, CreateShaderImplementation(file).c_str());

        return 1;
    }

    int LuaInterpreter::CreateTexture(lua_State *L)
    {
        std::string file = lua_tostring(L, 1);
        std::string name = lua_tostring(L, 2);

        lua_pushboolean(L, CreateTextureImplementation(file, name));

        return 1;
    }

    int LuaInterpreter::CreateModel(lua_State *L)
    {
        std::string file = lua_tostring(L, 1);
        std::string name = lua_tostring(L, 2);

        lua_pushboolean(L, CreateModelImplementation(file, name));

        return 1;
    }

    int LuaInterpreter::GetMillis(lua_State *L)
    {
        lua_pushnumber(L, GetMillisImplementation());
        return 1;
    }

    int LuaInterpreter::SetBackgroundColor(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        SetBackgroundColorImplementation(contextid, color);

        return 0;
    }

    int LuaInterpreter::CreateCube(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        std::string shaderName = lua_tostring(L, 2);
        float x = (float) lua_tonumber(L, 3);
        float y = (float) lua_tonumber(L, 4);
        float z = (float) lua_tonumber(L, 5);

        lua_pushnumber(L, CreateCubeImplementation(contextid, shaderName, x, y, z));

        return 1;
    }

    int LuaInterpreter::CreatePlane(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        std::string shaderName;
        try
        {
            shaderName = lua_tostring(L, 2);
        }
        catch(const std::logic_error& e)
        {
            shaderName = "";
        }
        float x = (float) lua_tonumber(L, 3);
        float y = (float) lua_tonumber(L, 4);
        float z = (float) lua_tonumber(L, 5);

        lua_pushnumber(L, CreatePlaneImplementation(contextid, shaderName, x, y, z));

        return 1;
    }

    int LuaInterpreter::CreatePyramid(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        std::string shaderName = lua_tostring(L, 2);
        float x = (float) lua_tonumber(L, 3);
        float y = (float) lua_tonumber(L, 4);
        float z = (float) lua_tonumber(L, 5);

        //unsigned int color = (unsigned int) lua_tonumber(L, 5);
        lua_pushnumber(L, CreatePyramidImplementation(contextid, shaderName, x, y, z));

        return 1;
    }

    int LuaInterpreter::CreateCustomObject(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        std::string shaderName = lua_tostring(L, 2);
        std::string modelName = lua_tostring(L, 3);
        float x = (float) lua_tonumber(L, 4);
        float y = (float) lua_tonumber(L, 5);
        float z = (float) lua_tonumber(L, 6);

        lua_pushnumber(L, CreateCustomObjectImplementation(contextid, shaderName, modelName, x, y, z));

        return 1;
    }

    int LuaInterpreter::SetObjectPos(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        lua_pushboolean(L, SetObjectPosImplementation(id, x, y, z));

        return 1;
    }

    int LuaInterpreter::SetObjectRot(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        lua_pushboolean(L, SetObjectRotImplementation(id, x, y, z));

        return 1;
    }

    int LuaInterpreter::SetObjectScale(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        lua_pushboolean(L, SetObjectScaleImplementation(id, x, y, z));

        return 1;
    }

    int LuaInterpreter::SetObjectPosOrigin(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        lua_pushboolean(L, SetObjectPosOriginImplementation(id, x, y, z));

        return 1;
    }

    int LuaInterpreter::SetObjectOrigin(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        lua_pushboolean(L, SetObjectOriginImplementation(id, x, y, z));

        return 1;
    }

    int LuaInterpreter::SetObjectTexture(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        std::string name = lua_tostring(L, 2);

        lua_pushboolean(L, SetObjectTextureImplementation(id, name));

        return 1;
    }

    int LuaInterpreter::SetObjectColor(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        lua_pushboolean(L, SetObjectColorImplementation(id, color));

        return 1;
    }

    std::unique_ptr<LuaInterpreter>LuaInterpreter::Create(std::shared_ptr<Contexts> context, std::shared_ptr<IOutput> output)
    {
        return std::make_unique<LuaInterpreter>(context, output);
    }

    int LuaInterpreter::SetDirectionalLight(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);
        float intensity = (float) lua_tonumber(L, 5);
        unsigned int color = (unsigned int) lua_tonumber(L, 6);

        lua_pushboolean(L, SetDirectionalLightImplementation(contextid, x, y, z, intensity, color));

        return 1;
    }

    int LuaInterpreter::CreatePointLight(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        float intensity = (float) lua_tonumber(L, 2);
        unsigned int color = (unsigned int) lua_tonumber(L, 3);
        float x = (float) lua_tonumber(L, 4);
        float y = (float) lua_tonumber(L, 5);
        float z = (float) lua_tonumber(L, 6);

        lua_pushnumber(L, CreatePointLightImplementation(contextid, intensity, color, x, y, z));

        return 1;
    }

    int LuaInterpreter::SetLightPos(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        lua_pushboolean(L, SetLightPosImplementation(id, x, y, z));

        return 1;
    }

    int LuaInterpreter::SetLightColor(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        lua_pushboolean(L, SetLightColorImplementation(id, color));

        return 1;
    }

    float LuaInterpreter::Col(uint32_t color)
    {
        return ((float) color) / 0xFF;
    }
}