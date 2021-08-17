#include "Oscillator.h"

Oscillator::Oscillator()
	:phase(0)
{

}

double Oscillator::sampleRate = 48000.;

double Oscillator::generateSinWave(double frequency) {
	double result = sin(phase * 2.0 * PI);
	if (phase >= 1.) {
		phase -= 1.;
	}
	phase += frequency / sampleRate;
	return result;
}

double Oscillator::generateSquareWave(double frequency) {
	double result = 0.;
	if (phase < 0.5) {
		result = -1.;
	}
	if (phase > 0.5) {
		result = 1.;
	}
	if (phase >= 1.0) {
		phase -= 1.0;
	}
	phase += frequency / sampleRate;
	return result;
}

double Oscillator::generateTriangleWave(double frequency) {
	double result = 0.;
	if (phase >= 1.0) {
		phase -= 1.0;
	}
	if (phase <= 0.5) {
		result = (phase - 0.25) * 4;
	}
	else {
		result = ((1.0 - phase) - 0.25) * 4;
	}
	phase += frequency / sampleRate;
	return result;
}

double Oscillator::generateSawtoothWave(double frequency) {
	double result = 0.;
	result = phase;
	if (phase >= 1.0) {
		phase -= 1.0;
	}
	phase += frequency / sampleRate;
	return result;
}

double Oscillator::generateWave(double frequency) {
	frequency *= (1.0 + detune);
	if (oscillatorType == OscillatorType::OscSin)
		return generateSinWave(frequency);
	else if (oscillatorType == OscillatorType::OscSquare)
		return generateSquareWave(frequency);
	else if (oscillatorType == OscillatorType::OscTriangle)
		return generateTriangleWave(frequency);
	else if (oscillatorType == OscillatorType::OscSawtooth)
		return generateSawtoothWave(frequency);
}

OscillatorType Oscillator::getType() {
	return oscillatorType;
}
void Oscillator::setType(OscillatorType oscType_) {
	oscillatorType = oscType_;
}

double Oscillator::getPhase() {
	return phase;
}

void Oscillator::setPhase(double phase_) {
	phase = phase_;
}

double Oscillator::getDetune() {
	return detune;
}

void Oscillator::setDetune(double detune_) {
	detune = detune_;
}

