/*
  ==============================================================================

    OtherLookAndFeel.cpp
    Created: 2 Sep 2023 6:12:17am
    Author:  wyinxuan

  ==============================================================================
*/

#include "OtherLookAndFeel.h"
OtherLookAndFeel::OtherLookAndFeel(juce::Colour _colourToUse) : colourToUse(_colourToUse) //assign _colourToUse to colourToUse data member 
{ 

}

/** Sets the images and colors for a image button. */
void OtherLookAndFeel::setImgToButton(juce::ImageButton& button, juce::StringRef relativePath, juce::Colour c)
{
    // access the relative path of image file 
    juce::File imageFile = juce::File::getCurrentWorkingDirectory()
        .getParentDirectory().getParentDirectory()
        .getChildFile("Assets")
        .getChildFile("Icons")
        .getChildFile(relativePath);
    // load the image from file 
    juce::Image buttonImage = juce::ImageFileFormat::loadFrom(imageFile);

    // set up the button img and colours
    button.setImages(true, true, true,
                     buttonImage, 1, juce::Colours::darkslategrey, // normalImage
                     juce::Image(nullptr), 1, juce::Colours::lightslategrey, // overImage
                     buttonImage, 1, c); //downImage
}

/** Configures settings for a rotary slider with custom colors and text box style. */
void OtherLookAndFeel::posSliderSettings(juce::Slider& slider, juce::Colour rotaryColour, juce::Colour thumbColour)
{
    // Configure as a rotary slider without a textbox.
    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    // Set slider colors.
    slider.setColour(juce::Slider::ColourIds::thumbColourId, thumbColour);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, rotaryColour);

    /**
     * Configure the slider to behave as a rotary control.
       @param startingAngle  Starting angle in radians. Sets the initial position of the slider (minimum value) to pi.
       @param endingAngle    Ending angle in radians. Defines the range for the slider's rotation (maximum value) to 3 * pi - 0.1 for a slightly smaller range.
       @param clockwise      Direction of rotation. If true, the slider rotates clockwise as it increases in value.
     */
    slider.setRotaryParameters(juce::MathConstants<float>::pi,
                               juce::MathConstants<float>::twoPi + juce::MathConstants<float>::pi - 0.1,
                               true);
}

/** Configures settings for a slider with custom colors and text box style. */
void OtherLookAndFeel::sliderSettings(juce::Slider& slider, juce::Slider::SliderStyle slider_style, 
                                      int textBoxWidth, int textBoxHeight,
                                      juce::Colour thumbColour, juce::Colour trackColour)
{
    // configure the style of slider and colours
    slider.setSliderStyle(slider_style);
    slider.setColour(juce::Slider::thumbColourId, thumbColour);
    slider.setColour(juce::Slider::trackColourId, trackColour);

    // style the textbox of slider
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, textBoxWidth, textBoxHeight);
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::grey);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::darkslategrey);
}

/** Configures settings for a juce::TextEditor used as a search bar. */
void OtherLookAndFeel::searchBarSettings(juce::TextEditor& searchBar,
                                        float fontSize,
                                        const juce::String& text)
{
    // set the font size for the search bar
    searchBar.setFont(16.0f);
    // set the text to display when the search bar is empty
    searchBar.setTextToShowWhenEmpty(text, juce::Colours::white);
}

/** Configures settings for a button used in a Playlist.*/
void OtherLookAndFeel::playlistButtonSettings(juce::Button& button, juce::Colour colour)
{
    // set the text color of the button to white
    button.setColour(juce::TextButton::textColourOffId,juce::Colours::white);
    // set the colour of the button
    button.setColour(juce::TextButton::buttonColourId, colour);
}

/** Configures settings for a button used for sampler instruments. */ 
void OtherLookAndFeel::samplerInstrumentsButtonSettings(juce::Button& button, juce::Colour colour)
{
    // set the text color of the button to black
    button.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    // set the colour of the button
    button.setColour(juce::TextButton::buttonColourId, colour);
}

/** Configures settings for a label used for sliders. */
void OtherLookAndFeel::labelSettings(juce::Label& label, juce::Slider& slider, const juce::String& labelName)
{
    // set the text color of the button to black
    label.setColour(juce::Label::textColourId, juce::Colours::darkgrey);
    // set the position of text
    label.setJustificationType(juce::Justification::horizontallyJustified);
    // set this label "stick to" a slider
    label.attachToComponent(&slider, false);
    // set the label name
    label.setText(labelName, juce::dontSendNotification);
}