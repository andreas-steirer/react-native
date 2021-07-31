/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cstdint>
#include <hermes/Public/GCConfig.h>
#include <hermes/Public/RuntimeConfig.h>

namespace facebook {
namespace react {

::hermes::vm::GCConfig::Builder defaultHermesGCConfigBuilder(
  int64_t heapSizeMB
) {
  namespace vm = ::hermes::vm;
  auto gcConfigBuilder =
      vm::GCConfig::Builder()
          .withName("RN")
          // For the next two arguments: avoid GC before TTI by initializing the
          // runtime to allocate directly in the old generation, but revert to
          // normal operation when we reach the (first) TTI point.
          .withAllocInYoung(false)
          .withRevertToYGAtTTI(true);
  if (heapSizeMB > 0) {
    gcConfigBuilder.withMaxHeapSize(heapSizeMB << 20);
  }
  return gcConfigBuilder;
}

} // namespace react
} // namespace facebook
