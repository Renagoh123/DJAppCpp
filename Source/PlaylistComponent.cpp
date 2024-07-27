/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 18 Aug 2023 1:36:44pm
    Author:  wyinxuan

  ==============================================================================
*/

#include <JuceHeader.h>
#include <optional>

#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(juce::AudioFormatManager& _formatManager, DeckGUI* _deckGUI1, DeckGUI* _deckGUI2)
                 : formatManger(_formatManager), deckGUI1(_deckGUI1), deckGUI2(_deckGUI2)
{
    // apply custom look and feel settings to the slider
    otherLookAndFeel->searchBarSettings(searchBar, 16.0f, " Search Track ");
    otherLookAndFeel->playlistButtonSettings(loadInPlayer1Btn, deckGUI1->deckColour);
    otherLookAndFeel->playlistButtonSettings(loadInPlayer2Btn, deckGUI2->deckColour);

    // add buttons and editable text box to make them visible.
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(importTrackBtn);
    addAndMakeVisible(loadInPlayer1Btn);
    addAndMakeVisible(loadInPlayer2Btn);
    addAndMakeVisible(searchBar);

    // add listeners for click events.
    tableComponent.setModel(this);
    importTrackBtn.addListener(this);
    loadInPlayer1Btn.addListener(this);
    loadInPlayer2Btn.addListener(this);
    searchBar.addListener(this);
   
    // add header for the table
    tableComponent.getHeader().addColumn("Tracks List", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 30);
    
}

PlaylistComponent::~PlaylistComponent() {}

void PlaylistComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(16.0f);
    g.drawText("PlaylistComponent", getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
    
}

void PlaylistComponent::resized()
{
    double rowH = getHeight() / 10;
    double btnY = rowH * 8;
    double btnW = getWidth() / 2;

    searchBar.setBounds(0, 0, getWidth()/1.5, rowH);
    importTrackBtn.setBounds(getWidth() / 1.5, 0, getWidth()/3, rowH);
    tableComponent.setBounds(0, 30,getWidth(), getHeight() - rowH * 3);
    loadInPlayer1Btn.setBounds(0, btnY, btnW, rowH);
    loadInPlayer2Btn.setBounds(btnW, btnY, btnW, rowH);
    
}
int PlaylistComponent::getNumRows() { return tracks.size(); }

void PlaylistComponent::paintRowBackground(juce::Graphics& g,
                                                int rowNumber,
                                                int width,
                                                int height,
                                                bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::firebrick);
    }
    else {
        g.fillAll(juce::Colour::fromRGBA(255, 250, 240, 255));
        
    }
}

void PlaylistComponent::paintCell(juce::Graphics& g,
                                        int rowNumber,
                                        int columnId,
                                        int width,
                                        int height,
                                        bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.setColour(juce::Colour::fromRGBA(255, 250, 240, 255));
    }
    else {
        g.setColour(juce::Colours::black);
    }

    g.drawText(tracks[rowNumber].title,
        2, 0,
        width - 4, height,
        juce::Justification::centredLeft,
        true);
}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                            int columnId,
                                                            bool isRowSelected,
                                                            juce::Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        // check if there is no existing component in the cell
        if (existingComponentToUpdate == nullptr)
        {
            // create a TextButton 
            juce::TextButton* btn = new juce::TextButton{ "X" };
            // convert the row number to a string for id
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
            // store the created TextButton into existingComponentToUpdate
            existingComponentToUpdate = btn;
        }
    }

    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if (button == &importTrackBtn)
    {
        DBG("PlaylistComponent::buttonClicked - Import track button was clicked");
 
        // launch the file chooser dialog.
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                // iterate through all the selected files
                for (const auto& file : chooser.getResults())
                {
                    // add the selected file to the playlist
                    juce::File trackFile{ file };
                    addTrack(trackFile);
                    
                }
             });

    }
    else if (button == &loadInPlayer1Btn)
    {
        DBG("PlaylistComponent::buttonClicked - Load to Deck1 button was clicked");
        loadInPlayer(deckGUI1);  // load the selected track into deck1
        
    }
    else if (button == &loadInPlayer2Btn)
    {
        DBG("PlaylistComponent::buttonClicked - Load to Deck2 button was clicked");
        loadInPlayer(deckGUI2);  // load the selected track into deck2
    }
    else
    {
        // remove a track based on the button's component ID
        int id = std::stoi(button->getComponentID().toStdString());
        removeTrack(id);
        // update the table after removing the track.
        tableComponent.updateContent();
    }
}

/** Drag-and-drop file handling.
  * Callback to check whether this target is interested in the set of files being offered.*/
bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
    std::cout << "PlaylistComponent::isInterestedInFileDrag " << std::endl;
    return true;
}

/** Drag-and-drop file handling.
  * Callback to indicate that the user has dropped the files onto this component. */
void PlaylistComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
    std::cout << "PlaylistComponent::filesDropped" << std::endl;
    // iterate through the dropped files and add each track
    for (const auto& file : files)
    {
        juce::File trackFile{ file };
        addTrack(trackFile);
    }

}

/** Convert the track file into Track object and add it into the `tracks` vector  */
void PlaylistComponent::addTrack(const juce::File& trackFile)
{
    DBG("PlaylistComponent::addTrack");
    // get the title and URL of the track from the file.
    juce::String trackTitle = deckGUI1->getAudioTitle(juce::URL{ trackFile });
    juce::String trackURL = juce::URL{ trackFile }.toString(false);

    // check if the track is not already in the playlist.
    if (!isTrackInPlayList(trackTitle))
    {
        // create a new Track object and add it into the playlist.
        Track newTrack{ trackTitle, trackURL };
        tracks.push_back(newTrack);
        // update the table content
        tableComponent.updateContent();
    }
    else { DBG(trackTitle << " is already loaded"); }
}

/** Check if a track is in the playlist.*/
bool PlaylistComponent::isTrackInPlayList(const juce::String& trackTitle) const
{
    DBG("PlaylistComponent::isTrackInPlayList");
    // check if the track is already in the playlist 
    for (const auto& t : tracks)
    {
        if (t.title == trackTitle)
        {
            // return true is found the track in the playlist
            return true;
        }
    }
    return false;
}

/** Remove a track from the playlist */
void PlaylistComponent::removeTrack(int id)
{
    DBG("PlaylistComponent::removeTrack");
    // remove a track at the specified index from the playlist
    tracks.erase(tracks.begin() + id);
}

/** Load a selected track into a specified player. */
void PlaylistComponent::loadInPlayer(DeckGUI* deckGUI)
{
    DBG("PlaylistComponent::loadInPlayer");
    // get the selected row from the table component.
    std::optional<int> selectedRow = tableComponent.getSelectedRow();

    if (selectedRow.has_value())
    {
        // load the selected track into the deck 
        deckGUI->loadAudioFileToPlaylist(tracks[selectedRow.value()].url);
    }
}

/** Search the title of track in the playlist that matches the input string. */
int PlaylistComponent::getMatchingTrackIndex(juce::String input)
{
    // Initialize trackIndex to -1 to indicate "no match found" initially
    int trackIndex = -1;

    // Loop through the tracks and look for a matching title
    for (int index = 0; index < tracks.size(); ++index)
    {
        if (tracks[index].title.contains(input))
        {
            // If a match is found, assign the index to trackIndex
            trackIndex = index;
            break;  // Exit the loop when a match is found.
        }
    }
    // Return the index, which could be -1 if no match was found
    return trackIndex;
}


/** Called when the user changes the text in the search bar.
  * It updates the search results in the searhbar based on the search input.*/
void PlaylistComponent::textEditorTextChanged(juce::TextEditor& editor)
{
    // get the text in the search bar
    searchBarInput = editor.getText();
    bool foundMatch = false;  // Flag to track if a match is found
    int trackIndex = 0;  // Initialize trackIndex

    // check if the search bar contains any input
    if (!searchBarInput.isEmpty())
    {
        // Find the first matching track.
        for (; trackIndex < tracks.size(); ++trackIndex)
        {
            if (tracks[trackIndex].title.contains(searchBarInput))
            {
                foundMatch = true;
                break;  // Exit the loop when a match is found.
            }
        }

        // If a match is found, select the row.
        if (foundMatch)
        {
            tableComponent.selectRow(trackIndex);
        }
        else
        {
            tableComponent.deselectAllRows();
        }
    }
    else
    {
        tableComponent.deselectAllRows();
    }

    // Update the table to display the search results.
    tableComponent.updateContent();
}


