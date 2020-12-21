#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Globals.h"

class GameState; // Declaration

class Game
{
public:
    /*
        Flag to check for pause game
    */
    bool Pause = false;
    /*
        RenderWindow object to create window
    */
    sf::RenderWindow window;

    /*
        Constructor to create window
    */
    Game();
    /*
        Destructor to delete all states
    */
    ~Game();
    /*
        Pushes new state pointer into vector states
        Argument:
        1) GameState pointer
    */
    void pushState(GameState* state);
    /*
        Delete states from vector states
    */
    void popState();
    /*
        Retrieve current state from vector state
    */
    GameState* CurrentState();
    /*
        Main game loop
    */
    void gameLoop();

private:
    /*
        An array to store GameState pointers
    */
    std::vector<GameState*> states;
    /*
        SoundBuffer object to create window
    */
    sf::SoundBuffer loopBuffer;
    /*
        Sound object to create window
    */
    sf::Sound loopSound;
};

#endif /* GAME_HPP */
