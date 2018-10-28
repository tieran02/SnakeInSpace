#include "SnakePlayer.hpp"

#include <SFML/Graphics.hpp>

SnakePlayer::SnakePlayer(ResourceManager& resourceManager, std::string name, float x, float y, const sf::Color& color) : Snake(resourceManager, name, x, y,color)
{
    //ctor
}

SnakePlayer::~SnakePlayer()
{
    //dtor
}

void SnakePlayer::Update(sf::RenderWindow& window)
{
    //Get the user input and change direction depending on what arrow key was pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ChangeDirection(EDirection::eWest);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ChangeDirection(EDirection::eEast);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        ChangeDirection(EDirection::eNorth);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        ChangeDirection(EDirection::eSouth);
    }


    //Update the base snake
    Snake::Update(window);
}
