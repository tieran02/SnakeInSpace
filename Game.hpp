#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"

class Game
{
public:
    //Game constructor assigns the game name, width and height
    Game(std::string name, int width, int height);
    ~Game();
    //Game Initialize is used to add the base scenes to the game
    void Initialize();
    //Start loads a scene and runs the gameloop
    void Start();

private:
    //Name of the game and window
    std::string m_name;
    //Pointer to the SFML window
    sf::RenderWindow* window;
    //width and height of the game
    int m_width, m_height;
    //Creates the SFML window
    void createWindow();
    //Main game loop
    void gameLoop();
};

#endif // GAME_HPP
