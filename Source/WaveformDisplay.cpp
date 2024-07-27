/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 9 Aug 2023 9:32:43am
    Author:  wyinxuan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                juce::AudioThumbnailCache& cacheToUse,
                                juce::Colour _colour)
                : audioThumbnail(1000, formatManagerToUse, cacheToUse), // create an AudioThumbnail
                  fileLoaded(false), // initialize fileLoaded to false 
                  position(0), // initalize position to 0
                  waveFormColour(_colour) //assign _colour to waveFormColour data member
{
    // change listener for audioThumbnail
    audioThumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 0);   // draw an outline around the component
   
    g.setColour(waveFormColour);

    // check if audio file is loaded
    if (fileLoaded)
    {
        // draw the waveform
        audioThumbnail.drawChannel(g, getLocalBounds(), 0, audioThumbnail.getTotalLength(), 0, 1.0f);
        // draw a playhead indicator
        g.setColour(juce::Colours::indianred);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        // draw a text if no audio file loaded
        g.setFont(20.0f);
        g.drawText("Waveform Here!", getLocalBounds(),juce::Justification::centred, true);   // draw some placeholder text
    }
    
}

void WaveformDisplay::resized() {}

/** Callback function that is invoked when the change is received from the broadcaster. */
void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    std::cout << "wfd: change received! " << std::endl;
    repaint(); // update the display
}

/** Load the audio file to display waveform */
void WaveformDisplay::loadURL(juce::URL audioURL)
{
    audioThumbnail.clear(); //clear the exsiting audioThumbnail

    // set the source for the audioThumbnail using the provided audioURL.
    fileLoaded = audioThumbnail.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        std::cout << "wfd: loaded! " << std::endl;
        repaint(); // display the waveform
    }
    else {
        std::cout << "wfd: not loaded! " << std::endl;
    }
}

/** Updates the position of the playhead indicator on the waveform display. */
void WaveformDisplay::setPositionRelative(double pos)
{
    // check if the new position is different from the current position
    if (pos != position)
    {
        // update the position
        position = pos;
        // repaint the waveform display
        repaint();
    }
}