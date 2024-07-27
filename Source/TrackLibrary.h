/*
  ==============================================================================

    TrackLibrary.h
    Created: 10 Sep 2023 7:42:56pm
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h> // Include necessary JUCE headers

class MusicLibrary
{
public:
    MusicLibrary();

    // Function to add a track to the music library
    void addTrack(const juce::File& trackFile);

    // Function to remove a track from the music library by track title
    void removeTrack(const juce::String& trackTitle);

    // Function to check if a track is in the music library
    bool isTrackInLibrary(const juce::String& trackTitle) const;

    // Function to get a list of all tracks in the library
    juce::Array<juce::String> getAllTracks() const;

private:
    juce::Array<juce::String> trackLibrary; // Store track titles in the library

    // You can add more data members or private helper functions as needed
};
