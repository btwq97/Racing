#pragma once

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Game.h"

class Game; // Declaration

class GameState
{
protected:
    /*
        Protected allows the game pointer to be accessed in every child class (just like public does), but we can't access it if the class is not a child (so Resource Manager can't access it for example)
    */
    Game* game;
public:
    /*
        Virtual object
        Draw sprite in window
    */
    virtual void draw(const float dt) = 0;
    /*
        Virtual object
        Update inputs when window is open
    */
    virtual void update(const float dt) = 0;
    /*
        Virtual object
        Handle inputs based on changes made in update
    */
    virtual void handleInput() = 0;
};

#endif /* GAME_STATE_HPP */