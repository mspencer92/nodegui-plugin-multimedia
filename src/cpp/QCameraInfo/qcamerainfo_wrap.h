#pragma once

#include <napi.h>

#include <QCameraInfo>

#include "Extras/Utils/nutils.h"
#include "core/Component/component_wrap.h"

class QCameraInfoWrap: public Napi::ObjectWrap<QCameraInfoWrap> {
  COMPONENT_WRAPPED_METHODS_DECLARATION
 private:
  QCameraInfo *instance;
  bool disableDeletion;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  static Napi::Value fromQCameraInfo(Napi::Env env, QCameraInfo *item);

  QCameraInfoWrap(const Napi::CallbackInfo &info);

  ~QCameraInfoWrap();

  QCameraInfo *getInternalInstance();

  // class constructor
  static Napi::FunctionReference constructor;

  // wrapped methods

};

  namespace StaticQCameraInfoWrapMethods {
    Napi::Value availableCameras(const Napi::CallbackInfo &info);
};  // namespace StaticQCameraInfoWrapMethods 
