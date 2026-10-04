# rtlsdr-dsp

This is a personal hobby project aimed at learning digital signal processing (DSP) with (and) C++.


## Hardware

| Device | Role | Key specs |
|---|---|---|
| [Nooelec NESDR SMArt v5](https://www.nooelec.com/store/sdr/sdr-receivers/nesdr-smart-sdr.html) | SDR receiver (USB) | RTL2832U + R820T2 tuner, ~25 MHz – 1.75 GHz (HF down to 100 kHz via direct sampling), 8-bit I/Q, up to ~2.4 MS/s stable |
| [Focusrite Scarlett 2i2 (3rd Gen)](https://us.focusrite.com/products/scarlett-2i2-3rd-gen) | Audio interface (USB-C) | 2 in / 2 out, 24-bit / 192 kHz. Plays demodulated audio live |


## Resources

- **[Smith]** S. W. Smith, *The Scientist and Engineer's Guide to Digital
  Signal Processing*, 2nd ed. San Diego, CA: California Technical
  Publishing, 1999. [Online]. Available: https://www.dspguide.com
- **[PySDR]** M. Lichtman, *PySDR: A Guide to SDR and DSP using Python*.
  [Online]. Available: https://pysdr.org


## Setup (Ubuntu)

1. Stop the kernel's DVB-T TV driver from taking over the dongle:

   ```bash
   printf 'blacklist dvb_usb_rtl28xxu\nblacklist rtl2832_sdr\nblacklist rtl2832\n' | sudo tee /etc/modprobe.d/blacklist-rtlsdr.conf
   sudo modprobe -r rtl2832_sdr dvb_usb_rtl28xxu rtl2832
   ```

2. Install the toolchain and libraries:

   ```bash
   sudo apt install clang clang-format clang-tidy cmake ninja-build pkg-config \
                    rtl-sdr librtlsdr-dev libfftw3-dev
   ```

3. Check that the dongle streams without dropping samples (Ctrl-C to stop):

   ```bash
   rtl_test -s 2400000
   ```

## Building

The build setup is in `CMakePresets.json`:

| Preset      | Compiler | Purpose                                         |
|-------------|----------|-------------------------------------------------|
| `debug`     | clang    | Everyday development, with ASan + UBSan         |
| `release`   | clang    | Optimized (`RelWithDebInfo`), for real-time use |
| `gcc-debug` | g++      | Occasional check with a second compiler         |

```bash
cmake --preset debug
cmake --build --preset debug
./build/debug/dsp
```

Sanitizer builds run several times slower. If a `debug` build drops samples at
high sample rates, lower the rate or use `release`.

## Layout

The project builds a single program, `dsp`. Each feature is added to it as its
own pair of source files.

```
CMakeLists.txt       shared settings: C++20, warnings, sanitizers, librtlsdr/FFTW
CMakePresets.json    build presets
src/CMakeLists.txt   the `dsp` program and its list of source files
src/main.cc          entry point
src/<feature>.cc/.h  one pair per feature
notes/               study notes: DSP and C++ explanations, equations, snippets
```

### Adding a source file

Create `src/<feature>.cc` and `src/<feature>.h`, then add the `.cc` to the list
in `src/CMakeLists.txt`:

```cmake
add_executable(dsp
  main.cc
  device.cc
  <feature>.cc)
```

Headers are included by their path from the repo root, for example
`#include "src/device.h"`. Add `PkgConfig::FFTW` (single-precision `fftw3f`) to
`target_link_libraries` once the code needs FFTs.

## Code style

[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)


## Use of AI

In this project the intention is to limit AI use to an project organization and guidance capacity.
Although AI is definetely capable enough of implementing most of the concepts of this project well enough, I intend to
implement DSP concepts and program logic personally. This allows me to learn and work through solutions and 
implementations on my own, build understanding and conceptualization around the topics and concepts of DSP and C++.

In an organizational capacity AI is used to create and maintain this project folder and file structure, as well as 
actively building and updating this README.md file according to how the project changes. I use AI to also keep track of and
update/set up libraries and packages necessary for this project.

AI is also great in a learning capacity alongside traditional resources that I will be using in this project like
textbooks, articles and tutorials.


## License

[MIT](LICENSE). The project links against [FFTW](https://www.fftw.org/), which
is GPL-licensed. Any distributed binaries that include FFTW fall under the GPL.
