#include "qcamerainfo_wrap.h"
#include <QDebug>

#include "Extras/Utils/nutils.h"
#include "QtWidgets/QTreeWidget/qtreewidget_wrap.h"
#include "core/Component/component_wrap.h"

Napi::FunctionReference QCameraInfoWrap::constructor;

Napi::Object QCameraInfoWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QCameraInfo";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {       StaticMethod("availableCameras",
                    &StaticQCameraInfoWrapMethods::availableCameras),
                    COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QCameraInfoWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

QCameraInfo *QCameraInfoWrap::getInternalInstance() {
  return this->instance;
}

Napi::Value QCameraInfoWrap::fromQCameraInfo(Napi::Env env,
                                                     QCameraInfo *item) {
  // The item might be a nullptr, therefore use env.Null() as return value.
  if (item == nullptr) {
    return env.Null();
  }

  Napi::Value itemWrap = QCameraInfoWrap::constructor.New(
      {Napi::External<QCameraInfo>::New(env, new QCameraInfo(*item))});

  return itemWrap;
}

QCameraInfoWrap::~QCameraInfoWrap() {
  if (!this->disableDeletion) {
    delete this->instance;
  }
}
QCameraInfoWrap::QCameraInfoWrap(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<QCameraInfoWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() > 0 && info[0].IsExternal()) {
    // --- if external ---
    this->instance = info[0].As<Napi::External<QCameraInfo>>().Data();
    if (info.Length() == 2) {
      this->disableDeletion = info[1].As<Napi::Boolean>().Value();
    }
  } else {
    // --- regular cases ---
    if (info.Length() == 0) {
      this->instance = new QCameraInfo();
    } else {
      Napi::TypeError::New(env, "Wrong number of arguments")
          .ThrowAsJavaScriptException();
    }
  }
  this->rawData = extrautils::configureComponent(this->getInternalInstance());
}
Napi::Value StaticQCameraInfoWrapMethods::availableCameras(
    const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  QList<QCameraInfo> items = QCameraInfo::availableCameras();
  Napi::Array napiItems = Napi::Array::New(env, items.size());
    for (int i = 0; i < items.size(); i++) {
    QCameraInfo item = items[i];
        Napi::Object val = QCameraInfoWrap::constructor.New({Napi::External<QCameraInfo>::New(env, &item), Napi::Boolean::New(env, true)});
        napiItems[i] = val;
    }
  return napiItems;
}