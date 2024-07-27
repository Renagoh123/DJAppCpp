/*
  ==============================================================================

    SamplerInstrumentsComponent.h
    Created: 11 Sep 2023 10:16:39am
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "Track.h"
#include "OtherLookAndFeel.h"

//==============================================================================
/*
*/
class SamplerInstrumentsComponent  : public juce::Component,
                                     public juce::Button::Listener                                
{
public:
    /**
     * Constructor
        @param _player: Pointer to the unique DJAudioPlayer for the SamplerInstrumentsComponent.
     */
    SamplerInstrumentsComponent(DJAudioPlayer* _player);
    ~SamplerInstrumentsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener */
    void buttonClicked(juce::Button* button) override;

private:

    /** Access the source of instrument samplers.
      * Initialize each sampler into a `Track` objects and store them in the `samplers` vector with `Track` objects.
      * Each Track represents a sampler instrument.
    */
    void createObj();

    /** Plays the sampler with the specified title
        @param samplerTitle the title of sampler to play 
    */
    void playSampler(const juce::String& samplerTitle);

    // Vector to store samplers 
    std::vector<Track> samplers;

    // Data Member 
    // Button for different sampler instruments 
    juce::TextButton sampler1btn{ "Drum" };
    juce::TextButton sampler2btn{ "E-guitar" };
    juce::TextButton sampler3btn{ "Violin" };
    juce::TextButton sampler4btn{ "Flute" };

    DJAudioPlayer* player;

    // Unique pointer to manage look and feel for DeckGUI components
    std::unique_ptr<OtherLookAndFeel> otherLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerInstrumentsComponent)
};
