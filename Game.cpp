#include "Game.h"

void Game::initVariables() {
    window = nullptr;

    points = 0;
    enemySpawnTimerMax = 1000.0f;
    enemySpawnTimer = enemySpawnTimerMax ;
    maxEnemies = 5;
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
    enemy.setPosition(10.0f, 10.0f);
    enemy.setSize(sf::Vector2f(100.0f, 100.0f));
    enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    enemy.setFillColor(sf::Color::Cyan);
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(1.0f);
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

void Game::spawnEnemy() {
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window -> getSize().x - enemy.getSize().x)),
        0.0f
    );

    enemy.setFillColor(sf::Color::Green);

    enemies.push_back(enemy);
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

void Game::updateMousePositions() {
    mousePosWindow = sf::Mouse::getPosition(*window);
}

void Game::update() {
    pollEvents();

    updateMousePositions();

    updateEnemies();
}

void Game::updateEnemies() {
    if (enemies.size() < maxEnemies) {
        if (enemySpawnTimer >= enemySpawnTimerMax) {
            spawnEnemy();
            enemySpawnTimer = 0.0f;
        } else {
            enemySpawnTimer += 1.0f;
        }
    }

    for (auto &e : enemies) {
         e.move(0.0f, 5.0f);
    }
}

void Game::render() {
    window -> clear();

    renderEnemies();

    window -> display();
}

void Game::renderEnemies() {
    for (auto &e : enemies) {
        window -> draw(e);
    }
}
