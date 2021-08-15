#ifndef SFML_TEST_GAME_H
#define SFML_TEST_GAME_H

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class Game {
private:
    sf::RenderWindow * window;
    sf::VideoMode videoMode;
    sf::Event event;

    sf::Vector2i mousePosWindow;

    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;

    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;

    void initVariables();
    void initWindow();
    void initEnemies();
public:
    Game();
    virtual ~Game();

    const bool isWindowOpen() const;

    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();
    void update();
    void updateEnemies();

    void renderEnemies();
    void render();
};

#endif //SFML_TEST_GAME_H
