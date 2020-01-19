import {
  Component,
  NativeElement,
} from "@nodegui/nodegui";
import addon from './utils/addon';

export class QCameraInfo extends Component {
  native: NativeElement;
  constructor(arg: QCameraInfo) {
    const native = new addon.QCameraInfo(arg.native)
    super()
    this.native = native;
  }
}

