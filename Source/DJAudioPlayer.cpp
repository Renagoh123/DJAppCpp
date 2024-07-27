/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 8 Aug 2023 9:32:13am
    Author:  wyinxuan

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager) 
              : formatManager( _formatManager ), isFileLoaded(false) 
{

}

DJAudioPlayer::~DJAudioPlayer() {}

/** Tells the source to prepare for playing. */
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

/** Fetch subsequent blocks of audio data. */
void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}

/** Release any resources after playback has stopped. */
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

/** Load the audio file */
void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    // get the audio title from the URL
    audioTitle = getAudioTitleFromURL(audioURL);
    // create a reader for the auudio file
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader,true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        // Set the fileLoaded flag to true if loading was successful
        isFileLoaded = true;
    }
    else
    {
        // Set the fileLoaded flag to false if loading failed
        isFileLoaded = false;
    }
}

/** Set the gain(volume) of the audio. */
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
}

/** Set the speed (resampling ratio) of the audio playback.*/
void DJAudioPlayer::setSpeed(double ratio)
{
    //  check if the provided ratio is in the valid range (0 to 3.0)
    if (ratio <= 0 || ratio > 3.0)
    {
        // if it is out of bounds, rest it to the default value
        if (ratio < 0 || ratio > 3.0)
        {
            ratio = 1.0;
        }
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 3.0" << std::endl;
    }
    else {
        // adjusting the playback speed
        resampleSource.setResamplingRatio(ratio);
    }
}

/** Set the playback position in seconds. */
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

/** Set the playback position relative to the length of the audio. */
void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        // calculate the position in seconds based on the relative position
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

/** Play the audio */ 
void DJAudioPlayer::play()
{
    transportSource.start();
    DBG("file is working");
}

/** Pause playback */
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

/** Replay the audio */
void DJAudioPlayer::replay(bool shouldLoop)
{
    if (readerSource != nullptr)
    {
        readerSource->setLooping(shouldLoop);
    }
}

/** Get the current playback position in seconds. */
double DJAudioPlayer::getPosition()
{
    return transportSource.getCurrentPosition();
}

/** Get the relative position of the playhead */
double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

/** Returns the length of audio in seconds. */
double DJAudioPlayer::getLengthInSeconds()
{
    return transportSource.getLengthInSeconds();
}

/** Get the title of an audio file from its URL. */
juce::String DJAudioPlayer::getAudioTitleFromURL(const juce::URL& audioURL)
{
    return juce::File(audioURL.getLocalFile()).getFileNameWithoutExtension();
}

