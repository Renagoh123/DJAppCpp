/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 8 Aug 2023 9:32:13am
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource {
public:
    /**
     * Constructor
       @param formatManager - Reference to the AudioFormatManager for handling audio formats
     */
    DJAudioPlayer(juce::AudioFormatManager& formatManager);
    ~DJAudioPlayer();

    /** Tells the source to prepare for playing. */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /** Fetch subsequent blocks of audio data. */
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    /** Release any resources after playback has stopped. */
    void releaseResources() override;

    /** Load the audio file 
        @param audioURL - URL of the audio file to load. */
    void loadURL(juce::URL audioURL);

    /** Set the gain(volume) of the audio.
        @param gain - gain value between 0 and 1. */
    void setGain(double gain);

    /** Set the speed (resampling ratio) of the audio playback.
        @param ratio - speed ratio between 0 and 100. */
    void setSpeed(double ratio);

    /** Set the playback position in seconds.
        @param posInSecs - the playback position in second.
    */
    void setPosition(double posInSecs);

    /** Set the playback position relative to the length of the audio.
        @param pos - the relative position between 0 and 1.
    */
    void setPositionRelative(double pos);

    /** Play the audio */ 
    void play();

    /** Pause playback */
    void stop();
    
    /** Replay the audio 
        @param isLooping - If true, the audio will loop; Otherwise, it will play once.
     */
    void replay(bool IsLooping);
   
    /** Get the current playback position in seconds. */
    double getPosition();

    /** Get the relative position of the playhead */
    double getPositionRelative();
    
    /** Returns the length of audio in seconds.*/
    double getLengthInSeconds();

    /** Get the title of an audio file from its URL.
     *  Return the title of the audio file without the file extension.
        @param audioURL - URL of the audio file to load.
    */
    juce::String getAudioTitleFromURL(const juce::URL& audioURL);

    //  The title of the currently loaded audio 
    juce::String audioTitle;

    // Flag indicating the state of file is loaded 
    bool isFileLoaded;

private:
    // Reference to the manager for handling different audio formats.
    juce::AudioFormatManager& formatManager;
    // Unique pointer to manage the reader source for audio file reading.
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    // Audio transport source for playback control.
    juce::AudioTransportSource transportSource;
    // Resampling audio source handles resampling of audio data.
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

};
