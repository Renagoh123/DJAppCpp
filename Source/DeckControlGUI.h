/*
  ==============================================================================

    DeckControlGUI.h
    Created: 31 Aug 2023 4:20:06pm
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DeckControlGUI  : public juce::Component
{
public:
    DeckControlGUI();
    ~DeckControlGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckControlGUI)
};
