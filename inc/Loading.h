#pragma once

#ifndef LOAD_HPP
#define LOAD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "GameState.h"
#include "PlayState.h"
#include "Globals.h"

class LoadState : public GameState
{
private:
    /*
        SoundBuffer object
    */
    sf::SoundBuffer loadBuffer;
    /*
        Sound object
    */
    sf::Sound loadSound;
    /*
        Texture object
    */
    sf::Texture loadTexture;
    /*
        Sprite object
    */
    sf::Sprite loadSprite;
    /*
        Font object
    */
    sf::Font loadFont;
    /*
        Text object
    */
    sf::Text loadText;
    /*
        Array to store Text object
    */
    std::vector<sf::Text> countdown;
    /*
        Array to store Color object
    */
    std::vector<sf::Color> colour = { sf::Color::Red, sf::Color::Yellow, sf::Color::Green, sf::Color::Black };

    const int COUNT = 4;
    /*
        Reset variables to original state
    */
    void resetState();

public:
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput() {};

    LoadState(Game* game);
    /*
        Push to PlayState
    */
    void playGame();
};

#endif