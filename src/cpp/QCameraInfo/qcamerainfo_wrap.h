#pragma once

#include <napi.h>
#include <nodegui/core/Component/component_macro.h>

#include <QCameraInfo>

class QCameraInfoWrap : public Napi::ObjectWrap<QCameraInfoWrap> {
 private:
  QCameraInfo* instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QCameraInfoWrap(const Napi::CallbackInfo& info);
  QCameraInfo* getInternalInstance();
  // Wrapped methods

  COMPONENT_WRAPPED_METHODS_DECLARATION
};
