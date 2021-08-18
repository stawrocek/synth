#include "Distortion.h"

float Distortion::processSingleSample(float sample) {
	if (distortionType == DistortionType::SoftClippingAtan) {
		return (2.0 / PI) * atan(sample * gain * 10.0) * wetLevel + (1.0 - wetLevel) * sample;
	}
	else if (distortionType == DistortionType::HardClipping) {
		float clean = (1.0 - wetLevel) * sample;
		float dist = sample*gain*10;
		float g = sample*gain*10;
		if (g >= 1.0) dist = 1.0;
		else if (g <= -1.0) dist = -1.0;
		
		return clean + wetLevel * dist;
	}
}

void Distortion::setType(DistortionType type) {
	distortionType = type;
}

void Distortion::setGain(float gain_) {
	gain = gain_;
}

void Distortion::setWetLevel(float wetLevel_) {
	wetLevel = wetLevel_;
}
