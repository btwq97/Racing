#pragma once

#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "GameState.h"
#include "Loading.h"
#include "Globals.h"
#include "Car.h"

class PlayState : public GameState
{
private:
	sf::Texture playBg, playCar;
	sf::Sprite sPlayBg, sPlayCar;
	sf::SoundBuffer accBuffer, turnBuffer;
	sf::Sound accSound, turnSound;
	sf::Font pauseFont;
	sf::Text pauseText;
	
	/*
		Radius
	*/
	const float R = 22;
	/*
		Car characteristics
	*/
	float speed = 0, angle = 0, maxSpeed = 12.0, acc = 0.2, dec = 0.3, turnSpeed = 0.08;
	int offsetX = 0, offsetY = 0;
	/*
		Direction flags
	*/
	bool Up = 0, Right = 0, Down = 0, Left = 0;

	std::vector<sf::Color> colour = { sf::Color::Red, sf::Color::Green, sf::Color::Magenta, sf::Color::Blue, sf::Color::White };

	void resetState();
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	PlayState(Game* game);
	/*
		Play Acceleration Audio
	*/
	void playAcc();
	/*
		Play Drift Audio
	*/
	void playTurn();
	/*
		Stop all movement Audio
	*/
	void Stop();
	/*
		Pause all/Resume movement Audio
	*/
	void Pause();
	/*
		Restart game at countdown screen
	*/
	void restartGame();
};

#endif