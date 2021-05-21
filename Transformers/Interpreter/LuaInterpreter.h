//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_LUAINTERPRETER_H
#define ARCPOSITION_LUAINTERPRETER_H

#include <memory>
#include "../Contexts.h"
#include "../World.h"
#include "../../Output/IOutput.h"
#include "ILanInterpreter.h"
/**
 * Lua is a C library thus having C defined functions
 */
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
};


namespace Math4BG
{
    class LuaInterpreter : public ILanInterpreter
    {
    public:
        LuaInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output);
        ~LuaInterpreter() override = default;

        void ExecuteCommand(const std::string &cmd);
        void ExecuteFile(const std::string &path) override;
        double GetNumber(const std::string &var);
        std::string GetString(const std::string &var);
        bool GetBool(const std::string &var);
        bool CheckValidity() override;

        void RegisterFunctions() override;

        int CallOnInitFunction() override;
        int CallUpdateFunction(double lag) override;
        int CallOnWindowClosed(int windowId) override;

        //---

        int CreateWindow(lua_State *L);
        int DestroyWindow(lua_State *L);
        int SetBackgroundColor(lua_State *L);

        int CreateShader(lua_State *L);
        int CreateModel(lua_State *L);

        //---

        int GetMillis(lua_State *L);

        //---

        int CreateCircle(lua_State *L);
        int SetCirclePos(lua_State *L);
        int SetCircleSize(lua_State *L);
        int SetCircleColor(lua_State *L);

        int CreateLine(lua_State *L);
        int SetLinePos(lua_State *L);
        int SetLineColor(lua_State *L);

        int CreateDot(lua_State *L);
        int SetDotPos(lua_State *L);
        int SetDotColor(lua_State *L);

        int CreateRectangle(lua_State *L);
        int SetRectanglePos(lua_State *L);
        int SetRectangleDimens(lua_State *L);
        int SetRectangleColor(lua_State *L);

        //---

        int CreateCube(lua_State *L);
        int CreatePyramid(lua_State *L);
        int SetObjectPos(lua_State *L);
        int SetObjectPosOrigin(lua_State *L);
        int SetObjectOrigin(lua_State *L);
        int SetObjectRot(lua_State *L);
        int SetObjectScale(lua_State *L);

        int CreateCustomObject(lua_State *L);


        static std::shared_ptr<LuaInterpreter> Create(std::shared_ptr<Contexts> context, std::shared_ptr<IOutput> output);

    private:
        std::unique_ptr<lua_State, decltype(lua_close) *> m_luaState;
        bool CheckLua(int r);
        void ThrowLuaException();
    };

    typedef int (LuaInterpreter::*mem_func)(lua_State *L);

// This template wraps a member function into a C-style "free" function compatible with lua.
    template<mem_func func>
    int dispatch(lua_State *L)
    {
        LuaInterpreter *ptr = *static_cast<LuaInterpreter **>(lua_getextraspace(L));
        return ((*ptr).*func)(L);
    }
}

#endif //ARCPOSITION_LUAINTERPRETER_H
