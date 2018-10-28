#ifndef GRID_HPP
#define GRID_HPP

#include "Node.hpp"
#include <list>
#include <vector>
#include "Entity.hpp"

class Grid
{
public:
    Grid(int height, int width,int nodeSize, sf::RectangleShape walls[4]);
    ~Grid();

    //Initialise the grid (assign the 2d array of nodes with default values)
    void Initialize();
    //Update all the nodes by getting the entities position and checking if its an obstacle
    void UpdateNodes();
    //Get a node from the grid using world position (E.G entity position)
    Node* GetNodeFromWorldPosition(const Vector2f& pos);
    //Get all the surrounding nodes
    std::vector<Node*> GetNeighbours(Node& node);
    //Draw the grid over the game (used for debugging only to visualise the grid)
    void DebugDraw(sf::RenderWindow& window);

private:
    //width and height of the grid (NOT WORLD SPACE)
    int m_width, m_height;
    //size of the node (size of the snake head)
    int m_nodeSize;
    //2d vector of nodes
    Node m_nodes[800/16][640/16];
    //Have a copy of the game walls in the grid
    sf::RectangleShape m_walls[4];
    //Resets the grid back to default values
    void resetGrid(std::vector<Entity*> entities);
};

#endif // GRID_HPP
