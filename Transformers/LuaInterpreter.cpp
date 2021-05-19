//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include <utility>
#include "LuaInterpreter.h"
#include "../Output/IOutput.h"

namespace Math4BG
{
    LuaInterpreter::LuaInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output) :
            m_luaState(nullptr, lua_close),
            m_output(std::move(output))
    {
        m_contexts = std::shared_ptr<Contexts>(std::move(contexts));
        m_luaState.reset(luaL_newstate());
        luaL_openlibs(m_luaState.get());

        RegisterFunctions();
    }

    LuaInterpreter::~LuaInterpreter()
    = default;

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

    bool LuaInterpreter::CheckValidity()
    {
        unsigned int count = 0;
        char *functions[] = {"OnInit", "OnUpdate"};
        for (auto &function : functions)
        {
            lua_getglobal(m_luaState.get(), function);
            if (!lua_isfunction(m_luaState.get(), -1))
                return false;
        }

        return true;
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
        throw std::runtime_error(error);
    }

    int LuaInterpreter::SecondCallback(lua_State *L)
    {
        std::cout << "coucou" << std::endl;
        return 0;
    }

    void LuaInterpreter::RegisterFunctions()
    {
        *static_cast<LuaInterpreter **>(lua_getextraspace(m_luaState.get())) = this;

        lua_register(m_luaState.get(), "SecondCallback", &dispatch<&LuaInterpreter::SecondCallback>);

        lua_register(m_luaState.get(), "CreateCircle", &dispatch<&LuaInterpreter::CreateCircle>);
        lua_register(m_luaState.get(), "SetCirclePos", &dispatch<&LuaInterpreter::SetCirclePos>);
        lua_register(m_luaState.get(), "SetCircleSize", &dispatch<&LuaInterpreter::SetCircleSize>);
        lua_register(m_luaState.get(), "SetCircleColor", &dispatch<&LuaInterpreter::SetCircleColor>);

        lua_register(m_luaState.get(), "CreateLine", &dispatch<&LuaInterpreter::CreateLine>);
        lua_register(m_luaState.get(), "SetLinePos", &dispatch<&LuaInterpreter::SetLinePos>);
        lua_register(m_luaState.get(), "SetLineColor", &dispatch<&LuaInterpreter::SetLineColor>);

        lua_register(m_luaState.get(), "CreateDot", &dispatch<&LuaInterpreter::CreateDot>);
        lua_register(m_luaState.get(), "SetDotPos", &dispatch<&LuaInterpreter::SetDotPos>);
        lua_register(m_luaState.get(), "SetDotColor", &dispatch<&LuaInterpreter::SetDotColor>);

        lua_register(m_luaState.get(), "CreateRectangle", &dispatch<&LuaInterpreter::CreateRectangle>);
        lua_register(m_luaState.get(), "SetRectanglePos", &dispatch<&LuaInterpreter::SetRectanglePos>);
        lua_register(m_luaState.get(), "SetRectangleDimens", &dispatch<&LuaInterpreter::SetRectangleDimens>);
        lua_register(m_luaState.get(), "SetRectangleColor", &dispatch<&LuaInterpreter::SetRectangleColor>);

        lua_register(m_luaState.get(), "CreateCube", &dispatch<&LuaInterpreter::CreateCube>);

        lua_register(m_luaState.get(), "CreateShader", &dispatch<&LuaInterpreter::CreateShader>);

        lua_register(m_luaState.get(), "CreateWindow", &dispatch<&LuaInterpreter::CreateWindow>);
        lua_register(m_luaState.get(), "SetBackgroundColor", &dispatch<&LuaInterpreter::SetBackgroundColor>);
    }

/*void LuaInterpreter::SetWorld(std::shared_ptr<World> world)
{
    m_world = std::shared_ptr<World>(std::move(world));
}*/

    int LuaInterpreter::CreateWindow(lua_State *L)
    {
        std::string title = lua_tostring(L, 1);
        unsigned int width = lua_tonumber(L, 2);
        unsigned int height = lua_tonumber(L, 3);
        uint32_t type = lua_tonumber(L, 4);

        *m_output << "Creating window : " << title << std::endl;

        int id = m_contexts->CreateContext({title, width, height}, (WorldType) type);
        lua_pushnumber(L, id);
        return 1;
    }

    int LuaInterpreter::DestroyWindow(lua_State *L)
    {
        return 0;
    }

    int LuaInterpreter::CreateShader(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        std::string file = lua_tostring(L, 2);

        std::string name = "";

        if(m_contexts->ContextExists(contextid))
            name = ((*m_contexts)[contextid])->GetWorld()->CreateShader(file);

        lua_pushstring(L, name.c_str());

        return 1;
    }

    int LuaInterpreter::CreateCircle(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        double x = (double) lua_tonumber(L, 2);
        double y = (double) lua_tonumber(L, 3);
        double radius = (double) lua_tonumber(L, 4);
        unsigned int color = (unsigned int) lua_tonumber(L, 5);

        int id = -1;
        if (m_contexts->ContextExists(contextid))
            id = ((*m_contexts)[contextid])->GetWorld()->CreateCircle({x, y}, radius, color);

        lua_pushnumber(L, id);

        return 1;
    }

    int LuaInterpreter::SetCirclePos(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        double x = (double) lua_tonumber(L, 2);
        double y = (double) lua_tonumber(L, 3);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetCirclePos(id, {x, y});
        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetCircleSize(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        double size = (double) lua_tonumber(L, 2);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetCircleSize(id, size);
        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetCircleColor(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetCircleColor(id, color);
        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::CreateLine(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        double xStart = (double) lua_tonumber(L, 2);
        double yStart = (double) lua_tonumber(L, 3);
        double xEnd = (double) lua_tonumber(L, 4);
        double yEnd = (double) lua_tonumber(L, 5);
        unsigned int color = (unsigned int) lua_tonumber(L, 6);

        int id = -1;
        if (m_contexts->ContextExists(contextid))
            id = ((*m_contexts)[contextid])->GetWorld()->CreateLine({xStart, yStart}, {xEnd, yEnd}, color);

        lua_pushnumber(L, id);
        return 1;
    }

    int LuaInterpreter::SetLinePos(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        double xStart = (double) lua_tonumber(L, 2);
        double yStart = (double) lua_tonumber(L, 3);
        double xEnd = (double) lua_tonumber(L, 4);
        double yEnd = (double) lua_tonumber(L, 5);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetLinePos(id, {xStart, yStart}, {xEnd, yEnd});
        lua_pushboolean(L, out);
        return 1;
    }

    int LuaInterpreter::SetLineColor(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetLineColor(id, color);
        lua_pushboolean(L, out);
        return 1;
    }

    int LuaInterpreter::SetBackgroundColor(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        ((*m_contexts)[contextid])->GetWorld()->SetBackgroundColor(color);
        return 0;
    }

    int LuaInterpreter::CreateDot(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        double x = (double) lua_tonumber(L, 2);
        double y = (double) lua_tonumber(L, 3);
        unsigned int color = (int) lua_tonumber(L, 4);

        ((*m_contexts)[contextid])->GetWorld()->CreateDot({ x, y }, color);
        return 1;
    }

    int LuaInterpreter::SetDotPos(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        double x = (double) lua_tonumber(L, 2);
        double y = (double) lua_tonumber(L, 3);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetDotPos(id, {x, y});
        lua_pushboolean(L, out);
        return 1;
    }

    int LuaInterpreter::SetDotColor(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetDotColor(id, color);
        lua_pushboolean(L, out);
        return 1;
    }

    int LuaInterpreter::CreateRectangle(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        double x = (double) lua_tonumber(L, 2);
        double y = (double) lua_tonumber(L, 3);
        double width = (double) lua_tonumber(L, 4);
        double height = (double) lua_tonumber(L, 5);
        unsigned int color = (unsigned int) lua_tonumber(L, 6);

        int id = -1;
        if (m_contexts->ContextExists(contextid))
            id = ((*m_contexts)[contextid])->GetWorld()->CreateRectangle({x, y}, width, height, color);

        lua_pushnumber(L, id);

        return 1;
    }

    int LuaInterpreter::SetRectanglePos(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        double x = (double) lua_tonumber(L, 2);
        double y = (double) lua_tonumber(L, 3);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetRectanglePos(id, { x, y });
        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetRectangleDimens(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        double width = (double) lua_tonumber(L, 2);
        double height = (double) lua_tonumber(L, 3);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetRectangleDimens(id, width, height);
        lua_pushboolean(L, out);
        return 1;
    }

    int LuaInterpreter::SetRectangleColor(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        bool out = m_contexts->GetWorldForId(id)->GetWorld()->SetRectangleColor(id, color);
        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::CreateCube(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        std::string shaderName = lua_tostring(L, 2);
        /*double x = (double) lua_tonumber(L, 2);
        double y = (double) lua_tonumber(L, 3);
        double width = (double) lua_tonumber(L, 4);
        double height = (double) lua_tonumber(L, 5);*/
        //unsigned int color = (unsigned int) lua_tonumber(L, 5);

        int id = -1;
        if (m_contexts->ContextExists(contextid))
            id = ((*m_contexts)[contextid])->GetWorld()->CreateCube(shaderName);

        lua_pushnumber(L, id);

        return 1;
    }
}