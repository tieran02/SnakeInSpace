#include "SnakeAI.hpp"
#include "SceneManager.hpp"

SnakeAI::SnakeAI(ResourceManager& resourceManager, std::string name, float x, float y, const sf::Color& color, Grid& grid) : Snake(resourceManager, name, x, y, color), m_grid(grid)
{

}

SnakeAI::~SnakeAI()
{
    //dtor
}

void SnakeAI::Initialize()
{
    Snake::Initialize();
    m_targetPos = Vector2f(0,0);
}

void SnakeAI::Update(sf::RenderWindow& window)
{
    //Find collectable
    Collectible* collectible = GetAliveCollectable();
    if(collectible != nullptr && m_targetPos == Vector2f(0,0))
    {
        //found a collectible and set the target pos to the collectible
        m_targetPos = collectible->GetPosition();
    }
    else if(collectible == nullptr && m_targetPos == Vector2f(0,0))
    {
        //set target position to a random point in the game
        m_targetPos = {static_cast<float>((rand()&25*16)+32) , static_cast<float>((rand()&30*16)+32)};
    }
    //Find a path to the target point
    m_pathfinding.FindPath(m_position,m_targetPos);

    //check if pathfinding has found a path
    if(m_pathfinding.HasPath())
    {
        //set node to the front of the path found by the pathfinder
        Node* node = m_pathfinding.GetPath().front();
        //set the direction to the direction of the node
        EDirection dir = GetDirectionToNode(node);
        ChangeDirection(dir);
    }
    else
    {
        //if path not found set target pos to 0 and next update the snake would get a new target pos
        m_targetPos = Vector2f(0,0);
    }
    //if snake has reached the target set the target pos
    if(m_position == m_targetPos)
        m_targetPos = Vector2f(0,0);

    //Update the snake
    Snake::Update(window);
}

void SnakeAI::Draw(sf::RenderWindow& window)
{
    Snake::Draw(window);
}


EDirection SnakeAI::GetDirectionToNode(Node* node) const
{
    //find out what direction the node is in
    if(m_position.x > node->GetWorldPos().x)
        return EDirection::eWest;
    else if(m_position.x < node->GetWorldPos().x)
        return EDirection::eEast;
    else if(m_position.y > node->GetWorldPos().y)
        return EDirection::eNorth;
    else if(m_position.y < node->GetWorldPos().y)
        return EDirection::eSouth;

    return EDirection::eEast;
}


Collectible* SnakeAI::GetAliveCollectable()
{
    //Get all entities with the tag of collectible
    std::vector<Entity*> entities = SceneManager::Instance().GetCurrentScene()->GetEntitiesByTag("Collectible");
    std::vector<Collectible*> collectibles;
    for(const auto& entity : entities)
    {
        //cast entity to collectible
        Collectible* collectible = static_cast<Collectible*>(entity);
        if(collectible->IsAlive())
            collectibles.push_back(collectible);
    }
    if(collectibles.size() > 0)
    {
        int index = rand() % collectibles.size();
        return collectibles[index];
    }
    return nullptr;
}
