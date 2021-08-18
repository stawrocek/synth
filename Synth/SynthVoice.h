#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"
#include "Oscillator.h"
#include "Distortion.h"

enum class FilterType {
	LowPassFilter = 0,
	HighPassFilter = 1
};

class SynthVoice : public juce::SynthesiserVoice
{
public:
	SynthVoice();
	bool canPlaySound(juce::SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
		int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailoff) override;
	void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
	void pitchWheelMoved(int newPitchWheel);
	void controllerMoved(int controllerNumber, int newControllerValue);
	
	void setSampleRate(int sampleRate);

	void setOscillator(OscillatorType oscillatorType, int id);
	void setDetune(int detune, int id);
	void setMix(int mixVal, int id);

	void setAdsrAttack(float attack);
	void setAdsrDecay(float decay);
	void setAdsrSustain(float sustain);
	void setAdsrRelease(float release);

	void setFilterCutoff(float cutoff);
	void setFilterResonance(float resonance);
	void setFilterType(FilterType filterType);

	void setLFORate(float rate);
	void setLFOIntensity(float intensity);
	void setLFOWavetype(OscillatorType type);
	void setLFOTargetCutoff(bool targetCutoff);
	void setLFOTargetDetune(bool targetDetune);
	void setLFOTargetVolume(bool targetVolume);

	void setOscEnabled(bool enable, int index);
	void setADSREnabled(bool enable);
	void setLFOEnabled(bool enable);
	void setFilterEnabled(bool enable);
	void setAmpEnabled(bool enable);

	void setDistortionType(DistortionType distortionType);
	void setDistortionGain(float gain);
	void setDistortionWetLevel(float wetLevel);

private:
	double noteOnLevel;
	double frequency;
	float sampleRate;
	Oscillator osc1;
	Oscillator osc2;
	Oscillator osc3;
	float detune1, detune2, detune3;
	float mix[3] = {1, 1, 1};
	juce::ADSR adsr;
	juce::ADSR::Parameters adsrParams;

	IIRFilter filterLeft;
	IIRFilter filterRight;
	float filterCutoff;
	float filterResonance;
	FilterType filterType;
	juce::IIRCoefficients filterCoefficients;
	Distortion distortion;

	float lfoRate;
	float lfoIntensity;
	bool lfoTargetCutoff = false;
	bool lfoTargetDetune = false;
	bool lfoTargetVolume = false;

	bool osc1Enabled = true;
	bool osc2Enabled = true;
	bool osc3Enabled = true;
	bool adsrEnabled = true;
	bool lfoEnabled  = true;
	bool filterEnabled  = true;
	bool ampEnabled;

	bool tailOff = false;
	float stopNoteVelocity = 0.0;
	Oscillator lfo;
};