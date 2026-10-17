// Streams samples from the RTL-SDR and prints signal power.
#include <rtl-sdr.h>

#include <iostream>

#include "device.h"

int main() {
  auto dongle = Device(0);
  std::cout << dongle.GetManufacturer() << "\n" << dongle.GetProduct() << "\n"
  << dongle.GetSerial();
}
