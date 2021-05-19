//
// Created by Benjam on 19-05-21.
//

#include "JavascriptInterpreter.h"

namespace Math4BG
{

    JavascriptInterpreter::JavascriptInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output) :
    m_jsContext(nullptr, duk_destroy_heap),
    ILanInterpreter(contexts, output)
    {
        m_jsContext.reset(duk_create_heap_default());
        RegisterFunctions();
    }

    void JavascriptInterpreter::RegisterFunctions()
    {
        duk_context* context = m_jsContext.get();
        *static_cast<JavascriptInterpreter **>(duk_to_pointer(context, -1)) = this;

        /*duk_push_c_function(m_jsContext.get(), "CreateCircle", &dispatch<&JavascriptInterpreter::CreateCircle>);

        duk_push_c_function(m_jsContext.get(), &dispatch<&JavascriptInterpreter::CreateCircle>, 5);*/
    }

    std::shared_ptr<JavascriptInterpreter>JavascriptInterpreter::Create(std::shared_ptr<Contexts> context, std::shared_ptr<IOutput> output)
    {
        return std::shared_ptr<JavascriptInterpreter>(static_cast<JavascriptInterpreter *>(new JavascriptInterpreter(context, output)));
    }

    void JavascriptInterpreter::ExecuteFile(const std::string &path)
    {

    }

    bool JavascriptInterpreter::CheckValidity()
    {
        return true;
    }

    int JavascriptInterpreter::CallOnInitFunction()
    {
        return 0;
    }

    int JavascriptInterpreter::CallUpdateFunction(double lag)
    {
        return 0;
    }

    int JavascriptInterpreter::CallOnWindowClosed(int windowId)
    {
        return 0;
    }

    int JavascriptInterpreter::CreateWindow(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::DestroyWindow(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetBackgroundColor(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::CreateShader(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::CreateCircle(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetCirclePos(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetCircleSize(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetCircleColor(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::CreateLine(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetLinePos(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetLineColor(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::CreateDot(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetDotPos(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetDotColor(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::CreateRectangle(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetRectanglePos(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetRectangleDimens(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::SetRectangleColor(duk_context *L)
    {
        return 0;
    }

    int JavascriptInterpreter::CreateCube(duk_context *L)
    {
        return 0;
    }
}