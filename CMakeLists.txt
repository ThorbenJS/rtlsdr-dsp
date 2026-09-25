cmake_minimum_required(VERSION 3.28)
project(dsp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DSP_SANITIZE "Build with AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

# Common compile settings, linked into every target.
add_library(dsp_options INTERFACE)
target_compile_options(dsp_options INTERFACE -Wall -Wextra -Wpedantic -Wshadow)
if(DSP_SANITIZE)
  target_compile_options(dsp_options INTERFACE
    -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(dsp_options INTERFACE -fsanitize=address,undefined)
endif()

# Optional third-party libraries. Link with PkgConfig::RTLSDR / PkgConfig::FFTW.
find_package(PkgConfig REQUIRED)
pkg_check_modules(RTLSDR IMPORTED_TARGET librtlsdr)
pkg_check_modules(FFTW IMPORTED_TARGET fftw3f)

add_subdirectory(apps)
