// Streams samples from the RTL-SDR and prints signal power.
#include <rtl-sdr.h>

#include <iostream>
#include "sample_stream.h"
#include "device.h"

int main() {
  auto dongle = Device(0);
  std::cout << dongle.GetManufacturer() << "\n" << dongle.GetProduct() << "\n"
  << dongle.GetSerial() << "\n";
  dongle.Open();
  if (dongle.SetCenterFreq(94'300'000)) {
    throw std::logic_error("Setting center frequency failed");
  }
  if (dongle.SetSampleRate(2'400'000)) {
    throw std::logic_error("Setting sample rate failed");
  }
  std::cout << "Testing sample streaming" << "\n";
  auto streamer = SampleStream(dongle);
  std::cout << streamer.Start();
}
