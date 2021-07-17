#include "Oscillator.h"

Oscillator::Oscillator()
	:phase(0)
{

}

double Oscillator::sampleRate = 44100.;

double Oscillator::generateSinWave(double frequency) {
	double result = sin(phase * PI);
	if (phase >= 1.) {
		phase -= 2.;
	}
	phase += frequency / sampleRate;
	return result;
}

double Oscillator::generateSquareWave(double frequency) {
	double result = 0.;
	if (phase < 0.) {
		result = -1.;
	}
	if (phase > 0.) {
		result = 1.;
	}
	if (phase >= 1.0) {
		phase -= 2.0;
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
		phase -= 2.0;
	}
	phase += frequency / sampleRate;
	return result;
}


