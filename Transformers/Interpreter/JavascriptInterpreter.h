//
// Created by Benjam on 19-05-21.
//

#ifndef MATH4BG_JAVASCRIPTINTERPRETER_H
#define MATH4BG_JAVASCRIPTINTERPRETER_H

#include "ILanInterpreter.h"
#include <duktape.h>

namespace Math4BG
{
    class JavascriptInterpreter : public ILanInterpreter
    {
    public:
        JavascriptInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output);
        ~JavascriptInterpreter() override = default;

        void RegisterFunctions() override;

        void ExecuteFile(const std::string &path) override;
        bool CheckValidity() override;

        int CallOnInitFunction() override;
        int CallUpdateFunction(double lag) override;
        int CallOnWindowClosed(int windowId) override;

        //---

        int CreateWindow(duk_context *L);
        int DestroyWindow(duk_context *L);
        int SetBackgroundColor(duk_context *L);

        int CreateShader(duk_context *L);

        //---

        int CreateCircle(duk_context *L);
        int SetCirclePos(duk_context *L);
        int SetCircleSize(duk_context *L);
        int SetCircleColor(duk_context *L);

        int CreateLine(duk_context *L);
        int SetLinePos(duk_context *L);
        int SetLineColor(duk_context *L);

        int CreateDot(duk_context *L);
        int SetDotPos(duk_context *L);
        int SetDotColor(duk_context *L);

        int CreateRectangle(duk_context *L);
        int SetRectanglePos(duk_context *L);
        int SetRectangleDimens(duk_context *L);
        int SetRectangleColor(duk_context *L);

        //---

        int CreateCube(duk_context *L);


        static std::shared_ptr<JavascriptInterpreter> Create(std::shared_ptr<Contexts> context, std::shared_ptr<IOutput> output);
    private:
        std::unique_ptr<duk_context, decltype(duk_destroy_heap) *> m_jsContext;



        typedef int (JavascriptInterpreter::*mem_func)(duk_context *duk);
        template<mem_func func>
        int dispatch(duk_context *duk)
        {
            JavascriptInterpreter *ptr = *static_cast<JavascriptInterpreter **>(duk_to_pointer(duk, -1));
            return ((*ptr).*func)(duk);
        }
    };
}

#endif //MATH4BG_JAVASCRIPTINTERPRETER_H
