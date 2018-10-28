#ifndef SNAKEPLAYER_HPP
#define SNAKEPLAYER_HPP

#include "Snake.hpp"


class SnakePlayer : public Snake
{
    public:
        SnakePlayer(ResourceManager& resourceManager, std::string name, float x, float y, const sf::Color& color = sf::Color::Green);
        ~SnakePlayer();
        //Override the virtual functions of the base class
        void Update(sf::RenderWindow& window) override;
};

#endif // SNAKEPLAYER_HPP
