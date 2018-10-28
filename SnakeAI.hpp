#ifndef SNAKEAI_HPP
#define SNAKEAI_HPP

#include "Snake.hpp"
#include "Collectible.hpp"
#include "Grid.hpp"
#include "Pathfinding.hpp"


class SnakeAI : public Snake
{
public:
    SnakeAI(ResourceManager& resourceManager, std::string name, float x, float y, const sf::Color& color, Grid& grid);
    ~SnakeAI();

    //Override the virtual functions of the base class
    void Initialize() override;
    void Update(sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;
private:
    //Reference to the grid and pathfinding objects
    Grid& m_grid;
    Pathfinding m_pathfinding {m_grid};

    //Get the first alive collectible and return the pointer ELSE return nullptr
    Collectible* GetAliveCollectable();
    //Get the direction towards the node
    EDirection GetDirectionToNode(Node* node) const;
    //target position to head towards
    Vector2f m_targetPos;
};

#endif // SNAKEAI_HPP
