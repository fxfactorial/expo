// Copyright 2004-present Facebook. All Rights Reserved.

#include "ABI19_0_0JSCPerfStats.h"

#ifdef JSC_HAS_PERF_STATS_API

#include <JavaScriptCore/JSPerfStats.h>
#include <ABI19_0_0jschelpers/ABI19_0_0JSCHelpers.h>
#include <ABI19_0_0jschelpers/ABI19_0_0Value.h>

using namespace facebook::ReactABI19_0_0;

static JSValueRef nativeGetHeapStats(
    JSContextRef ctx,
    JSObjectRef function,
    JSObjectRef thisObject,
    size_t argumentCount,
    const JSValueRef arguments[],
    JSValueRef* exception) {
  JSHeapStats heapStats = {0};
  JSGetHeapStats(ctx, &heapStats);

  auto result = facebook::ReactABI19_0_0::Object::create(ctx);
  result.setProperty("size", {ctx, Value::makeNumber(ctx, heapStats.size)});
  result.setProperty("extra_size", {ctx, Value::makeNumber(ctx, heapStats.extraSize)});
  result.setProperty("capacity", {ctx, Value::makeNumber(ctx, heapStats.capacity)});
  result.setProperty("object_count", {ctx, Value::makeNumber(ctx, heapStats.objectCount)});
  result.setProperty("object_size", {ctx, Value::makeNumber(ctx, heapStats.objectSizeAfterLastCollect)});
  result.setProperty("object_capacity", {ctx, Value::makeNumber(ctx, heapStats.objectCapacityAfterLastCollect)});
  result.setProperty("block_size", {ctx, Value::makeNumber(ctx, heapStats.blockSize)});
  result.setProperty("malloc_size", {ctx, Value::makeNumber(ctx, heapStats.mallocSize)});

  return (JSObjectRef) result;
}

static JSValueRef nativeGetGCStats(
    JSContextRef ctx,
    JSObjectRef function,
    JSObjectRef thisObject,
    size_t argumentCount,
    const JSValueRef arguments[],
    JSValueRef* exception) {
  JSGCStats gcStats = {0};
  JSGetGCStats(ctx, &gcStats);

  auto result = facebook::ReactABI19_0_0::Object::create(ctx);
  result.setProperty(
      "last_full_gc_length",
      {ctx, Value::makeNumber(ctx, gcStats.lastFullGCLength)});
  result.setProperty(
      "last_eden_gc_length",
      {ctx, Value::makeNumber(ctx, gcStats.lastEdenGCLength)});

  return (JSObjectRef) result;
}

#endif

namespace facebook {
namespace ReactABI19_0_0 {

void addJSCPerfStatsHooks(JSGlobalContextRef ctx) {
#ifdef JSC_HAS_PERF_STATS_API
  installGlobalFunction(ctx, "nativeGetHeapStats", nativeGetHeapStats);
  installGlobalFunction(ctx, "nativeGetGCStats", nativeGetGCStats);
#endif
}

} }
