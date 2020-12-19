#include "Loading.h"

const char* FLAG_DIR = "Images/flag.png";
const char* START_WAV = "Audio/countdown.wav";

/*
	Timer to see if 1s has elapsed
*/
static double timer = 0.0;
/*
	Stores 3 colour state (Red, Yellow, Green)
*/
static int colour_state = 0;

LoadState::LoadState(Game* game)
{
	resetState();

	if (!loadTexture.loadFromFile(FLAG_DIR))
		std::cout << "Failed to load " << FLAG_DIR << " image file" << std::endl;
	loadSprite.setTexture(loadTexture);
	// Resize bg to desired size
	sf::Vector2i targetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	loadSprite.setScale(targetSize.x / loadSprite.getLocalBounds().width,
		targetSize.y / loadSprite.getLocalBounds().height);
	// Load Font
	if (!loadFont.loadFromFile(FONT_DIR))
		std::cout << "Failed to load " << FONT_DIR << " ttf file" << std::endl;
	loadText.setFont(loadFont);
	// Settings for font
	loadText.setPosition(290, 140); // Edit later
	loadText.setCharacterSize(150);
	loadText.setFillColor(sf::Color::Black);
	loadText.setStyle(sf::Text::Bold);

	for (int i = 0;i < COUNT + 1;++i)
	{
		if (i < COUNT)
			loadText.setString(std::to_string(COUNT - i));
		else
		{
			loadText.setPosition(loadText.getPosition().x - 35, loadText.getPosition().y);
			loadText.setFillColor(sf::Color::White);
			loadText.setString("GO");
		}
		countdown.push_back(loadText);
	}

	// Audio
	if (!loadBuffer.loadFromFile(START_WAV))
		std::cout << "Failed to load " << START_WAV << " audio file" << std::endl;
	loadSound.setBuffer(loadBuffer);
	loadSound.play();

	this->game = game;
}

void LoadState::draw(const float dt)
{
	timer += dt;

	game->window.clear(colour[colour_state]);	
	game->window.draw(countdown[colour_state]);

	// Countdown for 1s
	if (timer >= 1.0)
	{
		switch (colour_state)
		{
		case 0:
			colour_state = 1;
			break;
		case 1:
			colour_state = 2;
			break;
		case 2:
			colour_state = 3;
			break;
		default:
			game->window.draw(loadSprite); // prevent "blinking"
			is_ready = true;
			break;
		}
		timer = 0;
	}
	else 
		if (colour_state == COUNT)
			game->window.draw(loadSprite);
}

void LoadState::update(const float dt)
{
	if (is_ready)
		playGame();
}

void LoadState::playGame()
{
	game->pushState(new PlayState(game));
}

void LoadState::resetState()
{
	colour_state = 0; // Restart to initial state
}
