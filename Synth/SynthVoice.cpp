#include <JuceHeader.h>

#include "SynthVoice.h"
#include "Config.h"

SynthVoice::SynthVoice() 
{
	params.attack = adsrInitialAttack;
	params.decay = adsrInitialDecay;
	params.sustain = adsrInitialSustain;
	params.release = adsrInitialRelease;
	adsr.setParameters(params);
	filterCutoff = filterInitialCutoff;
	filterResonance = filterInitialResonance;
	filterType = filterInitialType;
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
	int currentPitchWheelPosition) 
{
	adsr.noteOn();
	level = velocity;
	frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
}

void SynthVoice::stopNote(float velocity, bool allowTailoff)
{
	adsr.noteOff();
	//if (velocity < 0.00001 && allowTailoff == false)
	//if (velocity < 0.00001)
	if(!allowTailoff)
		clearCurrentNote();
	level = velocity;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	adsr.setParameters(params);
	updateFilter();
	for (int sample = 0; sample < numSamples; sample++)
	{
		double signal1 = osc1.generateWave(frequency) * mix[0];
		double signal2 = osc2.generateWave(frequency) * mix[1];
		double signal3 = osc3.generateWave(frequency) * mix[2];

		double signal = (signal1 * level + signal2 * level + signal3 * level);// / 3.0;
		//double signal = signal1 * level;
		signal = adsr.getNextSample() * signal;
		signal = iirFilter.processSingleSampleRaw(signal);
		signal *= level;

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{
			outputBuffer.addSample(channel, startSample, signal);
		}
		++startSample;
	}
}

void SynthVoice::pitchWheelMoved(int newPitchWheel)
{

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}


void SynthVoice::setSampleRate(int sampleRate_) {
	sampleRate = sampleRate_;
	adsr.setSampleRate(sampleRate);
}

void SynthVoice::setOscillator(OscillatorType oscillatorType, int id) {
	if(id == 1)
		osc1.setType(oscillatorType);
	if (id == 2)
		osc2.setType(oscillatorType);
	if (id == 3)
		osc3.setType(oscillatorType);
}

void SynthVoice::setDetune(int detune, int id) {
	if (id == 1)
		osc1.setDetune(detune/1000.f);
	if (id == 2)
		osc2.setDetune(detune/1000.f);
	if (id == 3)
		osc3.setDetune(detune/1000.f);
}

void SynthVoice::setMix(int mixVal, int id) {
	mix[id-1] = mixVal / 100.f;
}

void SynthVoice::setAdsrAttack(float attack) {
	params.attack = attack;
}

void SynthVoice::setAdsrDecay(float decay) {
	params.decay = decay;
}

void SynthVoice::setAdsrSustain(float sustain) {
	params.sustain = sustain;
}

void SynthVoice::setAdsrRelease(float release) {
	params.release = release;
}

void SynthVoice::setFilterCutoff(float cutoff) {
	filterCutoff = cutoff;
}

void SynthVoice::setFilterResonance(float resonance) {
	filterResonance = resonance;
}

void SynthVoice::setFilterType(FilterType filterType_) {
	filterType = filterType_;
}

void SynthVoice::updateFilter() {
	if (filterType == FilterType::LowPassFilter) {
		filterCoefficients = IIRCoefficients::makeLowPass(sampleRate, filterCutoff, filterResonance);
	}
	else if (filterType == FilterType::HighPassFilter) {
		filterCoefficients = IIRCoefficients::makeHighPass(sampleRate, filterCutoff, filterResonance);
	}
	iirFilter.setCoefficients(filterCoefficients);
}