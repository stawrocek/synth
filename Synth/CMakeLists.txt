cmake_minimum_required(VERSION 3.15)

# The top-level CMakeLists.txt file for a project must contain a literal, direct call to the
# `project()` command. `project()` sets up some helpful variables that describe source/binary
# directories, and the current project version. This is a standard CMake command.

project(SynthProject VERSION 0.0.1)
target_sources(SynthPlugin
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp)