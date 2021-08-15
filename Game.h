#ifndef SFML_TEST_GAME_H
#define SFML_TEST_GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float SPEED = 3.0f;
const int HEALTH = 20;
const int MAX_ENEMIES = 5;

class Game {
private:
    sf::RenderWindow * window;
    sf::VideoMode videoMode;
    sf::Event event;

    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    sf::Font font;

    sf::Text uiText;

    bool isGameEnded;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool isMouseHeld;

    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;

    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();
public:
    Game();
    virtual ~Game();

    const bool getIsWindowOpen() const;
    const bool getIsGameEnded() const;

    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget &renderTarget);
    void renderEnemies(sf::RenderTarget &renderTarget);
    void render();
};

#endif //SFML_TEST_GAME_H
