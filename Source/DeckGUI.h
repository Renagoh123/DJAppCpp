/*
  ==============================================================================

    DeckGUI.h
    Created: 8 Aug 2023 11:23:12am
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "OtherLookAndFeel.h"
//==============================================================================
/*
*/
class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer
{
public:
    /**
     * Constructor
        @param _player: Pointer to the unique DJAudioPlayesr for the deck.
        @param formatManagerToUse: Reference to a shared AudioFormatManager object for handling audio formats.
        @param cacheToUse: Reference to a shared AudioThumbnailCache object for catching audio thumbnail.
     */
    DeckGUI(DJAudioPlayer* _player,
      juce::AudioFormatManager& formatManagerToUse,
      juce::AudioThumbnailCache& cacheToUse,
      juce::Colour _colour);
    ~DeckGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener */
    void buttonClicked(juce::Button*) override;

    /** implement Slider::Listener */
    void sliderValueChanged(juce::Slider* slider) override;

    /** 
     * Drag-and-drop file handling.
     * Callback to check whether this target is interested in the set of files being offered.
     * Callback to indicate that the user has dropped the files onto this component.
     */
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /**
     * Timer callback for updating the position of waveform display 
     * based on the relative position of the audio playback in the DJAudioPlayer instance.
     */
    void timerCallback() override;

    /** Get the audio title from a given audio URL 
      * Return the title of the audio file without the file extension.
        @param audioURL - URL of the audio file to load.
    */
    juce::String getAudioTitle(const juce::URL& audioURL);
    
    /** Load an audio file to playlist for visualizing player and waveform displays.
     * This function is a wrapper which delegate the loading process to 
     * the private member function loadAudioFile(audioURL) function.
       @param audioURL - Reference to a shared URL of the audio file to load
     */
    void loadAudioFileToPlaylist(const juce::URL& audioURL);

    // Data member (for public use)
    juce::Colour deckColour;
    
private:
    /** 
     * Load an audio file from a URL as input into the player 
     * and waveform display for visualization.
       @param audioURL - URL of the audio file to load.
     */
    void loadAudioFile(juce::URL audioURL);
    
    // Importing audio files 
    juce::FileChooser fChooser{ "Select a file..." };

    // Data Member 
    // Button for controlling playback
    juce::ImageButton playButton{ "PLAY" };
    juce::ImageButton stopButton{ "STOP" };
    juce::ImageButton loadButton{ "LOAD" };
    juce::ImageButton replayButton{ "REPLAY" };
  
    // Sliders for volume, speed and position 
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
   
    juce::Label volLabel;
    juce::Label speedLabel;

    // Flag indicating the state of button
    bool isReplaying; 
    bool isPlaying;
    bool isPaused;
 
    // Flag indicating if new audio has been loaded into the deck
    bool newAudioLoaded;

    WaveformDisplay waveformDisplay;
    DJAudioPlayer* player;
    
    // Unique pointer to manage look and feel for DeckGUI components
    std::unique_ptr<OtherLookAndFeel> otherLookAndFeel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
