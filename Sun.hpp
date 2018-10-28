#ifndef SUN_HPP
#define SUN_HPP

#include "Entity.hpp"
#include "Planet.hpp"

class Sun : public Planet
{
public:
    Sun(ResourceManager& resourceManager, float x, float y);
    ~Sun();

    //Override the virtual functions of the base class
    void Initialize() override;
    void Unload() override;
    void Update(sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;
    void OnCollision(Entity& other) override;
};

#endif // SUN_HPP
