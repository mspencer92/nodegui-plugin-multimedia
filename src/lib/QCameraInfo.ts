import {
  Component,
  NativeElement,
  checkIfNativeElement,
} from "@nodegui/nodegui";
import addon from './utils/addon';

export class QCameraInfo extends Component {
  native: NativeElement;
  constructor(arg?: QCameraInfo | NativeElement) {
    super();
    if (checkIfNativeElement(arg)) {
      this.native = arg as NativeElement;
  } else {
    if (arg instanceof QCameraInfo){
      this.native = new addon.QCameraInfo(arg.native);
    } else {
      this.native = new addon.QCameraInfo();
    }
  }
  }
  static availableCameras(): QCameraInfo[] {
    const nativeItems = addon.QCameraInfo.availableCameras();
    return nativeItems.map(function(eachItem: QCameraInfo) {
        return new QCameraInfo(eachItem);
    });

  }
}

