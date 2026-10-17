#ifndef DSP_SRC_DEVICE_H_
#define DSP_SRC_DEVICE_H_

#include <rtl-sdr.h>

#include <array>
#include <memory>
#include <string>

struct DeviceCloser {
  void operator()(rtlsdr_dev_t* device) {
    rtlsdr_close(device);
  }
};

// This is a wrapper class for wrapping the functionalities of the
// rtlsdr C library under a single Device object.
class Device {
public:
  explicit Device(uint32_t device_index);

  int Open();

  [[nodiscard]] int Close() const;

  [[nodiscard]] int SetCenterFreq(uint32_t freq) const;

  [[nodiscard]] uint32_t GetCenterFreq() const;

  [[nodiscard]] int SetFreqCorrection(int ppm) const;

  [[nodiscard]] int GetFreqCorrection() const;

  [[nodiscard]] int GetTunerGain() const;

  [[nodiscard]] int SetTunerGain(int gain) const;

  [[nodiscard]] int SetTunerBandwidth(uint32_t bw) const;

  [[nodiscard]] int SetTunerIFgain(int stage, int gain) const;

  [[nodiscard]] int SetTunerGainMode(bool manual) const;

  [[nodiscard]] uint32_t GetSampleRate() const;

  [[nodiscard]] int SetSampleRate(uint32_t rate) const;

  [[nodiscard]] int SetTestmode(bool on) const;

  [[nodiscard]] int SetAGCmode(bool on) const;

  [[nodiscard]] int SetDirectSampling(int mode) const ;

  [[nodiscard]] int GetDirectSampling() const;

  [[nodiscard]] int SetOffsetTuning(bool on) const;

  [[nodiscard]] int GetOffsetTuning() const;

  [[nodiscard]] int ResetBuffer() const;

  int ReadSync(void *buf, int len, int *n_read) const;

  int ReadAsync(rtlsdr_read_async_cb_t cb, void *ctx,
                uint32_t buf_num, uint32_t buf_len) const;

  [[nodiscard]] int CancelAsync() const;

  [[nodiscard]] int SetBiasTee(int on) const;

  int SetBiasTeeGPIO(int gpio, int on) const;

  [[nodiscard]] std::string GetManufacturer() const;

  [[nodiscard]] std::string GetProduct() const;

  [[nodiscard]] std::string GetSerial() const;

private:
  std::unique_ptr<rtlsdr_dev_t, DeviceCloser> dev_;
  uint32_t index_;
  std::array<char, 256> manufacturer_;
  std::array<char, 256> product_;
  std::array<char, 256> serial_;
};

#endif  // DSP_SRC_DEVICE_H_
