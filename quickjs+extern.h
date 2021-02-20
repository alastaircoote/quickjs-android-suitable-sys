#include "quickjs/quickjs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    JSValue JS_NewInt64__(JSContext *ctx, int64_t val);
    JSValue JS_NewBool__(JSContext *ctx, JS_BOOL val);
    JSValue JS_NewFloat64__(JSContext *ctx, double d);
    JS_BOOL JS_IsException__(JSValueConst v);
    void JS_FreeValue__(JSContext *ctx, JSValue v);
    JS_BOOL JS_IsUndefined__(JSValueConst v);
    JS_BOOL JS_IsString__(JSValueConst v);

    int JS_GetTag__(JSValueConst v);

#ifdef __cplusplus
} /* extern "C" { */
#endif