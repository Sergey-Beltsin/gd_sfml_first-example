#ifndef SFML_TEST_GAME_H
#define SFML_TEST_GAME_H

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

    sf::RectangleShape rectangleShape;

    void initVariables();
    void initWindow();
    void initEnemies();
public:
    Game();
    virtual ~Game();

    const bool isWindowOpen() const;

    void pollEvents();
    void update();
    void render();
};

#endif //SFML_TEST_GAME_H
