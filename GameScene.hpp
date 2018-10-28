#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <string>
#include <memory>

#include "Scene.hpp"
#include "Snake.hpp"
#include "Collectible.hpp"
#include "Sun.hpp"
#include "Planet.hpp"
#include "Grid.hpp"
#include "Pathfinding.hpp"
#include "Highscore.hpp"

class GameScene : public Scene
{
public:
    GameScene(std::string name);
    ~GameScene();
    //Override scenes virtual function
    void Initialize() override;
    void Start() override;
    void Unload() override;
    void Update(sf::RenderWindow& window) override;
    void Render(sf::RenderWindow& window) override;

private:
    //SFML clock to use as the game timer
    sf::Clock m_clock;
    //Set the game time to 90 seconds
    float m_gameTimer {90.0f};
    //array of 4 snakes using smart pointers to manage the memory
    std::unique_ptr<Snake> m_Snakes[4];

    //SFML rectangles for the walls
    sf::RectangleShape m_walls[4];
    //array of 5 collectibles using smart pointers to manage the memory
    std::unique_ptr<Collectible> m_collectibles[5];
    //Sun object that is centered in the middle of the screen
    Sun m_sun {m_resourceManager, 800/2,640/2};
    //array of 2 planets using smart pointers to manage the memory
    std::unique_ptr<Planet> m_planets[2];
    //A* pathfinding grid (Used to get the current state of the map and find paths for the AI)
    Grid m_grid {800, 640, 16, m_walls};
    //Pathfinding object used to find paths for the AI
    Pathfinding m_pathfinding{m_grid};
    //Highscore object used to save scores and hold current scores of the game
    Highscore m_highscore;

    //Initialise collectibles (Create and allocate memory)
    void initCollectibles();
    //Spawn the collectibles
    void spawnCollectibles();
    //Check the current state of the game and detect if any snake has won
    void winCheck();
    //Draw the user interface
    void drawUI(sf::RenderWindow& window);
};

#endif // GAMESCENE_HPP
