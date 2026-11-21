#include "src/sample_stream.h"

#include <iostream>
#include <vector>

SampleStream::SampleStream(Device& device) : device_(std::move(device)) {}

int SampleStream::Start() {
  device_.ResetBuffer();
 return device_.ReadAsync(SampleStream::OnSample,
 this, 0, 0);
}

int SampleStream::Stop() const { return device_.CancelAsync(); }

void SampleStream::PrintSamples(const std::vector<uint8_t>& samples) {
  std::cout << samples.size() << '\n';
  std::cout.flush();
}

void SampleStream::OnSample(unsigned char* buf, uint32_t len, void* ctx) {
  std::vector<uint8_t> samples(buf, buf + len);
  // Turn ctx back into "this".
  auto* self = static_cast<SampleStream*>(ctx);
  self->PrintSamples(samples);
}