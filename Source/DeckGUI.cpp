/*
  ==============================================================================

    DeckGUI.cpp
    Created: 8 Aug 2023 11:23:12am
    Author:  wyinxuan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
           juce::AudioFormatManager& formatManagerToUse,
           juce::AudioThumbnailCache& cacheToUse,
           juce::Colour _colour)
               : player(_player), //assign _player to player data member
                 waveformDisplay(formatManagerToUse, cacheToUse,_colour), // call the constructor on waveform
                 deckColour(_colour), //assign _colour to deckColour data member
                 otherLookAndFeel(std::make_unique<OtherLookAndFeel>(_colour)) //initialize otherLookAndFeel with the provided colour
                 
{
    // Set the image to the button 
    // Images source from Freepik
    otherLookAndFeel->setImgToButton(playButton, "playback.png", deckColour);
    otherLookAndFeel->setImgToButton(stopButton, "stop.png", deckColour);
    otherLookAndFeel->setImgToButton(loadButton, "load.png", deckColour);
    otherLookAndFeel->setImgToButton(replayButton, "replay.png", deckColour);
   
    // apply custom look and feel settings to the slider
    otherLookAndFeel->sliderSettings(volSlider, juce::Slider::SliderStyle::LinearVertical, 40, 20, deckColour, juce::Colours::brown);
    otherLookAndFeel->sliderSettings(speedSlider, juce::Slider::SliderStyle::LinearVertical, 40,20, deckColour,juce::Colours::brown);
    otherLookAndFeel->posSliderSettings(posSlider, deckColour,juce::Colours::firebrick);
    otherLookAndFeel->labelSettings(volLabel, volSlider , "VOL");
    otherLookAndFeel->labelSettings(speedLabel, speedSlider, "SPD");
   

    // add buttons and sliders to make them visible.
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(replayButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(volLabel);
    addAndMakeVisible(speedLabel);

    // add listeners for click events.
    playButton.addListener(this);
    stopButton.addListener(this);
    replayButton.addListener(this);
    volSlider.addListener(this);
    posSlider.addListener(this);
    speedSlider.addListener(this);
    loadButton.addListener(this);

    // set the range for sliders
    volSlider.setRange(0, 1.0, 0.1);
    speedSlider.setRange(0, 3.0, 0.5);
    posSlider.setRange(0, 1.0);

    // start a timer
    startTimer(200);

}

/**Destruction will happen when the objects go out of scope. */
DeckGUI::~DeckGUI()
{
    // Timer stops running when the program destroys the DeckGUI objects.
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 0);   // draw an outline around the component

    g.setColour(juce::Colours::darkgrey);
    g.setFont(16.0f);
    
    // check if new audio is not loaded
    if (!newAudioLoaded)
    {
        // draw the title of (loaded) audio
        g.drawFittedText(player->audioTitle, juce::Rectangle< int >(posSlider.getX() * 2, posSlider.getY() * 1.45, 135, 80), 4, juce::Justification::centred, true); 
    }
    else 
    {
        // redraw the title of the new audio
        g.drawFittedText(player->audioTitle, juce::Rectangle< int >(posSlider.getX() * 2, posSlider.getY() * 1.45, 135, 80), 4, juce::Justification::centred, true);
        newAudioLoaded = false;
        repaint();
    }
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 12 * 3; 
    double btnY = rowH * 3.6;
    double btnW = getWidth() / 6;
    double btnH = rowH / 3;

    waveformDisplay.setBounds(0, 0, getWidth(), rowH);
    replayButton.setBounds(btnW, btnY, btnW, btnH);
    stopButton.setBounds(2 * btnW, btnY, btnW, btnH);
    playButton.setBounds(3 * btnW, btnY, btnW, btnH);
    loadButton.setBounds(4 * btnW, btnY, btnW, btnH);

    double sldY = rowH * 1.4;
    double sldW = getWidth() / 12;
    double sldH = rowH * 2.2;
    volSlider.setBounds(sldW, sldY, sldW, sldH);
    speedSlider.setBounds(getWidth() - sldW * 2, sldY, sldW, sldH);
    posSlider.setBounds(sldW * 2, sldY, sldW * 8, sldH); 
   
}

/** implement Button::Listener */
void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        // get the play button state
        isPlaying = playButton.getToggleState();
        // set the play button state is true
        playButton.setToggleState(!isPlaying, juce::NotificationType::dontSendNotification);

        if (!isPlaying)
        {
            player->play(); 
            // set the stop button state to false
            stopButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
        else{ player->stop(); }
    }

    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        // get the stop button state
        isPaused = stopButton.getToggleState();
        // set the stop button state is true
        stopButton.setToggleState(!isPaused, juce::NotificationType::dontSendNotification);

        if (!isPaused)
        {
            player->stop();
            // change the play button state to false
            playButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
    }

    if (button == &replayButton)
    {
        std::cout << "Replay button was clicked " << std::endl;
        // get the replay button state
        isReplaying = replayButton.getToggleState();
        // set the replay button state is true
        replayButton.setToggleState(!isReplaying, juce::NotificationType::dontSendNotification);
        player->replay(!isReplaying);  // toggle the replay mode in the player
    }

    if (button == &loadButton)
    {
        std::cout << "Load button was clicked " << std::endl;
        // launch the file chooser dialog.
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                // load the selected audio file.
                auto chosenFile = chooser.getResult();
                loadAudioFile(juce::URL{ chooser.getResult() });
            });
    }
}

/** implement Slider::Listener */
void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        // adjust the volume of the track based on the value of vol slider
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        // adjust the playback speed of the track based on the value of speed slider
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        // adjust the playback position of the track based on the value of pos slider
        player->setPositionRelative(slider->getValue());
    }
}

/** Drag-and-drop file handling.
  * Callback to check whether this target is interested in the set of files being offered.*/
bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag " << std::endl;
    return true;
}

/** Drag-and-drop file handling.
  * Callback to indicate that the user has dropped the files onto this component. */
void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        // load the dropped audio file into the player and waveform display components
        player->loadURL(juce::URL{ juce::File{files[0]} });
    }
}

/** Timer callback for updating the position of waveform display
 * based on the relative position of the audio playback in the DJAudioPlayer instance. */
void DeckGUI::timerCallback()
{
    // get the relative position of the audio playback
    double relativePosition = player->getPositionRelative();

    // check if the relative position is within the valid range (0.0, 1.0)
    if (relativePosition > 0.0 && relativePosition <1.0)
    {
        // update the waveform display and position slider positions
        waveformDisplay.setPositionRelative(relativePosition);
        posSlider.setValue(relativePosition);
    }
    else {
       //DBG("DeckGUI::timerCallback - Invalid relativePosition: ");
    }
}

/** Get the audio title from a given audio URL */
juce::String DeckGUI::getAudioTitle(const juce::URL& audioURL)
{
    return player->getAudioTitleFromURL(audioURL);
}

/** Public member function:
 * Load an audio file from a URL as input into the player
 * and waveform display for visualization 
*/
void DeckGUI::loadAudioFileToPlaylist(const juce::URL& audioURL)
{
    loadAudioFile(audioURL);
}

/** Private member function: 
 * Load an audio file from a URL as input into the player
 * and waveform display for visualization */
void DeckGUI::loadAudioFile(juce::URL audioURL)
{
    DBG("DeckGUI::loadAudioFile");
   
    player->loadURL(audioURL);  // Load the audio URL into the player
    waveformDisplay.loadURL(audioURL); // Load the audio URL into the waveform display
    newAudioLoaded = true;  // flag that new audio has been loaded
}
