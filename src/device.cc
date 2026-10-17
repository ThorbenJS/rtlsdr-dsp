#include "src/device.h"

Device::Device(uint32_t device_index) : index_(device_index){
  rtlsdr_get_device_usb_strings(device_index, manufacturer_.data(),
    product_.data(), serial_.data());
}

Device::~Device() { Close(); }

void Device::Open() {
  if (rtlsdr_open(&dev_, index_)) {
    fail_state_ = true;
  }
}

void Device::Close() const {
  rtlsdr_close(dev_);
}

int Device::SetCenterFreq(const uint32_t freq) const {
  return rtlsdr_set_center_freq(dev_, freq);
}

uint32_t Device::GetCenterFreq() const {
  return rtlsdr_get_center_freq(dev_);
}

int Device::SetFreqCorrection(const int ppm) const {
  return rtlsdr_set_freq_correction(dev_, ppm);
}

int Device::GetFreqCorrection() const {
  return rtlsdr_get_freq_correction(dev_);
}

int Device::GetTunerGain() const {
  return rtlsdr_get_tuner_gain(dev_);
}

int Device::SetTunerGain(const int gain) const {
  return rtlsdr_set_tuner_gain(dev_, gain);
}

int Device::SetTunerBandwidth(const uint32_t bw) const {
  return rtlsdr_set_tuner_bandwidth(dev_, bw);
}

int Device::SetTunerIFgain(const int stage, const int gain) const {
  return rtlsdr_set_tuner_if_gain(dev_, stage, gain);
}

int Device::SetTunerGainMode(const bool manual) const {
  return rtlsdr_set_tuner_gain_mode(dev_, manual);
}

uint32_t Device::GetSampleRate() const {
  return rtlsdr_get_sample_rate(dev_);
}

int Device::SetSampleRate(const uint32_t rate) const {
  return rtlsdr_set_sample_rate(dev_, rate);
}

int Device::SetTestmode(const bool on) {
  int res = rtlsdr_set_testmode(dev_, on);
  if (!res) {
    test_mode_ = on;
  }
  return res;
}

int Device::SetAGCmode(const bool on) {
  int res = rtlsdr_set_agc_mode(dev_, on);
  if (!res) {
    agc_mode_ = on;
  }
  return res;
}

int Device::SetDirectSampling(const int mode) {
  int res = rtlsdr_set_direct_sampling(dev_, mode);
  if (!res) {
    direct_sampling_mode_ = mode;
  }
  return res;
}

int Device::GetDirectSampling() const {
  return rtlsdr_get_direct_sampling(dev_);
}

int Device::SetOffsetTuning(bool on) const {
  return rtlsdr_set_offset_tuning(dev_, on);
}

int Device::GetOffsetTuning() const {
  return rtlsdr_get_offset_tuning(dev_);
}

int Device::ResetBuffer() const {
  return rtlsdr_reset_buffer(dev_);
}

int Device::ReadSync(void* buf, int len, int* n_read) const {
  return rtlsdr_read_sync(dev_, buf, len, n_read);
}

int Device::ReadAsync(rtlsdr_read_async_cb_t cb, void* ctx, uint32_t buf_num,
                      uint32_t buf_len) const {
  return rtlsdr_read_async(dev_, cb, ctx, buf_num, buf_len);
}

int Device::CancelAsync() const {
  return rtlsdr_cancel_async(dev_);
}

int Device::SetBiasTee(int on) const {
  return rtlsdr_set_bias_tee(dev_, on);
}

int Device::SetBiasTeeGPIO(int gpio, int on) {
  return rtlsdr_set_bias_tee_gpio(dev_, gpio, on);
}