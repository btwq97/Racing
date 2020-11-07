#include "PlayState.h"

const char* PLAY_BG_DIR = "Images\\background.png";
const char* CAR_DIR = "Images\\car.png";
const char* ACC_DIR = "Audio\\acceleration.wav";
const char* TURN_DIR = "Audio\\turn.wav";

/*
	Car structure objects
*/
const int N = 5;
Car car[5];

PlayState::PlayState(Game* game)
{
	resetState();
	// For BG
	if (!playBg.loadFromFile(PLAY_BG_DIR))
		std::cout << "Failed to load " << PLAY_BG_DIR << " image file" << std::endl;
	playBg.setSmooth(true);
	sPlayBg.setTexture(playBg);
	sPlayBg.setScale(2, 2);
	// For Car
	if (!playCar.loadFromFile(CAR_DIR))
		std::cout << "Failed to load " << CAR_DIR << " image file" << std::endl;
	playCar.setSmooth(true);
	sPlayCar.setTexture(playCar);
	sPlayCar.setOrigin(22, 22);

	// Setting 'AI' players
	for (int i = 0;i < N;i++)
	{
		car[i].x = 300 + i * 50;
		car[i].y = 1700 + i * 80;
		car[i].speed = 7 + i;
	}

	// Load Audio
	if (!accBuffer.loadFromFile(ACC_DIR))
		std::cout << "Failed to load " << ACC_DIR << " audio file" << std::endl;
	accSound.setBuffer(accBuffer);
	accSound.setLoop(true);
	if (!turnBuffer.loadFromFile(TURN_DIR))
		std::cout << "Failed to load " << TURN_DIR << " audio file" << std::endl;
	turnSound.setBuffer(turnBuffer);

	this->game = game;
}

void PlayState::update(const float dt)
{
	sf::Event evnt;
	Up = 0, Right = 0, Down = 0, Left = 0; // Reset direction flags
	while (game->window.pollEvent(evnt))
	{
		if ((evnt.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
			game->window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			restartGame();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		Up = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		Right = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		Down = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		Left = 1;
}

void PlayState::handleInput()
{
	// Car movement
	if (Up && speed < maxSpeed)
	{
		if (speed < 0)
		{
			speed += dec;
		}
		else
		{
			playAcc();
			speed += acc;
		}
	}

	if (Down && speed > -maxSpeed)
	{
		if (speed > 0)
			speed -= dec;
		else
			speed -= acc;
	}

	if (!Up && !Down)
	{
		if (speed - dec > 0)
		{
			speed -= dec;
		}
		else if (speed + dec < 0)
		{
			playAcc();
			speed += dec;
		}
		else
		{
			Stop();
			speed = 0;
		}
	}

	if (Right && speed != 0)
	{
		playTurn();
		angle += turnSpeed * speed / maxSpeed;
	}
		
	if (Left && speed != 0)
	{
		playTurn();
		angle -= turnSpeed * speed / maxSpeed;
	}
		

	car[0].speed = speed;
	car[0].angle = angle;

	for (int i = 0;i < N;i++) car[i].move();
	for (int i = 1;i < N;i++) car[i].findTarget();

	//collision
	for (int i = 0;i < N;i++)
		for (int j = 0;j < N;j++)
		{
			int dx = 0, dy = 0;
			while (dx * dx + dy * dy < 4 * R * R)
			{
				car[i].x += dx / 10.0;
				car[i].x += dy / 10.0;
				car[j].x -= dx / 10.0;
				car[j].y -= dy / 10.0;
				dx = car[i].x - car[j].x;
				dy = car[i].y - car[j].y;
				if (!dx && !dy) 
					break;
			}
		}
}

void PlayState::draw(const float dt)
{
	if (car[0].x > 320) offsetX = car[0].x - 320;
	if (car[0].y > 240) offsetY = car[0].y - 240;
	sPlayBg.setPosition(-offsetX, -offsetY);
	game->window.draw(sPlayBg);

	for (int i = 0;i < N;i++)
	{
		sPlayCar.setPosition(car[i].x - offsetX, car[i].y - offsetY);
		sPlayCar.setRotation(car[i].angle * 180 / 3.141593);
		sPlayCar.setColor(colour[i]);
		game->window.draw(sPlayCar);
	}
}

void PlayState::playAcc()
{
	accSound.play();
}

void PlayState::playTurn()
{
	turnSound.play();
}

void PlayState::Stop()
{
	turnSound.stop();
	accSound.stop();
}

void PlayState::restartGame()
{
	Stop();
	game->pushState(new LoadState(game));
}

void PlayState::resetState()
{
	// Reset variables
	speed = 0, angle = 0, maxSpeed = 12.0, acc = 0.2, dec = 0.3, turnSpeed = 0.08;
	offsetX = 0, offsetY = 0;
	Up = 0, Right = 0, Down = 0, Left = 0;
	// Reset car position + characteristics
	for (int i = 0; i < N; ++i)
	{
		car[i].reset();
	}
}