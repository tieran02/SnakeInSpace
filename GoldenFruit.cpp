#include "GoldenFruit.hpp"

GoldenFruit::GoldenFruit(ResourceManager& resourceManager, float x, float y)  : Collectible(resourceManager, "GoldenFruit", "GoldenFruit.png", x, y, 30)
{

}

GoldenFruit::~GoldenFruit()
{

}

void GoldenFruit::Initialize()
{
    //initialise the entity
    Entity::Initialize();
}

void GoldenFruit::OnPickUp(Entity& other)
{
    //check if other is a snake
    if(other.GetTag() == "Snake")
    {
        //cast other to a snake object
        Snake* snake = static_cast<Snake*>(&other);
        //Add 3 segment to the snake and increase
        snake->AddSegement(3);
        snake->IncreaseScore(m_score);
        //set alive to false
        SetAlive(false);
    }
    else if(other.GetTag() == "Sun" || other.GetTag() == "Planet")
        //if the fruit collides with the sun or a planet then set alive to false
        SetAlive(false);
}
