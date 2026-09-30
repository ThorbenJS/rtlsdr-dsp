// Streams samples from the RTL-SDR and prints signal power.
#include <rtl-sdr.h>
#include <array>
#include <iostream>
#include <memory>

namespace {
struct DeviceCloser {
  void operator()(rtlsdr_dev_t* device){ rtlsdr_close(device); }
};
}

int main() {
  const auto device_count = rtlsdr_get_device_count();
  const auto device_name = rtlsdr_get_device_name(0);
  std::array<char, 256> manufacturer;
  std::array<char, 256> product;
  std::array<char, 256> serial;
  rtlsdr_get_device_usb_strings(
   0, manufacturer.data(),
   product.data(), serial.data());
  std::cout << device_count << "\n";
  std::cout << device_name << "\n";
  std::cout << manufacturer.data() << "\n" << product.data()
  << "\n" << serial.data() << "\n";
  std::cout.flush();
  rtlsdr_dev_t* dev = nullptr;

  // Opens device.
  if (rtlsdr_open(&dev, 0)) {
    std::cout << "Opening device failed" << std::endl;
    return 1;
  }
  const std::unique_ptr<rtlsdr_dev_t, DeviceCloser> dongle(dev);
  auto sample_rate = rtlsdr_get_sample_rate(dongle.get());
  std::cout << "Current sample rate of device: " << sample_rate << std::endl;
}
