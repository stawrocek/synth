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

const juce::String osc1WaveTypeParamName = "Waveform1";
const juce::String osc2WaveTypeParamName = "Waveform2";
const juce::String osc3WaveTypeParamName = "Waveform3";
const juce::String osc1DetuneParamName = "Detune";
const juce::String osc2DetuneParamName = "Detune";
const juce::String osc3DetuneParamName = "Detune";
const juce::String osc1MixParamName = "Mix";
const juce::String osc2MixParamName = "Mix";
const juce::String osc3MixParamName = "Mix";

const juce::String adsrAttackParamId = "ADSR_ATTACK";
const juce::String adsrDecayParamId = "ADSR_DECAY";
const juce::String adsrSustainParamId = "ADSR_SUSTAIN";
const juce::String adsrReleaseParamId = "ADSR_RELEASE";

const juce::String adsrAttackParamName = "Attack";
const juce::String adsrDecayParamName = "Decay";
const juce::String adsrSustainParamName = "Sustain";
const juce::String adsrReleaseParamName = "Release";

const juce::String filterCutoffParamId = "CUTOFF";
const juce::String filterResonanceParamId = "RESONANCE";
const juce::String filterTypeParamId = "FILTER_TYPE";

const juce::String filterCutoffParamName = "Cutoff";
const juce::String filterResonanceParamName = "Resonance";
const juce::String filterTypeParamName = "Filter type";

const juce::String reverbRoomSizeParamId = "REVERB_ROOM_SIZE";
const juce::String reverbDampingParamId = "REVERB_DAMPING";
const juce::String reverbWetLevelParamId = "REVERB_WET_LEVEL";
const juce::String reverbWidthParamId = "REVERB_WIDTH";
const juce::String reverbFreezeModeParamId = "REVERB_FREEZE_MODE";

const juce::String reverbRoomSizeParamName = "Room";
const juce::String reverbDampingParamName = "Damping";
const juce::String reverbWetLevelParamName = "Wet/Dry";
const juce::String reverbWidthParamName = "Width";
const juce::String reverbFreezeModeParamName = "Freeze";

const float adsrInitialAttack = 0.5;
const float adsrInitialDecay = 0.2;
const float adsrInitialSustain = 1.0;
const float adsrInitialRelease = 0.5;

const float filterInitialCutoff = 440;
const float filterInitialResonance = 2;
const FilterType filterInitialType = FilterType::LowPassFilter;

const float reverbInitialRoomSize   = 0.5f;
const float reverbInitialDamping    = 0.5f;
const float reverbInitialWetLevel   = 0.33f;
const float reverbInitialWidth      = 1.0f;
const float reverbInitialFreezeMode = 0.0f;
