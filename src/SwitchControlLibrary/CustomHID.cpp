/*
Copyright (c) 2019 celclow
released under the MIT license
https://opensource.org/licenses/mit-license.php
*/

#include "./CustomHID.h"

#if defined(USBCON)

CustomHID_::CustomHID_() {}

int CustomHID_::SendReport(const void *data, int len) {
  auto ret = USB_Send(pluggedEndpoint | TRANSFER_RELEASE, data, len);
  return ret;
}

CustomHID_ &CustomHID() {
  static CustomHID_ obj;
  return obj;
}

#endif /* if defined(USBCON) */
