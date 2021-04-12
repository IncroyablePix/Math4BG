//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include <utility>
#include "LuaInterpreter.h"

LuaInterpreter::LuaInterpreter() :
m_luaState(nullptr, lua_close)
{
    m_luaState.reset(luaL_newstate());
    luaL_openlibs(m_luaState.get());

    RegisterFunctions();
}

LuaInterpreter::~LuaInterpreter()
= default;

void LuaInterpreter::Test()
{
    int r = luaL_dostring(m_luaState.get(), "a = 7 + 11");

    if(r == LUA_OK)
    {
        std::cout << r << std::endl;
    }
    else
    {
        std::string errormsg = lua_tostring(m_luaState.get(), -1);
    }
}

void LuaInterpreter::ExecuteCommand(const std::string &cmd)
{
    int out = luaL_dostring(m_luaState.get(), cmd.c_str());

    if(!CheckLua(out))
        ThrowLuaException();
}

void LuaInterpreter::ExecuteFile(const std::string &path)
{
    int out = luaL_dofile(m_luaState.get(), path.c_str());

    if(!CheckLua(out))
        ThrowLuaException();
}

bool LuaInterpreter::CheckValidity()
{
    unsigned int count = 0;
    char *functions[] = {"OnInit", "OnUpdate"};
    for(auto & function : functions)
    {
        lua_getglobal(m_luaState.get(), function);
        if(!lua_isfunction(m_luaState.get(), -1))
            return false;
    }

    return true;
}

int LuaInterpreter::CallUpdateFunction(const double lag)
{
    lua_getglobal(m_luaState.get(), "OnUpdate");
    if(lua_isfunction(m_luaState.get(), -1))
    {
        lua_pushnumber(m_luaState.get(), lag);

        int out = lua_pcall(m_luaState.get(), 1, 1, 0);
        if(!CheckLua(out))
            ThrowLuaException();

        return (int) lua_tonumber(m_luaState.get(), -1);
    }

    return -1;
}

int LuaInterpreter::CallOnInitFunction()
{
    lua_getglobal(m_luaState.get(), "OnInit");
    if(lua_isfunction(m_luaState.get(), -1))
    {
        int out = lua_pcall(m_luaState.get(), 0, 1, 0);
        if(!CheckLua(out))
            ThrowLuaException();

        return (int) lua_tonumber(m_luaState.get(), -1);
    }

    return -1;
}

double LuaInterpreter::GetNumber(const std::string &var)
{
    double val;

    lua_getglobal(m_luaState.get(), var.c_str());
    if(lua_isnumber(m_luaState.get(), -1))
    {
        val = lua_tonumber(m_luaState.get(), -1);
    }
    else
    {
        val = 0.0;
    }

    return val;
}

std::string LuaInterpreter::GetString(const std::string &var)
{
    std::string val;
    lua_getglobal(m_luaState.get(), var.c_str());
    if(lua_isstring(m_luaState.get(), -1))
    {
        val = lua_tostring(m_luaState.get(), -1);
    }
    else
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
    *static_cast<LuaInterpreter**>(lua_getextraspace(m_luaState.get())) = this;

    lua_register(m_luaState.get(), "SecondCallback", &dispatch<&LuaInterpreter::SecondCallback>);

    lua_register(m_luaState.get(), "CreateCircle", &dispatch<&LuaInterpreter::CreateCircle>);
    lua_register(m_luaState.get(), "SetCirclePos", &dispatch<&LuaInterpreter::SetCirclePos>);
    lua_register(m_luaState.get(), "SetCircleSize", &dispatch<&LuaInterpreter::SetCircleSize>);
    lua_register(m_luaState.get(), "SetCircleColor", &dispatch<&LuaInterpreter::SetCircleColor>);

    lua_register(m_luaState.get(), "CreateLine", &dispatch<&LuaInterpreter::CreateLine>);
    lua_register(m_luaState.get(), "SetLinePos", &dispatch<&LuaInterpreter::SetLinePos>);
    lua_register(m_luaState.get(), "SetLineColor", &dispatch<&LuaInterpreter::SetLineColor>);
}

void LuaInterpreter::SetWorld(std::shared_ptr<World> world)
{
    m_world = std::shared_ptr<World>(std::move(world));
}

int LuaInterpreter::CreateCircle(lua_State *L)
{
    double x = (double) lua_tonumber(L, 1);
    double y = (double) lua_tonumber(L, 2);
    double radius = (double) lua_tonumber(L, 3);
    unsigned int color = (unsigned int) lua_tonumber(L, 4);

    int id = m_world->CreateCircle({x, y}, radius, color);
    lua_pushnumber(L, id);
    return 1;
}

int LuaInterpreter::SetCirclePos(lua_State *L)
{
    int id = (int) lua_tonumber(L, 1);
    double x = (double) lua_tonumber(L, 2);
    double y = (double) lua_tonumber(L, 3);

    bool out = m_world->SetCirclePos(id, {x, y});
    lua_pushboolean(L, out);

    return 1;
}

int LuaInterpreter::SetCircleSize(lua_State *L)
{
    int id = (int) lua_tonumber(L, 1);
    double size = (double) lua_tonumber(L, 2);

    bool out = m_world->SetCircleSize(id, size);
    lua_pushboolean(L, out);

    return 1;
}

int LuaInterpreter::SetCircleColor(lua_State *L)
{
    int id = (int) lua_tonumber(L, 1);
    unsigned int color = (unsigned int) lua_tonumber(L, 2);

    bool out = m_world->SetCircleColor(id, color);
    lua_pushboolean(L, out);

    return 1;
}

int LuaInterpreter::CreateLine(lua_State *L)
{
    double xStart = (double) lua_tonumber(L, 1);
    double yStart = (double) lua_tonumber(L, 2);
    double xEnd = (double) lua_tonumber(L, 3);
    double yEnd = (double) lua_tonumber(L, 4);
    unsigned int color = (unsigned int) lua_tonumber(L, 5);

    int id = m_world->CreateLine({ xStart, yStart }, { xEnd, yEnd }, color);
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

    bool out = m_world->SetLinePos(id, { xStart, yStart }, { xEnd, yEnd });
    lua_pushboolean(L, out);
    return 1;
}

int LuaInterpreter::SetLineColor(lua_State *L)
{
    int id = (int) lua_tonumber(L, 1);
    unsigned int color = (unsigned int) lua_tonumber(L, 2);

    bool out = m_world->SetLineColor(id, color);
    lua_pushboolean(L, out);
    return 1;
}
