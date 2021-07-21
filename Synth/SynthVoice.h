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
		if (velocity < 0.00001 && allowTailoff == false)
		//if (velocity < 0.00001)
			clearCurrentNote();
		level = 0;
	}

	void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
	{
		for (int sample = 0; sample < numSamples; sample++)
		{
			double signal1 = osc1.generateWave(frequency);
			double signal2 = osc2.generateWave(frequency);
			double signal3 = osc3.generateWave(frequency);

			double signal = (signal1 * level + signal2 * level + signal3 * level)/3.0;
			//double signal = signal1 * level;
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

	void setOscillator(OscillatorType oscillatorType, int id) {
		if(id == 1)
			osc1.setType(oscillatorType);
		if (id == 2)
			osc2.setType(oscillatorType);
		if (id == 3)
			osc3.setType(oscillatorType);
	}

	void setDetune(int detune, int id) {
		if (id == 1)
			osc1.setDetune(detune/100.f);
		if (id == 2)
			osc2.setDetune(detune/100.f);
		if (id == 3)
			osc3.setDetune(detune/100.f);
	}

private:
	double level;
	double frequency;
	Oscillator osc1;
	Oscillator osc2;
	Oscillator osc3;
};