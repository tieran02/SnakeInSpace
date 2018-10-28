#include "SnakeSegment.hpp"
#include <iostream>
#include "Snake.hpp"

SnakeSegment::SnakeSegment(ResourceManager& resourceManager, float x, float y, Snake* owner) : Entity(resourceManager, "SnakeSegment", "SnakeBody.png", Vector2f(x,y), "Segment"), m_owner(owner)
{
    //ctor
}

SnakeSegment::~SnakeSegment()
{
    //dtor
}

void SnakeSegment::Initialize()
{
    Entity::Initialize();
}

void SnakeSegment::Draw(sf::RenderWindow& window)
{
    Entity::Draw(window);
}

bool SnakeSegment::HasOwnership(const Snake& snake)
{
   if(m_owner == &snake)
        return true;
   return false;
}

Snake* SnakeSegment::GetOwner()
{
    return m_owner;
}

