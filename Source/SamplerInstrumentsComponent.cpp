/*
  ==============================================================================

    SamplerInstrumentsComponent.cpp
    Created: 11 Sep 2023 10:16:39am
    Author:  wyinxuan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SamplerInstrumentsComponent.h"

//==============================================================================
SamplerInstrumentsComponent::SamplerInstrumentsComponent(DJAudioPlayer* _player): player(_player)
{
    // apply custom look and feel settings to the button
    otherLookAndFeel->samplerInstrumentsButtonSettings(sampler1btn, juce::Colours::firebrick);
    otherLookAndFeel->samplerInstrumentsButtonSettings(sampler2btn, juce::Colours::orange);
    otherLookAndFeel->samplerInstrumentsButtonSettings(sampler3btn, juce::Colours::dodgerblue);
    otherLookAndFeel->samplerInstrumentsButtonSettings(sampler4btn, juce::Colours::whitesmoke);

    // add buttons to the component and make them visible.
    addAndMakeVisible(sampler1btn);
    addAndMakeVisible(sampler2btn);
    addAndMakeVisible(sampler3btn);
    addAndMakeVisible(sampler4btn);

    // add button listeners for click events.
    sampler1btn.addListener(this);
    sampler2btn.addListener(this);
    sampler3btn.addListener(this);
    sampler4btn.addListener(this);
  
    // load sampler objects
    createObj();
  
}

SamplerInstrumentsComponent::~SamplerInstrumentsComponent() {}

void SamplerInstrumentsComponent::paint (juce::Graphics& g)
{

    g.fillAll (juce::Colours::dimgrey);   // clear the background

    g.setColour (juce::Colours::darkgrey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::lightgoldenrodyellow);
    g.setFont (18.0f);
    g.drawText ("Sampler Instruments", 5,10,getWidth(), 20,
                juce::Justification::centred, true);   // draw some placeholder text
}

void SamplerInstrumentsComponent::resized()
{
    int xPos = 50;
    int yPos = 40;
    double rowH = getHeight() / 3;
    double colW = getWidth() / 3;

    sampler1btn.setBounds(xPos, yPos, colW, rowH);
    sampler2btn.setBounds(xPos + getWidth() / 3, yPos, colW, rowH);
    sampler3btn.setBounds(xPos, yPos + rowH, colW, rowH);
    sampler4btn.setBounds(xPos + getWidth() / 3, yPos + rowH, colW, rowH);
}

void SamplerInstrumentsComponent::buttonClicked(juce::Button* button)
{
    // Check which button was clicked and trigger the appropriate sampler
    if (button == &sampler1btn)
    {
        DBG("SamplerInstrumentsComponent::sampler1 button was clicked");
        playSampler("drum");
    }

    if (button == &sampler2btn)
    {
        DBG("SamplerInstrumentsComponent::sampler2 button was clicked");

        playSampler("eguitar");
    }
    if (button == &sampler3btn)
    {
        DBG("SamplerInstrumentsComponent::sampler3 button was clicked");
        playSampler("violin");
    }
    if (button == &sampler4btn)
    {
        DBG("SamplerInstrumentsComponent::sampler4 button was clicked");
        playSampler("flute");
    }
    
}

/** Access the source of instrument samplers.
 ** Initialize each sampler into a `Track` objects and store them in the `samplers` vector with `Track` objects.
  * Each Track represents a sampler instrument.
 */
void SamplerInstrumentsComponent::createObj()
{
    // create a `samplersFile` vector with File object
    std::vector<juce::File> samplersFile;

    // define file paths for each sampler
    juce::File sampler1File = juce::File::getCurrentWorkingDirectory()
        .getParentDirectory().getParentDirectory()
        .getChildFile("Assets")
        .getChildFile("Samplers")
        .getChildFile("drum.wav");
    juce::File sampler2File = juce::File::getCurrentWorkingDirectory()
        .getParentDirectory().getParentDirectory()
        .getChildFile("Assets")
        .getChildFile("Samplers")
        .getChildFile("eguitar.wav");
    juce::File sampler3File = juce::File::getCurrentWorkingDirectory()
        .getParentDirectory().getParentDirectory()
        .getChildFile("Assets")
        .getChildFile("Samplers")
        .getChildFile("violin.wav");
    juce::File sampler4File = juce::File::getCurrentWorkingDirectory()
        .getParentDirectory().getParentDirectory()
        .getChildFile("Assets")
        .getChildFile("Samplers")
        .getChildFile("flute.wav");
 
    // add sampler files to the list
    samplersFile.push_back(sampler1File);
    samplersFile.push_back(sampler2File);
    samplersFile.push_back(sampler3File);
    samplersFile.push_back(sampler4File);

    // iterate the `samplersFile` vector and add them to the `samplers` vector 
    for (const juce::File& samplerFile : samplersFile)
    {
        juce::String samplerTitle = player->getAudioTitleFromURL(juce::URL{ samplerFile });
        juce::String samplerURL = juce::URL{ samplerFile }.toString(false);

        // create a Track object and add it to the array.
        Track newSampler{ samplerTitle, samplerURL };
        samplers.push_back(newSampler);
    }

}

/** Plays the sampler with the specified title */
void SamplerInstrumentsComponent::playSampler(const juce::String& samplerTitle)
{
    // find the sampler with the matching sampler title.
    for (int i = 0; i < samplers.size(); i++)
    {
        // check if the title of sampler match with desired sampler title
        if (samplers[i].title == samplerTitle)
        {
            // load the sampler file
            player->loadURL(samplers[i].url);
            DBG("url:" + samplers[i].url);

            // check if the sampler file is loaded successfully.
            if (player->isFileLoaded)
            {
                // start playing the loaded audio.
                player->play();
                DBG("SamplerInstrumentsComponent::" + samplerTitle + " sampler is playing");
            }
            else
            {
                DBG("SamplerInstrumentsComponent::" + samplerTitle + "sampler failed to load the file");
            }
        }
    }
}





