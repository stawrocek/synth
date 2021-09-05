#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Config.h"

SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
	scopeComponent(p.audioBufferQueue), osc1Component(p, 1), osc2Component(p, 2), osc3Component(p, 3),
	adsrComponent(p), filterComponent(p), reverbComponent(p), lfoComponent(p), ampComponent(p),
	delayComponent(p)
{
	setSize(950, 650);
	setResizable(false, false);
	addAndMakeVisible(osc1Component);
	addAndMakeVisible(osc2Component);
	addAndMakeVisible(osc3Component);
	addAndMakeVisible(adsrComponent);
	addAndMakeVisible(filterComponent);
	addAndMakeVisible(reverbComponent);
	addAndMakeVisible(lfoComponent);
	addAndMakeVisible(ampComponent);
	addAndMakeVisible(delayComponent);

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

	adsrComponent.setBounds(osc1Component.getBounds().withX(w*0.33).withWidth(w*0.4));
	filterComponent.setBounds(osc2Component.getBounds().withX(w*0.33).withWidth(w*0.22));
	lfoComponent.setBounds(osc3Component.getBounds().withX(w*0.33));
	
	ampComponent.setBounds(osc1Component.getBounds().withX(w * 0.73).withWidth(w*0.27));
	delayComponent.setBounds(osc2Component.getBounds().withX(w * 0.55).withWidth(w * 0.45));
	reverbComponent.setBounds(osc3Component.getBounds().withX(w * 0.66));

	scopeComponent.setBounds(0, h*0.6, w, h*0.3);

	midiKeyboardComponent.setBounds(area.removeFromBottom(h * 0.1));
}

void SynthAudioProcessorEditor::showHostMenuForParam(const juce::MouseEvent& event, juce::String paramID) {
	auto c = getHostContext();
	
	if (c != nullptr) {
		auto d = c->getContextMenuForParameterIndex(audioProcessor.tree.getParameter(paramID));
		d->showNativeMenu(this->getScreenPosition() + event.getPosition());
	}
}
