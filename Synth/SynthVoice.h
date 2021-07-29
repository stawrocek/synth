#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"
#include "Oscillator.h"

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
	void setOscillator(OscillatorType oscillatorType, int id);
	void setDetune(int detune, int id);
	void setMix(int mixVal, int id);
	void setSampleRate(int sampleRate);
	void setAdsrAttack(float attack);
	void setAdsrDecay(float decay);
	void setAdsrSustain(float sustain);
	void setAdsrRelease(float release);

private:
	double level;
	double frequency;
	Oscillator osc1;
	Oscillator osc2;
	Oscillator osc3;
	float mix[3] = {1, 1, 1};
	juce::ADSR adsr;
	juce::ADSR::Parameters params;
};