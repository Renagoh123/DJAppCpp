#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "SamplerInstrumentsComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    juce::AudioFormatManager formatManager;
    // note we need to tell it how large the cache is. 20 files are ok for now 
    juce::AudioThumbnailCache thumbnailCache{100};

    // DJAudioPlayer and DeckGUI for the first player
    DJAudioPlayer player1{ formatManager };
    DeckGUI deckGUI1{ &player1, formatManager, thumbnailCache, juce::Colours::orange};
    
    // DJAudioPlayer and DeckGUI for the second player
    DJAudioPlayer player2{ formatManager };
    DeckGUI deckGUI2{ &player2, formatManager, thumbnailCache, juce::Colours::dodgerblue };

    // PlaylistComponent for managing playlist with references to the first deck and second deck
    PlaylistComponent playlistComponent{formatManager, &deckGUI1, &deckGUI2};

    // SamplerInstrumentsComponent for sampler instruments, 
    // with a reference to the DJAudioPlayer.
    DJAudioPlayer playerForSamplerInstruments{ formatManager };
    SamplerInstrumentsComponent samplerInstrument{&playerForSamplerInstruments };
    
    // Mixer for audio sources
    juce::MixerAudioSource mixerSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

