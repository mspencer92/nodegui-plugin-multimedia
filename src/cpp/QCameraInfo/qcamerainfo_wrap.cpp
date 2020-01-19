#include "qcamerainfo_wrap.h"

#include "Extras/Utils/nutils.h"

Napi::FunctionReference QCameraInfoWrap::constructor;

Napi::Object QCameraInfoWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QCameraInfo";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
       COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

QCameraInfoWrap::QCameraInfoWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QCameraInfoWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  if (info[0].IsExternal()) {
    this->instance = info[0].As<Napi::External<QCameraInfo>>().Data();
  } else {
    Napi::TypeError::New(env,
                         "Incorrect initialization of QCameraInfoWrap")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QCameraInfo* QCameraInfoWrap::getInternalInstance() {
  return this->instance;
}

