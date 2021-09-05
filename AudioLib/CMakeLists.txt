cmake_minimum_required(VERSION 3.15)

project(SynthProject VERSION 0.0.1)

add_library(AudioLib STATIC
        Oscillator.cpp
		Oscillator.h
		Distortion.h
		Distortion.cpp
		)
set_target_properties(AudioLib PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
    VISIBILITY_INLINES_HIDDEN TRUE
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden)
