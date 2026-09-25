# DSP

This is a personal hobby project aimed at learning digital signal processing (DSP) with (and) C++.

The usage of Claude in this project is intended to function mainly as a devops / guidance agent.
My focus is to personally implement the DSP concepts and program logic myself so some learning 
and conceptualization can actually happen.

## Hardware

| Device | Role | Key specs |
|---|---|---|
| [Nooelec NESDR SMArt v5](https://www.nooelec.com/store/sdr/sdr-receivers/nesdr-smart-sdr.html) | SDR receiver (USB) | RTL2832U + R820T2 tuner, ~25 MHz – 1.75 GHz (HF down to 100 kHz via direct sampling), 8-bit I/Q, up to ~2.4 MS/s stable |
| [Focusrite Scarlett 2i2 (3rd Gen)](https://us.focusrite.com/products/scarlett-2i2-3rd-gen) | Audio interface (USB-C) | 2 in / 2 out, 24-bit / 192 kHz. Plays demodulated audio live |

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
./build/debug/apps/hello/hello
```

**CLion:** open the folder, then under *Settings → Build, Execution,
Deployment → CMake* enable the presets and disable the default profile.

Sanitizer builds run several times slower. If a `debug` build drops samples at
high sample rates, lower the rate or use `release`.

## Layout

```
CMakeLists.txt       shared settings: C++20, warnings, sanitizers, librtlsdr/FFTW
CMakePresets.json    build presets
apps/<name>/         one program per folder, sources directly inside
lib/                 (later) code shared between programs
```

### Adding a program

Create `apps/<name>/` with your sources and a `CMakeLists.txt`:

```cmake
add_executable(<name> main.cc)
target_link_libraries(<name> PRIVATE dsp_options PkgConfig::RTLSDR)
```

The build finds it automatically. Link `PkgConfig::FFTW` (single-precision
`fftw3f`) if the program needs FFTs.

## Code style

[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html),
enforced by `.clang-format` and `.clang-tidy`:

- `CamelCase` types and functions, `snake_case` variables
- `trailing_underscore_` private members, `kConstantName` constants
- `.cc` / `.h` files

```bash
clang-format -i apps/<name>/*.cc apps/<name>/*.h
clang-tidy -p build/debug apps/<name>/*.cc
```

## Roadmap

1. Stream samples live, convert u8 I/Q to complex float, print power/RMS
2. Live FFT spectrum in the terminal (windowing, dB scale)
3. Frequency shifting with an NCO / complex mixer
4. FIR low-pass filter design + decimation
5. FM broadcast demodulation, played live through the Scarlett
6. AM airband, then digital modes: ADS-B (1090 MHz), POCSAG, APRS
7. Machine learning with PyTorch on live signals (e.g. modulation classification)

## License

[MIT](LICENSE). The project links against [FFTW](https://www.fftw.org/), which
is GPL-licensed. Any distributed binaries that include FFTW fall under the GPL.
