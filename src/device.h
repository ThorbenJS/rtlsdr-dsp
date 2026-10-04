#ifndef DSP_SRC_DEVICE_H_
#define DSP_SRC_DEVICE_H_

#include <rtl-sdr.h>

#include <array>
#include <memory>
#include <string>

class Device {
public:
  explicit Device(uint32_t device_index);

  void Open();

  void Close();

private:
  rtlsdr_dev_t* dev_ = nullptr;
  uint32_t index_;
  std::string manufacturer_;
  std::string product_;
  std::string serial_;
  bool fail_state_ = false;




};

#endif  // DSP_SRC_DEVICE_H_
