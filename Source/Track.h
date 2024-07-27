/*
  ==============================================================================

    Track.h
    Created: 28 Aug 2023 11:04:22am
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Track
{
public:
    /**
     * Constructor
       @param _title: The title of the track.
       @param _url: The URL of the track.
     */
    Track(juce::String _title, juce::String _url);
    ~Track();

    /** DATA MEMBERS */
    juce::String title;
    juce::String url;
};