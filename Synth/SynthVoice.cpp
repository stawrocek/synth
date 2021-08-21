#include <JuceHeader.h>

#include "SynthVoice.h"
#include "Config.h"

SynthVoice::SynthVoice() 
{
	adsrParams.attack = adsrInitialAttack;
	adsrParams.decay = adsrInitialDecay;
	adsrParams.sustain = adsrInitialSustain;
	adsrParams.release = adsrInitialRelease;
	filterCutoff = filterInitialCutoff;
	filterResonance = filterInitialResonance;
	filterType = filterInitialType;
	adsr.setParameters(adsrParams);
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
	int currentPitchWheelPosition) 
{
	tailOff = false;
	if(adsrEnabled)
		adsr.noteOn();
	noteOnLevel = velocity;
	frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
}

void SynthVoice::stopNote(float velocity, bool allowTailoff)
{
	if (allowTailoff && !tailOff)
	{
		stopNoteVelocity = velocity;
		tailOff = true;
		if (adsrEnabled)
			adsr.noteOff();
	}
	else
	{
		clearCurrentNote();
		stopNoteVelocity = 0.0;
	}
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	if (!adsrEnabled && tailOff) {
		if (stopNoteVelocity < 0.01) {
			clearCurrentNote();
			return;
		}

		stopNoteVelocity *= 0.99;
	}
	if (adsrEnabled) {
		adsr.setParameters(adsrParams);
	}
	for (int sample = 0; sample < numSamples; sample++)
	{
		double detuneLFO = 0;
		double levelLFO = 1.0;
		double lfoVar = lfo.generateWave(lfoRate);
		double cutoffFreq = filterCutoff;
		if (lfoEnabled) {
			if (lfoTargetCutoff)
				cutoffFreq = jmax(0.1, filterCutoff + lfoVar * lfoIntensity * 300.0);
			if (lfoTargetDetune)
				detuneLFO = lfoVar * lfoIntensity * 100.0;
			if (lfoTargetVolume)
				levelLFO = lfoVar * lfoIntensity;
		}
		osc1.setDetuneCents(detune1 + detuneLFO);
		osc2.setDetuneCents(detune2 + detuneLFO);
		osc3.setDetuneCents(detune3 + detuneLFO);
		osc1.setDetuneHalfSteps(semitone1);
		osc2.setDetuneHalfSteps(semitone2);
		osc3.setDetuneHalfSteps(semitone3);

		if (filterType == FilterType::LowPassFilter) {
			filterCoefficients = IIRCoefficients::makeLowPass(sampleRate, cutoffFreq, filterResonance);
		}
		else if (filterType == FilterType::HighPassFilter) {
			filterCoefficients = IIRCoefficients::makeHighPass(sampleRate, cutoffFreq, filterResonance);
		}
		filterLeft.setCoefficients(filterCoefficients);
		filterRight.setCoefficients(filterCoefficients);

		double signal1 = osc1Enabled ? osc1.generateWave(frequency) * mix[0] : 0;
		double signal2 = osc2Enabled ? osc2.generateWave(frequency) * mix[1] : 0;
		double signal3 = osc3Enabled ? osc3.generateWave(frequency) * mix[2] : 0;

		double signal = (signal1 + signal2 + signal3) / 3.0;
		
		if (adsrEnabled) {
			double nextAdsr = adsr.getNextSample();
			signal = nextAdsr * signal;
		}
		else if (tailOff && !adsrEnabled){
			signal *= stopNoteVelocity;
		}
		signal *= noteOnLevel;
		signal *= (1.0 + levelLFO);

		float leftSignal = signal;
		float rightSignal = signal;

		if (filterEnabled) {
			leftSignal = filterLeft.processSingleSampleRaw(signal);
			rightSignal = filterRight.processSingleSampleRaw(signal);
		}

		if (ampEnabled) {
			leftSignal = distortion.processSingleSample(leftSignal);
			rightSignal = distortion.processSingleSample(rightSignal);
		}

		outputBuffer.addSample(0, startSample, leftSignal);
		outputBuffer.addSample(1, startSample, rightSignal);

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
		detune1 = detune;
	if (id == 2)
		detune2 = detune;
	if (id == 3)
		detune3 = detune;
}

void SynthVoice::setSemitone(int semitone, int id) {
	if (id == 1)
		semitone1 = semitone;
	if (id == 2)
		semitone2 = semitone;
	if (id == 3)
		semitone3 = semitone;
}

void SynthVoice::setMix(int mixVal, int id) {
	mix[id-1] = mixVal / 100.f;
}

void SynthVoice::setAdsrAttack(float attack) {
	adsrParams.attack = attack;
}

void SynthVoice::setAdsrDecay(float decay) {
	adsrParams.decay = decay;
}

void SynthVoice::setAdsrSustain(float sustain) {
	adsrParams.sustain = sustain;
}

void SynthVoice::setAdsrRelease(float release) {
	adsrParams.release = release;
}

void SynthVoice::setLFORate(float rate) {
	lfoRate = rate;
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

void SynthVoice::setLFOIntensity(float intensity) {
	lfoIntensity = intensity;
}

void SynthVoice::setLFOWavetype(OscillatorType type) {
	lfo.setType(type);
}

void SynthVoice::setLFOTargetCutoff(bool targetCutoff) {
	lfoTargetCutoff = targetCutoff;
}

void SynthVoice::setLFOTargetDetune(bool targetDetune) {
	lfoTargetDetune = targetDetune;
}

void SynthVoice::setLFOTargetVolume(bool targetVolume) {
	lfoTargetVolume = targetVolume;
}

void SynthVoice::setDistortionType(DistortionType distortionType) {
	distortion.setType(distortionType);
}

void SynthVoice::setDistortionGain(float gain) {
	distortion.setGain(gain);
}

void SynthVoice::setDistortionWetLevel(float wetLevel) {
	distortion.setWetLevel(wetLevel);
}

void SynthVoice::setOscEnabled(bool enable, int index) {
	if (index == 1) osc1Enabled = enable;
	if (index == 2) osc2Enabled = enable;
	if (index == 3) osc3Enabled = enable;
}
void SynthVoice::setADSREnabled(bool enable) {
	adsrEnabled = enable;
}

void SynthVoice::setLFOEnabled(bool enable) {
	lfoEnabled = enable;
}

void SynthVoice::setFilterEnabled(bool enable) {
	filterEnabled = enable;
}

void SynthVoice::setAmpEnabled(bool enable) {
	ampEnabled = enable;
}