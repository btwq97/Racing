#include "MenuState.h"

const char* MENU_BG_DIR = "Images\\menu.jpeg";

MenuState::MenuState(Game* game)
{
	// Load menu bg
	menuTexture.loadFromFile(MENU_BG_DIR);
	menuSprite.setTexture(menuTexture);
	// Load font
	font.loadFromFile(FONT_DIR);
	menuFont.setFont(font);
	titleFont.setFont(font);
	// Settings for font
	menuFont.setPosition(300,100); // Edit later
	menuFont.setCharacterSize(60);
	menuFont.setFillColor(sf::Color::White);
	menuFont.setStyle(sf::Text::Bold);
    menuFont.setString("Race Car 1.0");

	// Setting for game title
	titleFont.setPosition(80,100); // Edit later
	titleFont.setCharacterSize(30);
	titleFont.setFillColor(sf::Color::White);

	for (int i = 0;i < NUM_BUTTONS;++i)
	{
		buttons.push_back(titleFont);
		buttons[i].setPosition(titleFont.getPosition().x, titleFont.getPosition().y + i * 100); // Edit later
	}
	buttons[0].setString("Play Game");
	buttons[1].setString("Quit Game");
    // Resize bg to desired size
	sf::Vector2i targetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	menuSprite.setScale(targetSize.x / menuSprite.getLocalBounds().width,
		targetSize.y / menuSprite.getLocalBounds().height);
    // Audio

	this->game = game;
}

void MenuState::handleInput()
{
    sf::Event event;

    while (game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;
            /* Change Between game states */
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) // ESC button
                game->window.close();
            else if (event.key.code == sf::Keyboard::Return) // Enter button
                loadState();
            break;
            //check if text is hovered over
        case sf::Event::MouseMoved:
            if (isTextClicked(buttons[0]))
                buttons[0].setFillColor(sf::Color::Green);
            else
                buttons[0].setFillColor(sf::Color::White);
            if (isTextClicked(buttons[1]))
                buttons[1].setFillColor(sf::Color::Red);
            else
                buttons[1].setFillColor(sf::Color::White);
            break;
        }
        //check if text is clicked.
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (isTextClicked(buttons[0]))
                loadState();
            else if (isTextClicked(buttons[1]))
                game->window.close();
        }
    }
}

void MenuState::draw(const float dt)
{
    game->window.draw(menuSprite);

    game->window.draw(menuFont);

    //draw text
    for (auto x : buttons)
        game->window.draw(x);
}

void MenuState::loadState()
{
    start_sound.play();
    game->pushState(new LoadState(game));
}

bool MenuState::isTextClicked(sf::Text text)
{
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height); // Set a rectangle around text

    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;

    //Otherwise, don't do anything
    return false;
}