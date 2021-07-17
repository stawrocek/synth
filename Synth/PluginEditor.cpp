#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
	scopeComponent(p.audioBufferQueue)
{
    setSize (400, 400);

	if (JUCEApplication::isStandaloneApp())
		addAndMakeVisible(midiKeyboardComponent);
	midiKeyboardComponent.setMidiChannel(2);
	midiKeyboardState.addListener(&audioProcessor.midiMessageCollector);

	auto area = getLocalBounds();
	scopeComponent.setTopLeftPosition(0, 80);
	scopeComponent.setSize(area.getWidth(), area.getHeight() - 100);
	addAndMakeVisible(scopeComponent);

	midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
	midiVolume.setRange(0.0, 127.0, 1.0);
	midiVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	midiVolume.setPopupDisplayEnabled(true, false, this);
	midiVolume.setTextValueSuffix("Volume");
	midiVolume.setValue(1.0);
	midiVolume.addListener(this);
	addAndMakeVisible(&midiVolume);

	waveformBox.setTextWhenNoChoicesAvailable("No waveform selected :(");
	juce::StringArray waveforms{"sin", "square", "triangle", "sawtooth"};
	waveformBox.addItemList(waveforms, 1);
	waveformBox.setSelectedItemIndex(0, juce::dontSendNotification);

	waveformBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
		audioProcessor.tree, "WAVEFORM", waveformBox);

	addAndMakeVisible(waveformBox);		
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
	midiKeyboardState.removeListener(&audioProcessor.midiMessageCollector);
}

void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
	g.drawFittedText("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void SynthAudioProcessorEditor::resized()
{
	auto area = getLocalBounds();
	if(JUCEApplication::isStandaloneApp())
		midiKeyboardComponent.setBounds(area.removeFromTop(80).reduced(8));
	midiVolume.setBounds(40, 30, 20, getHeight() - 60);
	waveformBox.setBounds(200, 100, getWidth() - 210, 20);
}

void SynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	//audioProcessor.noteOnVel = midiVolume.getValue();
}
