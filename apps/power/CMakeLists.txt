add_executable(power main.cc)
target_link_libraries(power PRIVATE dsp_options PkgConfig::RTLSDR)
