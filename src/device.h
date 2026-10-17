#ifndef DSP_SRC_DEVICE_H_
#define DSP_SRC_DEVICE_H_

#include <rtl-sdr.h>
#include <memory>
#include <string>


// This is a wrapper class for wrapping the functionalities of the
// rtlsdr C library under a single Device object.
class Device {
public:
  explicit Device(uint32_t device_index);

  ~Device();

  void Open();

  void Close() const;

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

  int SetTestmode(bool on);

  int SetAGCmode(bool on);

  int SetDirectSampling(int mode);

  [[nodiscard]] int GetDirectSampling() const;

  [[nodiscard]] int SetOffsetTuning(bool on) const;

  [[nodiscard]] int GetOffsetTuning() const;

  [[nodiscard]] int ResetBuffer() const;

  int ReadSync(void *buf, int len, int *n_read) const;

  int ReadAsync(rtlsdr_read_async_cb_t cb, void *ctx,
                uint32_t buf_num, uint32_t buf_len) const;

  [[nodiscard]] int CancelAsync() const;

  [[nodiscard]] int SetBiasTee(int on) const;

  int SetBiasTeeGPIO(int gpio, int on);

private:
  rtlsdr_dev_t* dev_ = nullptr;
  uint32_t index_;
  std::string manufacturer_;
  std::string product_;
  std::string serial_;
  bool test_mode_;
  bool agc_mode_;
  int direct_sampling_mode_;
  bool fail_state_ = false;




};

#endif  // DSP_SRC_DEVICE_H_
