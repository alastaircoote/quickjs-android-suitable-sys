#include "quickjs/quickjs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    JSValue JS_NewInt64__(JSContext *ctx, int64_t val)
    {
        return JS_NewInt64(ctx, val);
    }

    JSValue JS_NewBool__(JSContext *ctx, JS_BOOL val)
    {
        return JS_NewBool(ctx, val);
    }

    JSValue JS_NewFloat64__(JSContext *ctx, double d)
    {
        return JS_NewFloat64(ctx, d);
    }

    JS_BOOL JS_IsException__(JSValueConst v)
    {
        return JS_IsException(v);
    }

    void JS_FreeValue__(JSContext *ctx, JSValue v)
    {
        JS_FreeValue(ctx, v);
    }

    void JS_FreeValueRT__(JSRuntime *rt, JSValue v)
    {
        JS_FreeValueRT(rt, v);
    }

    JS_BOOL JS_IsUndefined__(JSValueConst v)
    {
        return JS_IsUndefined(v);
    }

    JS_BOOL JS_IsString__(JSValueConst v)
    {
        return JS_IsString(v);
    }

    int JS_GetTag__(JSValueConst v)
    {
        return JS_VALUE_GET_TAG(v);
    }

    JSValue JS_DupValue__(JSContext *ctx, JSValueConst v)
    {
        return JS_DupValue(ctx, v);
    }

    JSValue JS_DupValueRT__(JSRuntime *rt, JSValueConst v)
    {
        return JS_DupValueRT(rt, v);
    }

    JS_BOOL JS_IsObject__(JSValueConst v)
    {
        return JS_IsObject(v);
    }

    const JSValue JS_UNDEFINED__ = JS_UNDEFINED;
    const JSValue JS_NULL__ = JS_NULL;
    const JSValue JS_TRUE__ = JS_TRUE;
    const JSValue JS_EXCEPTION__ = JS_EXCEPTION;
    const JSValue JS_UNINITIALIZED__ = JS_UNINITIALIZED;

    int JS_IsEqual__(JSValueConst v1, JSValueConst v2)
    {
        if (v1.tag != v2.tag)
        {
            return 0;
        }
        int tag = JS_VALUE_GET_TAG(v1);
        if (tag == JS_TAG_NULL || tag == JS_TAG_UNDEFINED || tag == JS_TAG_UNDEFINED)
        {
            return 1;
        }

        if (tag == JS_TAG_INT)
            return JS_VALUE_GET_INT(v1) == JS_VALUE_GET_INT(v2);
        if (tag == JS_TAG_FLOAT64)
            return JS_VALUE_GET_FLOAT64(v1) == JS_VALUE_GET_FLOAT64(v2);

        return JS_VALUE_GET_PTR(v1) == JS_VALUE_GET_PTR(v2);
    }

#ifdef __cplusplus
} /* extern "C" { */
#endif