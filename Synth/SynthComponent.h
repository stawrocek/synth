#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class SynthComponent : public juce::GroupComponent, 
					   public Button::Listener
{
public:
	SynthComponent(SynthAudioProcessor& processor, const juce::String & name, 
		const juce::String& buttonNameParamId);
	~SynthComponent();
	void paint(Graphics& g) override;
	void buttonClicked(Button*) override;

protected:
	class NameButtonLookAndFeel : public LookAndFeel_V4 {
		Font getTextButtonFont(TextButton&, int buttonHeight) override;
	};

	SynthAudioProcessor& processor;
	juce::TextButton buttonName;
	juce::String name;
	NameButtonLookAndFeel nameButtonLookAndFeel;

	bool isMuted = false;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> nameButtonAttachment;
};




