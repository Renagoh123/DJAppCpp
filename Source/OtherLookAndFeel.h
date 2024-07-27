/*
  ==============================================================================

    OtherLookAndFeel.h
    Created: 2 Sep 2023 6:12:17am
    Author:  wyinxuan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    /** Constructor 
      @params _colorToUse 
     */
    OtherLookAndFeel(juce::Colour _colourToUse);

    //==============================================================================
    /**
     * Sets the images and colors for a image button.
       @param button          The juce::ImageButton to set images and colors for.
       @param relativePath    The relative path to the image file
       @param c               The custom color to apply to the button.
     */
    void setImgToButton(juce::ImageButton& button, juce::StringRef relativePath, juce::Colour c);
    
    /**
    * Configures settings for a rotary slider with custom colors and text box style.
      @param slider         The juce::Slider to configure.
      @param slider_style   The style of the slider.
      @param textBoxWidth   The width of the text box.
      @param textBoxHeight  The height of the text box.
      @param thumbColour    The color for the slider thumb.
      @param trackColour    The color for the slider track.
     */
    void posSliderSettings(juce::Slider& slider, juce::Colour rotaryColour, juce::Colour thumColour);
    
    /**
     * Configures settings for a slider with custom colors and text box style.
       @param slider         The juce::Slider to configure.
       @param slider_style   The style of the slider.
       @param textBoxWidth   The width of the text box.
       @param textBoxHeight  The height of the text box.
       @param thumbColour    The color for the slider thumb.
       @param trackColour    The color for the slider track.
     */
    void sliderSettings(juce::Slider& slider,juce::Slider::SliderStyle slider_style, 
                        int textBoxWidth, int textBoxHeight,
                        juce::Colour thumbColour, juce::Colour trackColour);

    /**
     * Configures settings for a juce::TextEditor used as a search bar.
       @param searchBar  The juce::TextEditor to configure as a search bar.
       @param fontSize   The font size for the search bar.
       @param text       The text to display when the search bar is empty.
     */
    void searchBarSettings(juce::TextEditor& searchBar, float fontSize, const juce::String& text);

    /**
     * Configures settings for a button used in a Playlist.
       @param button  The juce::Button to configure for use in a Playlist
       @param colour  The color of the button.
     */
    void playlistButtonSettings(juce::Button& button, juce::Colour colour);

    /**
     * Configures settings for a button used for sampler instruments.
       @param button  The juce::Button to configure for sampler instruments.
       @param colour  The color of the button.
     */
    void samplerInstrumentsButtonSettings(juce::Button& button, juce::Colour colour);

    /** Configures settings for a label used for sliders. 
        @param label  The juce::Label to configure for sliders.
        @param slider  The juce::Slider to configure that label sticks to
        @param labelName   The label name to display
    */
    void OtherLookAndFeel::labelSettings(juce::Label& label, juce::Slider& slider, const juce::String& labelName);
private:
    // DATA MEMBERS 
    juce::Colour colourToUse;
};