#include "Game.h"

const char* LOOP_AUDIO = "Audio/loop.wav";

// Stopped here
Game::Game()
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::None);

    window.setFramerateLimit(MAX_FPS);

    if (!loopBuffer.loadFromFile(LOOP_AUDIO))
        std::cout << "Failed to load " << LOOP_AUDIO << " audio file" << std::endl;
    loopSound.setBuffer(loopBuffer);
    loopSound.setLoop(true);
    loopSound.setPlayingOffset(sf::seconds(13.f));
    loopSound.play();
}

Game::~Game()
{
    while (!states.empty())
        popState();
}

void Game::pushState(GameState* state)
{
    states.push_back(state);
}

void Game::popState()
{
    states.back();
    delete states.back();
    states.pop_back();
}

GameState* Game::CurrentState()
{
    if (states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        //control frame rate
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        //exception handling
        if (CurrentState() == nullptr)
            continue;

        if (!Pause)
            //get user input for current game state
            CurrentState()->handleInput();

        //update anything neccessary
        CurrentState()->update(dt);

        //clear window
        window.clear();

        //draw anything in the current game state
        CurrentState()->draw(dt);

        window.display();
    }
}
