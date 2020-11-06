#pragma once

#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "GameState.h"
#include "Globals.h"
#include "Loading.h"

class MenuState : public GameState
{
public:
    /*
        Constructor to load sprites when initialised
        Arguments:
        1) game pointer
    */
    MenuState(Game* game);

    /*
        Draw sprite in window
    */
    virtual void draw(const float dt);
    /*
        Update inputs when window is open
    */
    virtual void update(const float dt) {};
    /*
        Handle inputs based on changes made in update
    */
    virtual void handleInput();

private:
    /*
        Texture object
    */
    sf::Texture menuTexture;
    /*
        Sprite object
    */
    sf::Sprite menuSprite;
    /*
        Font object
    */
    sf::Font font;
    /*
        Text object
    */
    sf::Text menuFont, titleFont;
    /*
        Array to store Text object
    */
    std::vector<sf::Text> buttons;
    /*
        Buffer object
    */
    sf::SoundBuffer start_buffer;
    /*
        Sound object
    */
    sf::Sound start_sound;

    const int NUM_BUTTONS = 2;
    /*
        Checks if Text is clicked
        Arguments:
        1) Text object
    */
    bool isTextClicked(sf::Text text);
    /*
        Pushes next state into GameState array
    */
    void loadState();
};

#endif /* GAME_STATE_START_HPP */