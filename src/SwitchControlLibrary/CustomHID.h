/*
Copyright (c) 2019 celclow
released under the MIT license
https://opensource.org/licenses/mit-license.php
*/

#pragma once

#include <HID.h>

#if defined(USBCON)

class CustomHID_ : public HID_ {
 public:
  CustomHID_();
  int SendReport(const void *data, int len);
};

CustomHID_ &CustomHID();

#endif /* if defined(USBCON) */
