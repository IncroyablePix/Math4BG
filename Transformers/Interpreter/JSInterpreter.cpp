//
// Created by Benjam on 11/30/2021.
//

#include "JSInterpreter.h"

#include <utility>

namespace Math4BG
{
    JSInterpreter::JSInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output)
            : ILanInterpreter(std::move(contexts), std::move(output)),
            m_runTime(nullptr, JS_FreeRuntime),
            m_jsContext(nullptr, JS_FreeContext)
    {
        m_runTime.reset(JS_NewRuntime());
        m_jsContext.reset(CustomJsContext(m_runTime.get()));
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
}
