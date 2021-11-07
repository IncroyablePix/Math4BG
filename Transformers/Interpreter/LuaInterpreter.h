//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_LUAINTERPRETER_H
#define ARCPOSITION_LUAINTERPRETER_H

#include <memory>
#include "../Contexts.h"
#include "../World/IWorld.h"
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

        void RegisterFunctions() override;

        int CallOnInitFunction() override;
        int CallUpdateFunction(double lag) override;

        //---

        int Print(lua_State *L);

        int CreateContext(lua_State *L);
        int DestroyWindow(lua_State *L);
        int SetBackgroundColor(lua_State *L);

        int CreateShader(lua_State *L);
        int CreateTexture(lua_State *L);
        int CreateModel(lua_State *L);

        int CreatePointLight(lua_State *L);
        int SetLightPos(lua_State *L);
        int SetLightColor(lua_State *L);

        int SetDirectionalLight(lua_State *L);
        int SetCameraPos(lua_State *L);
        int SetCameraRot(lua_State *L);

        //---

        int GetMillis(lua_State *L);

        //---

        int CreateCube(lua_State *L);
        int CreatePlane(lua_State *L);
        int CreatePyramid(lua_State *L);
        int CreateCustomObject(lua_State *L);

        int SetObjectColor(lua_State *L);
        int SetObjectPos(lua_State *L);
        int SetObjectPosOrigin(lua_State *L);
        int SetObjectOrigin(lua_State *L);
        int SetObjectRot(lua_State *L);
        int SetObjectScale(lua_State *L);
        int SetObjectTexture(lua_State *L);

        static std::unique_ptr<LuaInterpreter> Create(std::shared_ptr<Contexts> context, std::shared_ptr<IOutput> output);

    private:
        std::unique_ptr<lua_State, decltype(lua_close) *> m_luaState;
        bool CheckLua(int r);
        void ThrowLuaException();

        static float Col(uint32_t color);
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
