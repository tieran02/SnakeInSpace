#include "Grid.hpp"
#include "SceneManager.hpp"

Grid::Grid(int height, int width, int nodeSize, sf::RectangleShape walls[4]) : m_width(height/16), m_height(width/16), m_nodeSize(nodeSize)
{
    //add the walls to the grid
    for(int i = 0; i < 4; i++)
    {
        m_walls[i] = walls[i];
    }
}

Grid::~Grid()
{
    //dtor
}

void Grid::Initialize()
{
    //loop through the grid
    for(int x = 0; x< m_width; x++)
    {
        for(int y = 0; y < m_height; y++)
        {
            //set the world pos equal to x multiplied by node size
            Vector2f worldPos = {(float)x*m_nodeSize,(float)y*m_nodeSize};
            //set grid pos
            Vector2i gridPos = {x,y};
            //Add node to the 2d array
            m_nodes[x][y] = Node(x+y,worldPos,gridPos,ENodeType::Passable);
        }
    }
}

Node* Grid::GetNodeFromWorldPosition(const Vector2f& pos)
{
    // to get the grid pos just divide the position by the node size
    int x = pos.x/m_nodeSize;
    int y = pos.y/m_nodeSize;
    return &m_nodes[x][y];
}

std::vector<Node*> Grid::GetNeighbours(Node& node)
{
    //vector of neighbours
    std::vector<Node*> neighbours;

    //loop through all surrounding nodes
    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            //Skip current node and the angled nodes
            if((x == 0 && y == 0) || (x == -1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == -1) || (x == 1 && y == 1))
                continue;

            //check if in bounds
            int checkX = node.GetGridPos().x + x;
            int checkY = node.GetGridPos().y + y;

            if(checkX >= 0 && checkX < m_width && checkY >= 0 && checkY < m_height )
            {
                //node is in bounds and add it to the neighbours vector
                neighbours.push_back(&m_nodes[checkX][checkY]);
            }
        }
    }
    return neighbours;
}


void Grid::UpdateNodes()
{
    //Get all active entities
    std::vector<Entity*> entities = SceneManager::Instance().GetCurrentScene()->GetAllEntities();
    resetGrid(entities);

    //Add walls to the grid
    for(const auto& wall : m_walls)
    {
        for(int x = wall.getPosition().x/m_nodeSize; x < (wall.getPosition().x + wall.getSize().x/m_nodeSize); x++)
        {
            for(int y = wall.getPosition().y/m_nodeSize; y < (wall.getPosition().y + wall.getSize().y/m_nodeSize); y++)
            {
                int GridX = (int)x;
                int GridY = (int)y;

                if(GridX < m_width && GridY < m_height && GridX >= 0 && GridY >= 0)
                    m_nodes[GridX][GridY].SetNodetype(ENodeType::Obstacle);
            }
        }
    }

    for(const auto entity : entities)
    {
        //get the grid pos of the entity
        Node* currentNode = GetNodeFromWorldPosition(entity->GetPosition());
        //check if the entity is a collectible and is so make the node passable
        if(entity->GetTag() == "Collectible")
            currentNode->SetNodetype(ENodeType::Passable);
        //check if the entity is a planet and is so make all nodes around the planet obstacles
        else if(entity->GetTag() == "Planet")
        {
            int padding = 8;
            for(int x = (entity->GetPosition().x - entity->GetSize().x/2 - padding)/m_nodeSize; x < (entity->GetPosition().x + entity->GetSize().x/2 + padding)/m_nodeSize; x++)
            {
                for(int y = (entity->GetPosition().y - entity->GetSize().y/2 - padding)/m_nodeSize; y < (entity->GetPosition().y + entity->GetSize().y/2 + padding)/m_nodeSize; y++)
                {
                    int GridX = (int)x;
                    int GridY = (int)y;

                    if(GridX < m_width && GridY < m_height && GridX > 0 && GridY > 0)
                        m_nodes[GridX][GridY].SetNodetype(ENodeType::Obstacle);
                }
            }
        }
        else //else make all other entities obstacles
        {
            currentNode->SetNodetype(ENodeType::Obstacle);
        }
    }
}

void Grid::resetGrid(std::vector<Entity*> entities)
{
    //loop through the grid
    for(int x = 0; x< m_width; x++)
    {
        for(int y = 0; y < m_height; y++)
        {
            //Reset nodes back to the default state
            m_nodes[x][y].SetNodetype(ENodeType::Passable);
            m_nodes[x][y].GCost = 0;
            m_nodes[x][y].HCost = 0;
            m_nodes[x][y].SetParent(nullptr);
        }
    }
}


void Grid::DebugDraw(sf::RenderWindow& window)
{
    //set the base grid colour
    sf::Color color = sf::Color(0,255,0,100);
    //loop through the grid
    for(int x = 0; x < m_width; x++)
    {
        for(int y = 0; y < m_height; y++)
        {
            //get the current node
            Node& node = m_nodes[x][y];

            switch(node.GetNodeType())
            {
            case(ENodeType::Obstacle):
                //make the obstacle red as the node is an obstacle
                color = sf::Color(255,0,0,100);
                break;
            case(ENodeType::Passable):
                //make the node green as the node is passable
                color = sf::Color(0,255,0,100);
                break;
            }
            //setup the node rectangle and draw it
            sf::RectangleShape nodeShape;
            nodeShape.setPosition(x*m_nodeSize,y*m_nodeSize);
            nodeShape.setOrigin(m_nodeSize/2,m_nodeSize/2);
            nodeShape.setSize({(float)m_nodeSize-2,(float)m_nodeSize-2});
            nodeShape.setFillColor(color);
            window.draw(nodeShape);
        }
    }
}
