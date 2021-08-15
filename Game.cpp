#include "Game.h"

void Game::initVariables() {
    window = nullptr;

    isGameEnded = false;
    points = 0;
    health = HEALTH;
    enemySpawnTimerMax = 10.0f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = MAX_ENEMIES;
    isMouseHeld = false;
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

void Game::initFonts() {
    if (!font.loadFromFile("../Fonts/Roboto-Regular.ttf")) {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load fonts!" << std::endl;
    }
}

void Game::initText() {
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setString("Points: 0");
}

void Game::initEnemies() {
    enemy.setPosition(10.0f, 10.0f);
    enemy.setSize(sf::Vector2f(100.0f, 100.0f));
    enemy.setFillColor(sf::Color::Cyan);
//    enemy.setOutlineColor(sf::Color::Green);
//    enemy.setOutlineThickness(1.0f);
}

Game::Game() {
    initVariables();
    initWindow();
    initFonts();
    initText();
    initEnemies();
}

Game::~Game() {
    delete window;
}

const bool Game::getIsWindowOpen() const {
    return window -> isOpen();
}

const bool Game::getIsGameEnded() const {
    return isGameEnded;
}

void Game::spawnEnemy() {
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window -> getSize().x - enemy.getSize().x)),
        0.0f
    );

    int type = rand() % 5;

    switch (type) {
        case 0:
            enemy.setSize(sf::Vector2f(10.0f, 10.0f));
            enemy.setFillColor(sf::Color::Magenta);

            break;
        case 1:
            enemy.setSize(sf::Vector2f(30.0f, 30.0f));
            enemy.setFillColor(sf::Color::Blue);

            break;
        case 2:
            enemy.setSize(sf::Vector2f(50.0f, 50.0f));
            enemy.setFillColor(sf::Color::Cyan);

            break;
        case 3:
            enemy.setSize(sf::Vector2f(70.0f, 70.0f));
            enemy.setFillColor(sf::Color::Yellow);

            break;
        case 4:
            enemy.setSize(sf::Vector2f(100.0f, 100.0f));
            enemy.setFillColor(sf::Color::Green);

            break;
        default:
            enemy.setSize(sf::Vector2f(100.0f, 100.0f));
            enemy.setFillColor(sf::Color::Green);

            break;
    }

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
    mousePosView = window -> mapPixelToCoords(mousePosWindow);
}

void Game::update() {
    pollEvents();

    if (!isGameEnded) {
        updateMousePositions();

        updateText();

        updateEnemies();
    }

    if (health <= 0) {
        isGameEnded = true;
    }
}

void Game::updateText() {
    std::stringstream ss;

    ss << "Points: " << points << std::endl
        << "Health: " << health << std::endl;

    uiText.setString(ss.str());
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

    for (int i = 0; i < enemies.size(); i += 1) {
          enemies[i].move(0.0f, SPEED);

         if (enemies[i].getPosition().y > window -> getSize().y) {
             enemies.erase(enemies.begin() + i);
             health -= 1;
         }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!isMouseHeld) {
            isMouseHeld = true;
            bool deleted = false;

            for (int i = 0; i < enemies.size() && !deleted; i += 1) {
                if (enemies[i].getGlobalBounds().contains(mousePosView)) {
                    if (enemies[i].getFillColor() == sf::Color::Magenta) {
                        points += 10;
                    } else if (enemies[i].getFillColor() == sf::Color::Blue) {
                        points += 7;
                    } else if (enemies[i].getFillColor() == sf::Color::Cyan) {
                        points += 5;
                    } else if (enemies[i].getFillColor() == sf::Color::Yellow) {
                        points += 3;
                    } else if (enemies[i].getFillColor() == sf::Color::Green) {
                        points += 1;
                    }

                    deleted = true;
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    } else {
        isMouseHeld = false;
    }
}

void Game::renderText(sf::RenderTarget &renderTarget) {
    renderTarget.draw(uiText);
}

void Game::renderEnemies(sf::RenderTarget &renderTarget) {
    for (auto &e : enemies) {
        renderTarget.draw(e);
    }
}

void Game::render() {
    window -> clear();

    renderEnemies(*window);

    renderText(*window);

    window -> display();
}
