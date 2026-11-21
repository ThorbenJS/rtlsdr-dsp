#ifndef DSP_SRC_SAMPLE_STREAM_H_
#define DSP_SRC_SAMPLE_STREAM_H_

#include <vector>

#include "device.h"

class SampleStream {
public:
  explicit SampleStream(Device& device);

  int Start();

  [[nodiscard]] int Stop() const;

  static void OnSample(unsigned char *buf, uint32_t len, void *ctx);

  void PrintSamples(const std::vector<uint8_t>& samples);

private:
  Device device_;

};

#endif  // DSP_SRC_SAMPLE_STREAM_H_
