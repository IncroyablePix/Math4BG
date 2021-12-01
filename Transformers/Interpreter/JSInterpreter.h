//
// Created by Benjam on 11/30/2021.
//

#ifndef MATH4BG_JSINTERPRETER_H
#define MATH4BG_JSINTERPRETER_H


#include "ILanInterpreter.h"
#include <quickjs/quickjs.h>
#include <quickjs/quickjs-libc.h>

namespace Math4BG
{
    class JSInterpreter : public ILanInterpreter
    {
    public:
        JSInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output);
        ~JSInterpreter() override = default;
        int CallOnInitFunction() override;
        int CallUpdateFunction(double lag) override;
        void ExecuteFile(const std::string &path) override;
        void RegisterFunctions() override;

        void CreateContext();

        static std::unique_ptr<JSInterpreter> Create(std::shared_ptr<Contexts> context, std::shared_ptr<IOutput> output);

    private:
        //std::unique_ptr<lua_State, decltype(lua_close) *> m_luaState;
        std::unique_ptr<JSRuntime, decltype(JS_FreeRuntime)*> m_runTime;
        std::unique_ptr<JSContext, decltype(JS_FreeContext)*> m_jsContext;
        static JSContext* CustomJsContext(JSRuntime* runtime);
        inline static std::unordered_map<int, void*> magicMap;
        int m_instanceNumber;
        /*void ExecuteCommand(const std::string &cmd);
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

        static float Col(uint32_t color);*/
        static int magicCount;
    };

}


#endif //MATH4BG_JSINTERPRETER_H
