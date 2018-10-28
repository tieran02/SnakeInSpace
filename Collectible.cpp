#include "Collectible.hpp"
#include <stdlib.h>
#include "Vector2.hpp"

Collectible::Collectible(ResourceManager& resourceManager, std::string name, std::string textureName, float x, float y, float activeTimer, int score)
 : Entity(resourceManager, name, textureName, {x,y}, "Collectible"), m_activeTimer(activeTimer), m_score(score)
{
    //ctor
}

Collectible::~Collectible()
{
    //dtor
}
void Collectible::Spawn()
{
    //random position that is within the game area and clamped to the grid
    float x = (rand()%45 * 16) + 32;
    float y = (rand()%35 * 16) + 32;
    SetPostion(x,y);
    //the current timer to the active timer
    m_currentTimer = m_activeTimer;
    //set the collectible to alive
    SetAlive(true);
}

void Collectible::SetAlive(bool alive)
{
    m_alive = alive;
}

void Collectible::UpdateTimer(float amount)
{
    //subtract an amount from the timer
    m_currentTimer -= amount;
    //check if timer is less than 0 and if it set alive to false
    if(m_currentTimer <= 0)
        SetAlive(false);
}

void Collectible::Draw(sf::RenderWindow& window)
{
    if(m_alive)
        Entity::Draw(window);
}

void Collectible::OnCollision(Entity& other)
{
    OnPickUp(other);
}

