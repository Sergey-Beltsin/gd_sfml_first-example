#include "Game.h"

void Game::initVariables() {
    window = nullptr;
}

void Game::initWindow() {
    videoMode.width = WINDOW_WIDTH;
    videoMode.height = WINDOW_HEIGHT;

    window = new sf::RenderWindow(
    videoMode,
    "My first game",
    sf::Style::Titlebar | sf::Style::Close
    );

    window -> setFramerateLimit(60);
}

void Game::initEnemies() {
//    rectangleShape.setPosition();
    rectangleShape.setSize(sf::Vector2f(100.0f, 100.0f));
    rectangleShape.setFillColor(sf::Color::Cyan);
    rectangleShape.setOutlineColor(sf::Color::Green);
    rectangleShape.setOutlineThickness(1.0f);
}

Game::Game() {
    initVariables();
    initWindow();
    initEnemies();
}

Game::~Game() {
    delete window;
}

const bool Game::isWindowOpen() const {
    return window -> isOpen();
}

void Game::pollEvents() {
    while (window -> pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window -> close();
                
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window -> close();
                }

                break;
        }
    }
}

void Game::update() {
    pollEvents();
}

void Game::render() {
    window -> clear();

    window -> draw(rectangleShape);

    window -> display();
}
