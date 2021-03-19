#include "quickjs/quickjs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    JSValue JS_NewInt64__(JSContext *ctx, int64_t val);
    JSValue JS_NewBool__(JSContext *ctx, JS_BOOL val);
    JSValue JS_NewFloat64__(JSContext *ctx, double d);

    JS_BOOL JS_IsException__(JSValueConst v);
    JS_BOOL JS_IsObject__(JSValueConst v);
    JS_BOOL JS_IsUndefined__(JSValueConst v);
    JS_BOOL JS_IsString__(JSValueConst v);

    void JS_FreeValue__(JSContext *ctx, JSValue v);
    int JS_GetTag__(JSValueConst v);

    JSValue JS_DupValue__(JSContext *ctx, JSValueConst v);
    JSValue JS_DupValueRT__(JSRuntime *rt, JSValueConst v);

    const JSValue JS_UNDEFINED__ = JS_UNDEFINED;
    const JSValue JS_NULL__ = JS_NULL;
    const JSValue JS_TRUE__ = JS_TRUE;
    const JSValue JS_EXCEPTION__ = JS_EXCEPTION;
    const JSValue JS_UNINITIALIZED__ = JS_UNINITIALIZED;

#ifdef __cplusplus
} /* extern "C" { */
#endif