//based on https://docs.juce.com/master/tutorial_dsp_delay_line.html

#pragma once

#include <JuceHeader.h>
#include "Config.h"

template <typename Type>
class DelayLine
{
public:
	void clear() noexcept {
		std::fill(rawData.begin(), rawData.end(), Type(0));
	}

	size_t size() const noexcept {
		return rawData.size();
	}

	void resize(size_t newValue) {
		rawData.resize(newValue);
		leastRecentIndex = 0;
	}

	Type back() const noexcept {
		return rawData[leastRecentIndex];
	}

	Type get(size_t delayInSamples) const noexcept {
		jassert(delayInSamples >= 0 && delayInSamples < size());

		return rawData[(leastRecentIndex + 1 + delayInSamples) % size()];
	}

	void set(size_t delayInSamples, Type newValue) noexcept {
		jassert(delayInSamples >= 0 && delayInSamples < size());

		rawData[(leastRecentIndex + 1 + delayInSamples) % size()] = newValue;
	}

	void push(Type valueToAdd) noexcept {
		rawData[leastRecentIndex] = valueToAdd;
		leastRecentIndex = leastRecentIndex == 0 ? size() - 1 : leastRecentIndex - 1;
	}

private:
	std::vector<Type> rawData;
	size_t leastRecentIndex = 0;
};

template <typename Type, size_t maxNumChannels = 2>
class Delay {
public:
	Delay() {
		setMaxDelayTime(4.0f);
		setDelayTime(0, 0.5f);
		setDelayTime(1, 0.5f);
		setWetLevel(0.5f);
		setFeedback(0.5f);
	}

	void prepare(const juce::dsp::ProcessSpec& spec) {
		jassert(spec.numChannels <= maxNumChannels);
		sampleRate = (Type)spec.sampleRate;
		updateDelayLineSize();
		updateDelayTime();

		filterCoefs = juce::dsp::IIR::Coefficients<Type>::makeFirstOrderHighPass(sampleRate, Type(1e3));

		for (auto& f : filters) {
			f.prepare(spec);
			f.coefficients = filterCoefs;
		}
	}

	void reset() noexcept {
		for (auto& f : filters)
			f.reset();

		for (auto& dline : delayLines)
			dline.clear();
	}

	size_t getNumChannels() const noexcept {
		return delayLines.size();
	}

	void setMaxDelayTime(Type newValue) {
		jassert(newValue > Type(0));
		maxDelayTime = newValue;
		updateDelayLineSize();
	}

	void setFeedback(Type newValue) noexcept {
		jassert(newValue >= Type(0) && newValue <= Type(1));
		feedback = newValue;
	}

	void setWetLevel(Type newValue) noexcept {
		jassert(newValue >= Type(0) && newValue <= Type(1));
		wetLevel = newValue;
	}

	void setDelayTime(size_t channel, Type newValue) {
		if (channel >= getNumChannels())
		{
			jassertfalse;
			return;
		}

		jassert(newValue >= Type(0));
		delayTimes[channel] = newValue;

		updateDelayTime();
	}

	void setDelayTime(Type newValue) {
		setDelayTime(0, newValue);
		setDelayTime(1, newValue);
	}

	void setTailoff(bool newValue) {
		if (tailoff == newValue) return;
		tailoff = newValue;
	}

	void setEnabled(bool newValue) {
		if (enabled == newValue) return;
		enabled = newValue;
		if (!enabled) {
			if (!tailoff)
				for (int i = 0; i < delayLines.size(); i++)
					delayLines[i].clear();
		}
	}

	void setFilter(Type newValue, FilterType filterType_) {
		filterType = filterType_;
		if(filterType == FilterType::LowPassFilter)
			filterCoefs = juce::dsp::IIR::Coefficients<Type>::makeFirstOrderLowPass(sampleRate, newValue);
		else if (filterType == FilterType::HighPassFilter)
			filterCoefs = juce::dsp::IIR::Coefficients<Type>::makeFirstOrderHighPass(sampleRate, newValue);

		for (auto& f : filters) {
			f.coefficients = filterCoefs;
		}
	}

	template <typename ProcessContext>
	void process(const ProcessContext& context) noexcept {
		auto& inputBlock = context.getInputBlock();
		auto& outputBlock = context.getOutputBlock();
		auto numSamples = outputBlock.getNumSamples();
		auto numChannels = outputBlock.getNumChannels();

		jassert(inputBlock.getNumSamples() == numSamples);
		jassert(inputBlock.getNumChannels() == numChannels);

		for (size_t ch = 0; ch < numChannels; ++ch) {
			auto* input = inputBlock.getChannelPointer(ch);
			auto* output = outputBlock.getChannelPointer(ch);
			auto& dline = delayLines[ch];
			auto delayTime = delayTimesSample[ch];
			auto& filter = filters[ch];

			for (size_t i = 0; i < numSamples; ++i) {
				auto delayedSample = filter.processSample(dline.get(delayTime));
				auto inputSample = input[i];
				if (!enabled)
					inputSample = 0;
				auto dlineInputSample = std::tanh(inputSample + feedback * delayedSample);
				
				dline.push(dlineInputSample);
				auto outputSample = input[i] + wetLevel * delayedSample;
				output[i] = outputSample;
			}
		}
	}

private:
	std::array<DelayLine<Type>, maxNumChannels> delayLines;
	std::array<size_t, maxNumChannels> delayTimesSample;
	std::array<Type, maxNumChannels> delayTimes;
	Type feedback{ Type(0) };
	Type wetLevel{ Type(0) };
	std::array<juce::dsp::IIR::Filter<Type>, maxNumChannels> filters;
	typename juce::dsp::IIR::Coefficients<Type>::Ptr filterCoefs;
	FilterType filterType = delayFilterInitialType;

	Type sampleRate{ Type(48000) };
	Type maxDelayTime{ Type(2) };
	bool tailoff = true;
	bool enabled = true;

	void updateDelayLineSize() {
		auto delayLineSizeSamples = (size_t)std::ceil(maxDelayTime * sampleRate);

		for (auto& dline : delayLines)
			dline.resize(delayLineSizeSamples);
	}

	void updateDelayTime() noexcept {
		for (size_t ch = 0; ch < maxNumChannels; ++ch)
			delayTimesSample[ch] = (size_t)juce::roundToInt(delayTimes[ch] * sampleRate);
	}
};
