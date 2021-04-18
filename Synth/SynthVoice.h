#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"
#include "Oscillator.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound* sound) override
	{
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
		int currentPitchWheelPosition) override
	{
		level = velocity;
		frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	}

	void stopNote(float velocity, bool allowTailoff) override
	{
		if (velocity < 0.00001)
			clearCurrentNote();
		level = 0;
	}

	void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
	{
		for (int sample = 0; sample < numSamples; sample++)
		{
			double signal = osc1.generateSinWave(frequency) * level;
			for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
			{
				outputBuffer.addSample(channel, startSample, signal);
			}

			++startSample;
		}
	}

	void pitchWheelMoved(int newPitchWheel) override
	{

	}

	void controllerMoved(int controllerNumber, int newControllerValue) override
	{

	}

private:
	double level;
	double frequency;
	Oscillator osc1;
};