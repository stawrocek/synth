#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class SynthComponent : public juce::GroupComponent
{
public:
	SynthComponent(SynthAudioProcessor& processor, const juce::String & name, 
		const juce::String& buttonNameParamId);
	~SynthComponent();
	void paint(Graphics& g) override;
	void resized() override;

protected:
	class NameButtonLookAndFeel : public LookAndFeel_V4 {
		Font getTextButtonFont(TextButton&, int buttonHeight) override;
	};
	void squareLayout();

	SynthAudioProcessor& processor;
	juce::TextButton buttonName;
	juce::String name;
	NameButtonLookAndFeel nameButtonLookAndFeel;
	
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> nameButtonAttachment;
};




