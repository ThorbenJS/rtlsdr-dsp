#include "src/device.h"

Device::Device(uint32_t device_index) : index_(device_index){
  rtlsdr_get_device_usb_strings(device_index, manufacturer_.data(),
    product_.data(), serial_.data());
}

void Device::Open() {
  if (rtlsdr_open(&dev_, index_)) {
    fail_state_ = true;
  }
}

void Device::Close() {
  rtlsdr_close(dev_);
}