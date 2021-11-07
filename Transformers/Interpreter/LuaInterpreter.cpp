//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include <utility>
#include <chrono>
#include "LuaInterpreter.h"
#include "../../Output/IOutput.h"
#include "../../Utils/ColorSwitch.h"
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
        std::cout << ss.str() << std::endl;
        *m_output << ss.str();

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

        //*m_output << "Creating window : " << title << std::endl;

        int id = m_contexts->CreateContext({title, width, height}, abstract);
        lua_pushnumber(L, id);
        return 1;
    }

    int LuaInterpreter::SetCameraPos(lua_State *L)
    {
        int contextid = lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);


        if(m_contexts->ContextExists(contextid))
            ((*m_contexts)[contextid])->GetWorld()->SetCameraPos({x, y, z});

        return 1;
    }

    int LuaInterpreter::SetCameraRot(lua_State *L)
    {
        int contextid = lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);


        if(m_contexts->ContextExists(contextid))
            ((*m_contexts)[contextid])->GetWorld()->SetCameraRot({x, y});

        return 1;
    }

    int LuaInterpreter::DestroyWindow(lua_State *L)
    {
        return 0;
    }

    int LuaInterpreter::CreateShader(lua_State *L)
    {
        std::string file = lua_tostring(L, 1);

        std::string name = "";

        name = m_contexts->CreateShader(file);
        //if (m_contexts->ContextExists(contextid))
            //name = ((*m_contexts)[contextid])->GetWorld()->CreateShader(file);

        lua_pushstring(L, name.c_str());

        return 1;
    }

    int LuaInterpreter::CreateTexture(lua_State *L)
    {
        std::string file = lua_tostring(L, 1);
        std::string name = lua_tostring(L, 2);

        bool out = m_contexts->LoadTexture(file, name);

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::GetMillis(lua_State *L)
    {
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
        auto now = ms.count();

        lua_pushnumber(L, now);
        return 1;
    }

    int LuaInterpreter::CreateModel(lua_State *L)
    {
        std::string file = lua_tostring(L, 1);
        std::string name = lua_tostring(L, 2);

        bool out = m_contexts->LoadModel(file, name);

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetBackgroundColor(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        /*float r = (float) lua_tonumber(L, 2);
        float g = (float) lua_tonumber(L, 3);
        float b = (float) lua_tonumber(L, 4);*/
        unsigned int color = (unsigned int) lua_tonumber(L, 2);

        //unsigned int color = (int) r * 0xFF

        ((*m_contexts)[contextid])->GetWorld()->SetBackgroundColor(color);
        return 0;
    }

    int LuaInterpreter::CreateCube(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        std::string shaderName = lua_tostring(L, 2);
        float x = (float) lua_tonumber(L, 3);
        float y = (float) lua_tonumber(L, 4);
        float z = (float) lua_tonumber(L, 5);

        Transform transform = {{x, y, z}};

        int id = -1;

        std::shared_ptr<Shader> shader = m_contexts->GetShaderByName(shaderName);

        if (m_contexts->ContextExists(contextid))
        {
            id = ((*m_contexts)[contextid])->GetWorld()->CreateCube(shader, transform);
            m_contexts->SetWorldForObjectId(id, contextid);
        }
        lua_pushnumber(L, id);

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

        Transform transform = {{x, y, z}};

        int id = -1;

        std::shared_ptr<Shader> shader = m_contexts->GetShaderByName(shaderName);

        if (m_contexts->ContextExists(contextid))
        {
            id = ((*m_contexts)[contextid])->GetWorld()->CreatePlane(shader, transform);
            m_contexts->SetWorldForObjectId(id, contextid);
        }

        lua_pushnumber(L, id);

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
        Transform transform = {{x, y, z}};

        int id = -1;

        std::shared_ptr<Shader> shader = m_contexts->GetShaderByName(shaderName);

        if (m_contexts->ContextExists(contextid))
        {
            id = ((*m_contexts)[contextid])->GetWorld()->CreatePyramid(shader, transform);
            m_contexts->SetWorldForObjectId(id, contextid);
        }

        lua_pushnumber(L, id);

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

        //unsigned int color = (unsigned int) lua_tonumber(L, 5);
        Transform transform({ x, y, z }, { x, y, z }, { 0.0, 0.0, 0.0 }, {1.0f, 1.0f, 1.0f});

        int id = -1;
        if(m_contexts->ModelExists(modelName))
        {
            auto model = ((*m_contexts)[modelName]);

            std::shared_ptr<Shader> shader = m_contexts->GetShaderByName(shaderName);

            if (m_contexts->ContextExists(contextid))
            {
                id = ((*m_contexts)[contextid])->GetWorld()->CreateCustomObject(model, shader, transform);
                m_contexts->SetWorldForObjectId(id, contextid);
            }
        }

        lua_pushnumber(L, id);

        return 1;
    }

    int LuaInterpreter::SetObjectPos(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        bool out = false;

        if (m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectPos(id, {x, y, z});

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetObjectRot(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        bool out = false;

        if (m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectRot(id, {x, y, z});

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetObjectScale(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        bool out = false;

        if (m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectScale(id, {x, y, z});

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetObjectPosOrigin(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        bool out = false;

        if (m_contexts->GetWorldForId(id))
        {
            auto world = m_contexts->GetWorldForId(id)->GetWorld();
            out = world->SetObjectPosOrigin(id, {x, y, z});
        }

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetObjectOrigin(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        bool out = false;

        if (m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectOrigin(id, {x, y, z});

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetObjectTexture(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        std::string name = lua_tostring(L, 2);

        bool out = false;

        if (m_contexts->TextureExists(name))
        {
            std::shared_ptr<Texture> texture = m_contexts->GetTextureByName(name);

            if (m_contexts->GetWorldForId(id))
                out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectTexture(id, texture);
        }
        else
        {
            std::stringstream ss;
            ss << "Texture \"" << name << "\" not found!";
            *m_output << ss.str();
        }

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::SetObjectColor(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);
        /*float r = (float) lua_tonumber(L, 2);
        float g = (float) lua_tonumber(L, 3);
        float b = (float) lua_tonumber(L, 4);*/

        bool out = false;

        glm::vec4 vectorizedColor(MaskToFloat(color), 1.0f);

        std::shared_ptr<Context> context = m_contexts->GetWorldForId(id);
        if(context)
            out = context->GetWorld()->SetObjectColor(id, vectorizedColor);


        return out;
    }

    std::unique_ptr<LuaInterpreter>LuaInterpreter::Create(std::shared_ptr<Contexts> context, std::shared_ptr<IOutput> output)
    {
        return std::make_unique<LuaInterpreter>(context, output);
        //return std::shared_ptr<LuaInterpreter>(static_cast<LuaInterpreter *>(new LuaInterpreter(context, output)));
    }

    int LuaInterpreter::SetDirectionalLight(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);
        float intensity = (float) lua_tonumber(L, 5);
        unsigned int color = (unsigned int) lua_tonumber(L, 6);
        /*float r = (float) lua_tonumber(L, 6);
        float g = (float) lua_tonumber(L, 7);
        float b = (float) lua_tonumber(L, 8);*/

        bool out = false;

        if (m_contexts->ContextExists(contextid))
            out = ((*m_contexts)[contextid])->GetWorld()->SetDirectionalLight(intensity, {x, y, z}, MaskToFloat(color));

        lua_pushboolean(L, out);

        return 1;
    }

    int LuaInterpreter::CreatePointLight(lua_State *L)
    {
        int contextid = (int) lua_tonumber(L, 1);
        float intensity = (float) lua_tonumber(L, 2);
        unsigned int color = (unsigned int) lua_tonumber(L, 3);
        /*float r = (float) lua_tonumber(L, 3);
        float g = (float) lua_tonumber(L, 4);
        float b = (float) lua_tonumber(L, 5);*/
        float x = (float) lua_tonumber(L, 4);
        float y = (float) lua_tonumber(L, 5);
        float z = (float) lua_tonumber(L, 6);

        //unsigned int color = (unsigned int) lua_tonumber(L, 5);
        Transform transform({ x, y, z }, { x, y, z }, { 0.0, 0.0, 0.0 }, {1.0f, 1.0f, 1.0f});
        //glm::vec3 color(r, g, b);

        int id = -1;
        if (m_contexts->ContextExists(contextid))
            id = ((*m_contexts)[contextid])->GetWorld()->CreatePointLight(intensity, MaskToFloat(color), transform);

        lua_pushnumber(L, id);

        return 1;
    }

    int LuaInterpreter::SetLightPos(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        float x = (float) lua_tonumber(L, 2);
        float y = (float) lua_tonumber(L, 3);
        float z = (float) lua_tonumber(L, 4);

        bool out = false;

        if(m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetLightPos(id, {x, y, z});

        return out;
    }

    int LuaInterpreter::SetLightColor(lua_State *L)
    {
        int id = (int) lua_tonumber(L, 1);
        unsigned int color = (unsigned int) lua_tonumber(L, 2);
        /*float r = (float) lua_tonumber(L, 2);
        float g = (float) lua_tonumber(L, 3);
        float b = (float) lua_tonumber(L, 4);*/

        bool out = false;
        glm::vec3 col = MaskToFloat(color);

        if(m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetLightColor(id, MaskToFloat(color));

        return out;
    }

    float LuaInterpreter::Col(uint32_t color)
    {
        return ((float) color) / 0xFF;
    }
}