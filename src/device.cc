#include "src/device.h"

Device::Device(uint32_t device_index) : index_(device_index){
  rtlsdr_get_device_usb_strings(device_index, manufacturer_.data(),
    product_.data(), serial_.data());
}

int Device::Open() {
  rtlsdr_dev_t* raw_dev = nullptr;
  int res = rtlsdr_open(&raw_dev, index_);
  dev_.reset(raw_dev);
  return res;
}

int Device::Close() const {
  return rtlsdr_close(dev_.get());
}

int Device::SetCenterFreq(const uint32_t freq) const {
  return rtlsdr_set_center_freq(dev_.get(), freq);
}

uint32_t Device::GetCenterFreq() const {
  return rtlsdr_get_center_freq(dev_.get());
}

int Device::SetFreqCorrection(const int ppm) const {
  return rtlsdr_set_freq_correction(dev_.get(), ppm);
}

int Device::GetFreqCorrection() const {
  return rtlsdr_get_freq_correction(dev_.get());
}

int Device::GetTunerGain() const {
  return rtlsdr_get_tuner_gain(dev_.get());
}

int Device::SetTunerGain(const int gain) const {
  return rtlsdr_set_tuner_gain(dev_.get(), gain);
}

int Device::SetTunerBandwidth(const uint32_t bw) const {
  return rtlsdr_set_tuner_bandwidth(dev_.get(), bw);
}

int Device::SetTunerIFgain(const int stage, const int gain) const {
  return rtlsdr_set_tuner_if_gain(dev_.get(), stage, gain);
}

int Device::SetTunerGainMode(const bool manual) const {
  return rtlsdr_set_tuner_gain_mode(dev_.get(), manual);
}

uint32_t Device::GetSampleRate() const {
  return rtlsdr_get_sample_rate(dev_.get());
}

int Device::SetSampleRate(const uint32_t rate) const {
  return rtlsdr_set_sample_rate(dev_.get(), rate);
}

int Device::SetTestmode(const bool on) const {
  return rtlsdr_set_testmode(dev_.get(), on);
}

int Device::SetAGCmode(const bool on) const {
  return rtlsdr_set_agc_mode(dev_.get(), on);
}

int Device::SetDirectSampling(const int mode) const {
  return rtlsdr_set_direct_sampling(dev_.get(), mode);
}

int Device::GetDirectSampling() const {
  return rtlsdr_get_direct_sampling(dev_.get());
}

int Device::SetOffsetTuning(bool on) const {
  return rtlsdr_set_offset_tuning(dev_.get(), on);
}

int Device::GetOffsetTuning() const {
  return rtlsdr_get_offset_tuning(dev_.get());
}

int Device::ResetBuffer() const {
  return rtlsdr_reset_buffer(dev_.get());
}

int Device::ReadSync(void* buf, int len, int* n_read) const {
  return rtlsdr_read_sync(dev_.get(), buf, len, n_read);
}

int Device::ReadAsync(rtlsdr_read_async_cb_t cb, void* ctx, uint32_t buf_num,
                      uint32_t buf_len) const {
  return rtlsdr_read_async(dev_.get(), cb, ctx, buf_num, buf_len);
}

int Device::CancelAsync() const {
  return rtlsdr_cancel_async(dev_.get());
}

int Device::SetBiasTee(int on) const {
  return rtlsdr_set_bias_tee(dev_.get(), on);
}

int Device::SetBiasTeeGPIO(int gpio, int on) const {
  return rtlsdr_set_bias_tee_gpio(dev_.get(), gpio, on);
}

std::string Device::GetManufacturer() const {
  std::string ret(manufacturer_.data());
  return ret;
}

std::string Device::GetProduct() const {
  std::string ret(product_.data());
  return ret;
}

std::string Device::GetSerial() const {
  std::string ret(serial_.data());
  return ret;
}