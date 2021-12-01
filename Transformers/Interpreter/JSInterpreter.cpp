//
// Created by Benjam on 11/30/2021.
//

#include "JSInterpreter.h"

#include <utility>

namespace Math4BG
{
    int JSInterpreter::magicCount = 0;
    
    JSInterpreter::JSInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output)
            : ILanInterpreter(std::move(contexts), std::move(output)),
            m_runTime(nullptr, JS_FreeRuntime),
            m_jsContext(nullptr, JS_FreeContext),
            m_instanceNumber(++magicCount)
    {
        m_runTime.reset(JS_NewRuntime());
        m_jsContext.reset(CustomJsContext(m_runTime.get()));
        magicMap[m_instanceNumber] = this;
    }

    JSContext* JSInterpreter::CustomJsContext(JSRuntime *rt)
    {
        JSContext *ctx = JS_NewContextRaw(rt);
        if (!ctx)
        {
            return nullptr;
        }

        JS_AddIntrinsicBaseObjects(ctx);
        JS_AddIntrinsicDate(ctx);
        JS_AddIntrinsicEval(ctx);
        JS_AddIntrinsicStringNormalize(ctx);
        JS_AddIntrinsicRegExp(ctx);
        JS_AddIntrinsicJSON(ctx);
        JS_AddIntrinsicProxy(ctx);
        JS_AddIntrinsicMapSet(ctx);
        JS_AddIntrinsicTypedArrays(ctx);
        JS_AddIntrinsicPromise(ctx);
        JS_AddIntrinsicBigInt(ctx);

        return ctx;
    }

    void JSInterpreter::CreateContext()
    {
        JSValue globalObj = JS_GetGlobalObject(m_jsContext.get());

        JS_SetPropertyStr(m_jsContext.get(), globalObj, "createContext",
                          JS_NewCFunctionMagic(m_jsContext.get(), [](JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv, int magic)
                          {
                              std::string name;
                              unsigned int width;
                              unsigned int height;
                              bool abstract;

                              if(argc > 0)
                              {
                                  name = JS_ToCString(ctx, argv[0]);
                              }

                              if(argc > 2)
                              {
                                  JS_ToUint32(ctx, &width, argv[1]);
                                  JS_ToUint32(ctx, &height, argv[2]);
                              }

                              if(argc > 3)
                              {
                                  abstract = JS_ToBool(ctx, argv[3]);
                              }

                              return (JSValue) { ((JSInterpreter*) magicMap[magic])->CreateContextImplementation(name, width, height, abstract), JS_TAG_INT };
                          }, "createContext", 0, JS_CFUNC_generic, m_instanceNumber));
        JS_FreeValue(m_jsContext.get(), globalObj);
        //JSValue globalObj;//, console, foo;
        //foo = JS_NewObject(m_jsContext.get()); // Crée un objet
        //JS_SetPropertyStr(m_jsContext.get(), foo, "createContext")
    }

    int JSInterpreter::CallOnInitFunction()
    {
        return 0;
    }

    int JSInterpreter::CallUpdateFunction(double lag)
    {
        return 0;
    }

    std::unique_ptr<JSInterpreter> JSInterpreter::Create(std::shared_ptr<Contexts> context, std::shared_ptr<IOutput> output)
    {
        return std::make_unique<JSInterpreter>(context, output);
    }

    void JSInterpreter::ExecuteFile(const std::string &path)
    {

    }

    void JSInterpreter::RegisterFunctions()
    {

    }
}
