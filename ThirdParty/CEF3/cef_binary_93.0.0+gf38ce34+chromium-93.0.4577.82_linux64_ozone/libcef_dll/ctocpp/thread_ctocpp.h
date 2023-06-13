// Copyright (c) 2021 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=b7b3e79350d42ab829eff401d6b4486ba4039267$
//

#ifndef CEF_LIBCEF_DLL_CTOCPP_THREAD_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_THREAD_CTOCPP_H_
#pragma once

#if !defined(WRAPPING_CEF_SHARED)
#error This file can be included wrapper-side only
#endif

#include "include/capi/cef_thread_capi.h"
#include "include/cef_thread.h"
#include "libcef_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefThreadCToCpp
    : public CefCToCppRefCounted<CefThreadCToCpp, CefThread, cef_thread_t> {
 public:
  CefThreadCToCpp();
  virtual ~CefThreadCToCpp();

  // CefThread methods.
  CefRefPtr<CefTaskRunner> GetTaskRunner() override;
  cef_platform_thread_id_t GetPlatformThreadId() override;
  void Stop() override;
  bool IsRunning() override;
};

#endif  // CEF_LIBCEF_DLL_CTOCPP_THREAD_CTOCPP_H_
