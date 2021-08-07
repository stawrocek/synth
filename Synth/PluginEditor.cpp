#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
	scopeComponent(p.audioBufferQueue), osc1Component(p, 1), osc2Component(p, 2), osc3Component(p, 3),
	adsrComponent(p), filterComponent(p), reverbComponent(p)
{
	setSize(800, 600);
	addAndMakeVisible(osc1Component);
	addAndMakeVisible(osc2Component);
	addAndMakeVisible(osc3Component);

	addAndMakeVisible(adsrComponent);

	addAndMakeVisible(filterComponent);

	addAndMakeVisible(reverbComponent);

	if (JUCEApplication::isStandaloneApp())
		addAndMakeVisible(midiKeyboardComponent);
	midiKeyboardComponent.setMidiChannel(2);
	midiKeyboardState.addListener(&audioProcessor.midiMessageCollector);

	
	addAndMakeVisible(scopeComponent);
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
	midiKeyboardState.removeListener(&audioProcessor.midiMessageCollector);
}

void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SynthAudioProcessorEditor::resized()
{
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	osc1Component.setBounds(0, 0, w * 0.33, h * 0.2);
	osc2Component.setBounds(osc1Component.getBounds().withY(h*0.2));
	osc3Component.setBounds(osc1Component.getBounds().withY(h*0.4));

	adsrComponent.setBounds(osc1Component.getBounds().withX(w*0.33));
	filterComponent.setBounds(osc2Component.getBounds().withX(w*0.33));
	
	reverbComponent.setBounds(osc3Component.getBounds().withX(w*0.66));

	scopeComponent.setBounds(0, h*0.6, w, h*0.3);

	if(JUCEApplication::isStandaloneApp())
		midiKeyboardComponent.setBounds(area.removeFromBottom(h * 0.1));
}

void SynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	//audioProcessor.noteOnVel = midiVolume.getValue();
}
