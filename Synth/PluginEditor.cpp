#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
	scopeComponent(p.audioBufferQueue), osc1Component(p, 1), osc2Component(p, 2), osc3Component(p, 3)
{
	setSize(800, 600);

	addAndMakeVisible(osc1Component);
	addAndMakeVisible(osc2Component);
	addAndMakeVisible(osc3Component);

	if (JUCEApplication::isStandaloneApp())
		addAndMakeVisible(midiKeyboardComponent);
	midiKeyboardComponent.setMidiChannel(2);
	midiKeyboardState.addListener(&audioProcessor.midiMessageCollector);

	
	addAndMakeVisible(scopeComponent);

	/*midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
	midiVolume.setRange(0.0, 127.0, 1.0);
	midiVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	midiVolume.setPopupDisplayEnabled(true, false, this);
	midiVolume.setTextValueSuffix("Volume");
	midiVolume.setValue(1.0);
	midiVolume.addListener(this);
	addAndMakeVisible(&midiVolume);*/

	waveformBox.setTextWhenNoChoicesAvailable("No waveform selected :(");
	juce::StringArray waveforms{"sin", "square", "triangle", "sawtooth"};
	waveformBox.addItemList(waveforms, 1);
	waveformBox.setSelectedItemIndex(0, juce::dontSendNotification);

	//waveformBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
	//	audioProcessor.tree, "WAVEFORM", waveformBox);

	
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
	auto h = area.getHeight();
	auto w = area.getWidth();

	osc1Component.setBounds(0, 0, w * 0.33, h * 0.2);
	osc2Component.setBounds(osc1Component.getBounds().withY(h*0.2));
	osc3Component.setBounds(osc1Component.getBounds().withY(h*0.4));

	scopeComponent.setBounds(0, h*0.6, w, h*0.3);
	//scopeComponent.setTopLeftPosition(0, 80);
	//scopeComponent.setSize(area.getWidth(), area.getHeight() - 100);

	if(JUCEApplication::isStandaloneApp())
		midiKeyboardComponent.setBounds(area.removeFromBottom(h * 0.1));
	//midiVolume.setBounds(0, getHeight()*0.6, getWidth(), getHeight()*0.15);
	waveformBox.setBounds(200, 100, w - 210, 20);
}

void SynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	//audioProcessor.noteOnVel = midiVolume.getValue();
}
