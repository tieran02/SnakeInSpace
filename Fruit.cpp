#include "Fruit.hpp"
#include <iostream>

Fruit::Fruit(ResourceManager& resourceManager, float x, float y) : Collectible(resourceManager, "Fruit", "Fruit.png", x, y, 10)
{
    //ctor
}

Fruit::~Fruit()
{
    //dtor
}

void Fruit::Initialize()
{
    //initialise the entity
    Entity::Initialize();
}

void Fruit::OnPickUp(Entity& other)
{
    //check if other is a snake
    if(other.GetTag() == "Snake")
    {
        //cast other to a snake object
        Snake* snake = static_cast<Snake*>(&other);
        //Add one segment to the snake
        snake->AddSegement(1);
        //increase score
        snake->IncreaseScore(m_score);
        //set alive to false
        SetAlive(false);
    }
    else if(other.GetTag() == "Sun" || other.GetTag() == "Planet")
    {
        //if the fruit collides with the sun or a planet then set alive to false
        SetAlive(false);
    }
}
