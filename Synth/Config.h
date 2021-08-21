#pragma once

#include <JuceHeader.h>

const juce::String osc1WaveTypeParamId = "WAVEFORM1";
const juce::String osc2WaveTypeParamId = "WAVEFORM2";
const juce::String osc3WaveTypeParamId = "WAVEFORM3";
const juce::String osc1DetuneParamId = "OSC1DETUNE";
const juce::String osc2DetuneParamId = "OSC2DETUNE";
const juce::String osc3DetuneParamId = "OSC3DETUNE";
const juce::String osc1DetuneStepsParamId = "OSC1DETUNESTEPS";
const juce::String osc2DetuneStepsParamId = "OSC2DETUNESTEPS";
const juce::String osc3DetuneStepsParamId = "OSC3DETUNESTEPS";
const juce::String osc1MixParamId = "OSC1MIX";
const juce::String osc2MixParamId = "OSC2MIX";
const juce::String osc3MixParamId = "OSC3MIX";

const juce::String osc1WaveTypeParamName = "Waveform1";
const juce::String osc2WaveTypeParamName = "Waveform2";
const juce::String osc3WaveTypeParamName = "Waveform3";
const juce::String osc1DetuneParamName = "Detune";
const juce::String osc2DetuneParamName = "Detune";
const juce::String osc3DetuneParamName = "Detune";
const juce::String osc1DetuneStepsParamName = "Semitone";
const juce::String osc2DetuneStepsParamName = "Semitone";
const juce::String osc3DetuneStepsParamName = "Setmitone";

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

const juce::String delayTimeParamId = "DELAY_TIME";
const juce::String delayWetLevelParamId = "DELAY_WET_LEVEL";
const juce::String delayFeedbackParamId = "DELAY_FEEDBACK";
const juce::String delayFilterParamId = "DELAY_FILTER";
const juce::String delayTailoffParamId = "DELAY_TAILOFF";

const juce::String delayTimeParamName = "Time";
const juce::String delayWetLevelParamName = "Wet/Dry";
const juce::String delayFeedbackParamName = "Feedback";
const juce::String delayFilterParamName = "Filter";
const juce::String delayTailoffParamName = "Tailoff";

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

const juce::String lfoWaveformTypeParamId = "LFO_WAVEFORM_TYPE";
const juce::String lfoRateParamId = "LFO_RATE";
const juce::String lfoIntensityParamId = "LFO_INTENSITY";
const juce::String lfoWaveformTypeParamName = "Waveform type";
const juce::String lfoRateParamName = "Rate";
const juce::String lfoIntensityParamName = "Intensity";
const juce::String lfoTarget1ActiveParamId = "LFO_TARGET_1_ACTIVE";
const juce::String lfoTarget1ActiveParamName = "LFO cutoff";
const juce::String lfoTarget2ActiveParamId = "LFO_TARGET_2_ACTIVE";
const juce::String lfoTarget2ActiveParamName = "LFO detune";
const juce::String lfoTarget3ActiveParamId = "LFO_TARGET_3_ACTIVE";
const juce::String lfoTarget3ActiveParamName = "LFO volume";

const juce::String ampGainParamId = "AMP_GAIN";
const juce::String ampWetLevelParamId = "AMP_WET_LEVEL";
const juce::String ampVolumeParamId = "AMP_VOLUME";
const juce::String ampDistortionTypeParamId = "AMP_DISTORTION_TYPE";
const juce::String ampGainParamName = "Gain";
const juce::String ampWetLevelParamName = "Wet/Dry";
const juce::String ampVolumeParamName = "Volume";
const juce::String ampDistortionTypeParamName = "Distortion type";

const juce::String osc1EnabledParamId = "OSC1ENABLED";
const juce::String osc1EnabledParamName = "Osc enabled";
const juce::String osc2EnabledParamId = "OSC2ENABLED";
const juce::String osc2EnabledParamName = "Osc2 enabled";
const juce::String osc3EnabledParamId = "OSC3ENABLED";
const juce::String osc3EnabledParamName = "Osc3 enabled";
const juce::String adsrEnabledParamId = "ADSRENABLED";
const juce::String adsrEnabledParamName = "Adsr enabled";
const juce::String filterEnabledParamId = "FILTERENABLED";
const juce::String filterEnabledParamName = "Filter Enabled";
const juce::String reverbEnabledParamId = "REVERBENABLED";
const juce::String reverbEnabledParamName = "Reverb Enabled";
const juce::String lfoEnabledParamId = "LFOENABLED";
const juce::String lfoEnabledParamName = "LFO Enabled";
const juce::String ampEnabledParamId = "AMPENABLED";
const juce::String ampEnabledParamName = "Amp Enabled";
const juce::String delayEnabledParamId = "DELAYENABLED";
const juce::String delayEnabledParamName = "Delay Enabled";

const float adsrInitialAttack = 0.5;
const float adsrInitialDecay = 0.2;
const float adsrInitialSustain = 1.0;
const float adsrInitialRelease = 0.5;

const float filterInitialCutoff = 440;
const float filterInitialResonance = 2;
const FilterType filterInitialType = FilterType::LowPassFilter;

const float delayInitialTime = 2.0f;
const float delayInitialWetLevel = 0.33f;
const float delayInitialFeedback = 0.5;
const float delayInitialFilter = 100;
const bool delayInitialTailoff = true;

const float reverbInitialRoomSize   = 0.5f;
const float reverbInitialDamping    = 0.5f;
const float reverbInitialWetLevel   = 0.33f;
const float reverbInitialWidth      = 1.0f;
const bool reverbInitialFreezeMode = false;

const float ampInitialGain = 0.5;
const float ampInitialWetLevel = 0.0;
const float ampInitialVolume = 1.0;

const float lfoInitialRate = 0.0;
const float lfoInitialIntensity = 0.0;
