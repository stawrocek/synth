#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "SynthComponent.h"
#include "RotarySlider.h"
#include "WaveformButton.h"

class LFOComponent : public SynthComponent
{
public:
	LFOComponent(SynthAudioProcessor& processor);

	void resized() override;

private:
	WaveformButton btnOscSine;
	WaveformButton btnOscRect;
	WaveformButton btnOscTriangle;
	WaveformButton btnOscSawtooth;

	RotarySlider sliderLFORate;
	RotarySlider sliderLFOIntensity;

	GroupComponent lfoTargets;
	TextButton lfoTargetFilterCutoff;
	TextButton lfoTargetDetune;
	TextButton lfoTargetVolume;
	

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentRate;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentIntensity;
	
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonTarget1Attachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonTarget2Attachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonTarget3Attachment;

};



