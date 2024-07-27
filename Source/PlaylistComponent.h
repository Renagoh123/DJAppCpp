/*
  ==============================================================================

    PlaylistComponent.h
    Created: 18 Aug 2023 1:36:44pm
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

#include "DeckGUI.h"
#include "Track.h"
#include "OtherLookAndFeel.h"
//==============================================================================
/*
*/
class PlaylistComponent : public juce::Component,
                          public juce::TableListBoxModel,
                          public juce::Button::Listener,
                          public juce::FileDragAndDropTarget,
                          public juce::TextEditor::Listener           
{
public:
    PlaylistComponent(juce::AudioFormatManager& _formatManager, DeckGUI* _deckGUI1, DeckGUI* _deckGUI2);
    ~PlaylistComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    /** Returns the number of rows in the table */
    int getNumRows() override;

    /** Provides graphical code which draws the background of a row in the table */
    void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;

    /** Contains graphical code which draws the contents of individual cells */
    void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    /** Create or update a custom component to go in a cell. */
    juce::Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) override;

    /** Implement Button::Listener */
    void buttonClicked(juce::Button* button) override;

    /**
     * Drag-and-drop file handling.
     * Callback to check whether this target is interested in the set of files being offered.
     * Callback to indicate that the user has dropped the files onto this component.
     */
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /** Called when the user changes the text in the search bar.
     * It updates the search results in the searchbar based on the search input.
       @param editor - The TextEditor component that triggered the callback.
     */
    void textEditorTextChanged(juce::TextEditor&) override;


private:

    /** Convert the track file into Track object and add it into the `tracks` vector
        @param trackFile - The file representing the track to be added
    */
    void addTrack(const juce::File& trackFile);

    /** Check if a track is in the playlist.
      * Return True if the track is in the playlist, False otherwise.
        @param trackTitle - The title of the track to search for.
     */
    bool isTrackInPlayList(const juce::String& trackTitle) const;

    /** Remove a track from the playlist
        @param id - The index of the track to remove from the playlist */
    void removeTrack(int id);

    /** Load a selected track into a specified player
        @param DeckGUI - A pointer to the DeckGUI where the track will be loaded. */
    void loadInPlayer(DeckGUI* deckGUI);

    /** Search the title of track in the playlist that matches the input string.
      * Return The index of the matching track or -1 if no match is found.
        @param input - The input string to search for in track titles.
     */
    int getMatchingTrackIndex(juce::String input);

    // Table component for displaying the playlist
    juce::TableListBox tableComponent;
 
    // Vector to store Track object
    std::vector<Track> tracks;
 
    // Buttons for importing, loading to Deck1 and Deck 2
    juce::TextButton importTrackBtn{ "Import To Track Library" };
    juce::TextButton loadInPlayer1Btn{ "To Deck1" };
    juce::TextButton loadInPlayer2Btn{ "To Deck2" };

    // Text editor for searching tracks in the playlist
    juce::TextEditor searchBar{"Search: "};
    juce::String searchBarInput;

    // Importing audio file
    juce::FileChooser fChooser{ "Select a file..." };

    // Data Memebers
    juce::AudioFormatManager& formatManger;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;

    // Unique pointer to manage look and feel for DeckGUI components
    std::unique_ptr<OtherLookAndFeel> otherLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
