#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP
#include "Grid.hpp"
#include <list>
#include <unordered_set>


class Pathfinding
{
public:
    Pathfinding(Grid& grid);
    ~Pathfinding();
    //Finds the shortest path from the start position to the end position
    void FindPath(const Vector2f& startPos, const Vector2f& endPos);
    //Returns a constant reference to the path
    const std::list<Node*>& GetPath() {return m_path;}
    //Check if path exist
    bool HasPath() const;
    //Debug draw allows you to visualise the path for debugging
    void DebugDraw(sf::RenderWindow& window);

private:
    Grid& m_grid;
    //a vector of open nodes
    std::vector<Node*> m_openSet;
    //a vector of closed nodes
    std::vector<Node*> m_closedSet;
    //take the path and reverse it back so the order is correct to follow
    void RetracePath(Node* startNode,Node* endNode);
    //Get the distance between two nodes
    int GetDistance(Node* nodeA,Node* nodeB) const;
    //path of nodes in a list (empty if no path found)
    std::list<Node*> m_path;
};

#endif // PATHFINDING_HPP
