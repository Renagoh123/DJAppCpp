/*
  ==============================================================================

    WaveformDisplay.h
    Created: 9 Aug 2023 9:32:43am
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    /**
     * Constructor
       @param formatManager - Reference to the AudioFormatManager for handling audio formats
       @param cacheToUse: Reference to a shared AudioThumbnailCache object for catching audio thumbnail.
       @param _colour - The color used for the waveform display
     */
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse, 
                    juce::AudioThumbnailCache& cacheToUse,
                    juce::Colour _colour);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /** Callback function that is invoked when the change is received from the broadcaster.
        @param source The broadcaster sending the change signal.
     */ 
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
    /** Load the audio file to display waveform
        @param audioURL - URL of the audio file to load.
     */
    void loadURL(juce::URL audioURL);

    /** Updates the position of the playhead indicator on the waveform display.
        @param pos The relative position (between 0 and 1) to set.
    */
    void setPositionRelative(double pos);


private:
    /** Data MEMBERS */
    juce::AudioThumbnail audioThumbnail;
    juce::Colour waveFormColour;

    bool fileLoaded; // flag check if a file is successfully loaded
    double position; // current playhead pos
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
