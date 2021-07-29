#pragma once

#include <JuceHeader.h>

const juce::String osc1WaveTypeParamId = "WAVEFORM1";
const juce::String osc2WaveTypeParamId = "WAVEFORM2";
const juce::String osc3WaveTypeParamId = "WAVEFORM3";
const juce::String osc1DetuneParamId = "OSC1DETUNE";
const juce::String osc2DetuneParamId = "OSC2DETUNE";
const juce::String osc3DetuneParamId = "OSC3DETUNE";
const juce::String osc1MixParamId = "OSC1MIX";
const juce::String osc2MixParamId = "OSC2MIX";
const juce::String osc3MixParamId = "OSC3MIX";

const juce::String osc1WaveTypeParamName = "waveform1";
const juce::String osc2WaveTypeParamName = "waveform2";
const juce::String osc3WaveTypeParamName = "waveform3";
const juce::String osc1DetuneParamName = "osc1detune";
const juce::String osc2DetuneParamName = "osc2detune";
const juce::String osc3DetuneParamName = "osc3detune";
const juce::String osc1MixParamName = "osc1mix";
const juce::String osc2MixParamName = "osc2mix";
const juce::String osc3MixParamName = "osc3mix";

const juce::String adsrAttackParamId = "ADSR_ATTACK";
const juce::String adsrDecayParamId = "ADSR_DECAY";
const juce::String adsrSustainParamId = "ADSR_SUSTAIN";
const juce::String adsrReleaseParamId = "ADSR_RELEASE";

const juce::String adsrAttackParamName = "Attack";
const juce::String adsrDecayParamName = "Decay";
const juce::String adsrSustainParamName = "Sustain";
const juce::String adsrReleaseParamName = "Release";

const float adsrInitialAttack = 0.5;
const float adsrInitialDecay = 0.2;
const float adsrInitialSustain = 1.0;
const float adsrInitialRelease = 0.5;