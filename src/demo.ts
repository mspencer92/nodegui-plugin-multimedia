import {
    QMainWindow,
    FlexLayout,
    QWidget,
    QLabel,
    QUrl
  } from "@nodegui/nodegui";
  import { QCameraInfo } from "./index";
  
  const cameras = QCameraInfo.availableCameras();
  console.log(cameras);