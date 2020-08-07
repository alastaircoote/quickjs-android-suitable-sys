#include "quickjs/quickjs.h"

#ifdef __cplusplus
extern "C" {
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

JS_BOOL JS_IsUndefined__(JSValueConst v)
{
    return JS_IsUndefined(v);
}

JS_BOOL JS_IsString__(JSValueConst v)
{
    return JS_IsString(v);
}


#ifdef __cplusplus
} /* extern "C" { */
#endif