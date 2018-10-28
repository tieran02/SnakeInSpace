#include "Pathfinding.hpp"
#include "Node.hpp"
#include <iostream>

Pathfinding::Pathfinding(Grid& grid) : m_grid(grid)
{
    //ctor
}

Pathfinding::~Pathfinding()
{
    //dtor
}

void Pathfinding::FindPath(const Vector2f& startPos, const Vector2f& targetPos)
{
    //get the start and target node from the grid using the world pos
    Node* startNode = m_grid.GetNodeFromWorldPosition(startPos);
    Node* targetNode = m_grid.GetNodeFromWorldPosition(targetPos);

    //Clear all previous data
    m_path.clear();
    m_openSet.clear();
    m_closedSet.clear();
    //Add the start node to the open set
    m_openSet.push_back(startNode);

    //loop through open set until open set is empty
    while(m_openSet.size() > 0)
    {
        //set the current node to the first node in the open set
        Node* currentNode = m_openSet[0];
        //loop through all the open sets except the current node
        for(size_t i = 1; i < m_openSet.size(); i++)
        {
            //check if the F cost is less than current node Fcost or check if F cost is less than current node Fcost AND hcost is also lower
            if(m_openSet[i]->FCost() < currentNode->FCost() || (m_openSet[i]->FCost() == currentNode->FCost() && m_openSet[i]->HCost < currentNode->HCost))
            {
                //node is closer so make it the current node
                currentNode = m_openSet[i];
            }
        }
        //remove the current node from the openset
        m_openSet.erase(std::remove(m_openSet.begin(), m_openSet.end(), currentNode), m_openSet.end());
        //add the current node to the closed set
        m_closedSet.push_back(currentNode);

        //Check if current node is equal to the target node
        if(currentNode == targetNode)
        {
            //retrace the path if the node has reached the target
            RetracePath(startNode,targetNode);
            return;
        }

        //get all neighbours of a node
        for(const auto& neighbour : m_grid.GetNeighbours(*currentNode))
        {
            //check if node is an obstacle or is in closed set and if it is continue to the next neighbour
            auto setIt = std::find(m_closedSet.begin(), m_closedSet.end(),neighbour);
            if(neighbour->GetNodeType() == ENodeType::Obstacle || setIt != m_closedSet.end())
                continue;

            //Calculate the movement cost to the new neighbour
            int newMovementCostToNeighbour = currentNode->GCost + GetDistance(currentNode, neighbour);
            //check if the neighbour is already in the open set
            bool foundInOpenSet = (std::find(m_openSet.begin(), m_openSet.end(), neighbour) != m_openSet.end());
            //if the new neighbours movement cost is less than the current one AND the neighbour is not in the open set
            if(newMovementCostToNeighbour < neighbour->GCost || !foundInOpenSet)
            {
                //set the the neighbours G and H cost and set the parent to the current node
                neighbour->GCost = newMovementCostToNeighbour;
                neighbour->HCost = GetDistance(neighbour, targetNode);
                neighbour->SetParent(currentNode);

                //Add the neighbour to the open set if it doesn't exist already
                if(!foundInOpenSet)
                {
                    m_openSet.push_back(neighbour);
                }
            }
        }
    }
}
void Pathfinding::RetracePath(Node* startNode,Node* endNode)
{
    //list of nodes as the path
    std::list<Node*> path;
    //set the current node to the end node
    Node* currentNode = endNode;
    //while the current node does not equal the start node add the current node to the front
    while(currentNode != startNode)
    {
        path.push_front(currentNode);
        currentNode = currentNode->GetParent();
    }
    //set the path
    m_path = path;
}

int Pathfinding::GetDistance(Node* nodeA,Node* nodeB) const
{
    //get the absolute value of the distance between node A and node B
    int dstX = std::abs(nodeA->GetGridPos().x - nodeB->GetGridPos().x);
    int dstY = std::abs(nodeA->GetGridPos().y - nodeB->GetGridPos().y);

    return 2 * (dstY+dstX);;
}

bool Pathfinding::HasPath() const
{
    //return true is the paths size is greater than 0
    if(m_path.size() > 0)
        return true;
    return false;
}


void Pathfinding::DebugDraw(sf::RenderWindow& window)
{
    //if the path size is less than 1 return out of the debug draw
    if(m_path.size() < 1)
        return;

    //loop through all the nodes in the path and draw them
    for(const auto& node : m_path)
    {
        int nodeSize = 16;

        sf::RectangleShape nodeShape;
        nodeShape.setPosition(node->GetWorldPos().x, node->GetWorldPos().y);
        nodeShape.setOrigin(nodeSize/2,nodeSize/2);
        nodeShape.setSize({(float)nodeSize-2,(float)nodeSize-2});
        nodeShape.setFillColor(sf::Color::Cyan);
        window.draw(nodeShape);
    }
}



