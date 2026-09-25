# DSP learning workspace

## Purpose
Learn DSP and C++ at the same time by writing programs that process real
radio signals from an RTL-SDR dongle.

**Programs are live and real-time.** They stream samples from the dongle and
process them as they arrive (spectrum, demodulation, decoding, audio out).
Recording I/Q to files is not part of this project. Don't suggest a
record-then-process workflow or add capture folders or scripts.

## Roles: who does what

**The user writes the DSP and program logic.** This is a learning project, and
writing the code is how the user learns.

Claude acts as the **devops and general help agent**:
- Toolchain, build systems (CMake), compiler flags, sanitizers, debuggers
- Installing and configuring dependencies (librtlsdr, FFTW, plotting tools, etc.)
- Driver and udev setup, USB and device troubleshooting
- Project scaffolding: directory layout, CMakeLists.txt, .gitignore, git setup
- Helper scripts and tooling *around* the code: live visualization of output,
  test harnesses, profiling
- Explaining DSP theory, C++ language features, and library APIs
- Reviewing the user's code, explaining compiler errors, and helping debug

Claude should **not** write the core DSP/program logic unprompted: filters,
FFTs, demodulators, mixers, decimators, sample-processing loops, and so on.
- When asked "how do I do X?", explain the concept, point at the relevant
  math/API, and give small illustrative snippets or pseudocode, not a finished
  implementation dropped into the project.
- Prefer hints, questions, and pointing out bugs over rewriting the user's code.
- If the user explicitly asks Claude to write a piece of logic, that's fine.
  Keep it minimal and explain it.
- Boilerplate that isn't the learning target (e.g. opening the device, audio
  output setup, CLI arg parsing) may be written by Claude when asked.

## Hardware
- **Nooelec NESDR SMArt v5** (RTL-SDR): Realtek RTL2832U + **Rafael Micro
  R820T** tuner (confirmed by `rtl_test`). USB ID `0bda:2838`. 29 gain steps,
  0.0–49.6 dB.
- Streams 2.4 MS/s with no sample loss (`rtl_test -s 2400000`, 2026-09-25).
- Rough capabilities: ~24 MHz – 1.7 GHz tuning range (tuner dependent), 8-bit
  I/Q samples, stable sample rates up to ~2.4 MS/s (max 3.2 MS/s).
- Samples arrive as interleaved unsigned 8-bit I/Q (`uint8_t`, centered at
  127.5), so convert to `std::complex<float>` before processing.
- Also attached: Focusrite Scarlett 2i2 (useful for audio output of
  demodulated signals, or as an audio-rate DSP input).

## Environment
- Ubuntu 26.04, **clang 21 (primary compiler)**, g++ 15.2 (cross-check),
  CMake 4.2, Ninja
- IDE: **CLion 2026.2**. It picks up `CMakePresets.json` as its CMake profiles,
  and uses `.clang-format` / `.clang-tidy` from the repo root.
- Git repo, branch `main`. The repo is public, so keep personal info
  (absolute paths, usernames, emails, device serials) out of tracked files.

## Project layout
One CMake project at the root, with one subdirectory per program:
```
CMakeLists.txt       root: C++20, warnings, sanitizer option, finds librtlsdr/FFTW
CMakePresets.json    debug (clang+ASan/UBSan), release (RelWithDebInfo), gcc-debug
apps/<name>/         one executable each; auto-added if it has a CMakeLists.txt
apps/hello/          toolchain smoke test, delete when real apps exist
```
- Add a shared library dir (e.g. `lib/`) once code is actually reused
  between apps. Don't create it before then.
- New app: create `apps/<name>/CMakeLists.txt` with `add_executable` and
  `target_link_libraries(<name> PRIVATE dsp_options ...)`, adding
  `PkgConfig::RTLSDR` / `PkgConfig::FFTW` (single-precision `fftw3f`) as needed.
- CLI builds: `cmake --preset debug && cmake --build --preset debug`
  (output goes to `build/<preset>/`)

## Code style: Google C++ Style Guide
- `.clang-format`: `BasedOnStyle: Google`
- `.clang-tidy`: google-*, bugprone-*, performance-*, modernize-*, plus Google
  naming enforcement
- Naming: `CamelCase` types and functions, `snake_case` variables,
  `trailing_underscore_` private members, `kConstantName` constants/enumerators
- Files: `.cc` / `.h`, header guards `DSP_<PATH>_<FILE>_H_`
- Any code Claude writes (examples, boilerplate, scripts' C++ parts) must follow
  this style too.

## Setup status / TODO
- [x] DVB-T kernel driver blacklisted in `/etc/modprobe.d/blacklist-rtlsdr.conf`
- [x] Installed `rtl-sdr librtlsdr-dev libfftw3-dev` (librtlsdr 2.0.x,
      FFTW 3.3.10). CMake finds `PkgConfig::RTLSDR` and `PkgConfig::FFTW`.
- [x] Dongle verified with `rtl_test`. Note: `rtl_test -t` prints "PLL not
      locked" and "No E4000 tuner found, aborting". Both are harmless on the
      R820T, because the `-t` benchmark only applies to E4000 tuners.
- [ ] Optional: `gqrx-sdr` as a GUI reference to compare the programs against
- [ ] Later: pick a live audio output library (e.g. PortAudio or miniaudio,
      on top of PipeWire/ALSA) once demodulation starts
- [x] git repo, `.gitignore`, CMake skeleton, presets, clang-format/tidy
      (all three presets verified building on 2026-09-25)

## Conventions
- C++20, `-Wall -Wextra -Wpedantic -Wshadow`. Develop in the `debug` preset
  (sanitizers on), measure performance in `release`.
- Real-time constraints: samples arrive through librtlsdr's async callback
  (`rtlsdr_read_async`) on a USB thread. Keep that callback fast and hand data
  to a processing thread (queue or ring buffer). If processing falls behind,
  samples get dropped. Watch for this, and help the user reason about it.
- Sanitizer builds are several times slower and may drop samples at high
  sample rates. If that happens, test with a lower rate or use `release`.

## Possible learning path (ideas, not requirements)
1. Stream samples live, convert u8 I/Q to complex float, print power/RMS
2. Live FFT spectrum in the terminal (FFTW, windowing, dB scale)
3. Frequency shifting (NCO / complex mixing)
4. FIR low-pass filter design + decimation
5. FM broadcast demodulation, played live through the Scarlett
6. AM (airband), then maybe digital: ADS-B at 1090 MHz, or POCSAG/APRS

## Future: machine learning (PyTorch)
Once a good amount of the DSP code exists, the user wants to add ML with
PyTorch alongside it (e.g. modulation classification, signal detection,
anomaly detection on the spectrum).
- Likely setup: train in Python/PyTorch, and run inference inside the live C++
  pipeline via LibTorch or ONNX Runtime (export the model to ONNX).
- Training needs data, and this project doesn't record. Options: public
  datasets (e.g. RadioML), synthetic signals generated in code, or a narrow
  exception that saves labeled examples for training. This is the user's call
  when the time comes. Raise it, don't decide it.
- The DSP code comes first. Don't steer toward ML before then.
