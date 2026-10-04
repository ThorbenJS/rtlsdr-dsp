# The one program. Add each new .cc file to this list.
add_executable(dsp
  main.cc
  device.cc)

# Headers are included by their path from the repo root: #include "src/device.h"
target_include_directories(dsp PRIVATE ${PROJECT_SOURCE_DIR})

# Add PkgConfig::FFTW (single-precision fftw3f) once the code needs FFTs.
target_link_libraries(dsp PRIVATE dsp_options PkgConfig::RTLSDR)

# Put the binary at build/<preset>/dsp.
set_target_properties(dsp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
