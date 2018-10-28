#include "Sun.hpp"
#include "Snake.hpp"
#include "Collectible.hpp"

Sun::Sun(ResourceManager& resourceManager, float x, float y) : Planet(resourceManager,"Sun", "Sun.png", {x,y}, 0, 0, 64)
{

}

Sun::~Sun()
{

}

void Sun::Initialize()
{
    Entity::Initialize();
}

void Sun::Unload()
{

}

void Sun::Update(sf::RenderWindow& window)
{
    Entity::Update(window);
}

void Sun::Draw(sf::RenderWindow& window)
{
    Entity::Draw(window);
}

void Sun::OnCollision(Entity& other)
{
    //Check if the collided entity was a snake head
    if(other.GetTag() == "Snake")
    {
        //cast the entity to a snake and kill the snake
        Snake* snake = static_cast<Snake*>(&other);
        snake->Kill();
    }

    if(other.GetTag() == "Collectible")
    {
        //cast the entity to a collectible and set alive to false
        Collectible* collectible = static_cast<Collectible*>(&other);
        collectible->SetAlive(false);
    }
}

