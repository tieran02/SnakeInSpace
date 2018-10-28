#ifndef PLANET_HPP
#define PLANET_HPP

#include "Entity.hpp"


class Planet : public Entity
{
public:
    Planet(ResourceManager& resourceManager, const std::string& name, const std::string& textureName, Vector2f center, float distance, float speed, float radius);
    virtual ~Planet();

    //Override the virtual functions of the base class
    void Initialize() override;
    void Unload() override;
    void Update(sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;
    //Make the planet implement the entities OnCollision
    virtual void OnCollision(Entity& other) = 0;

private:
    //The center of the planet
    Vector2f m_center;
    //distance from the sun / center of the screen
    float m_distance;
    //Speed of the planets orbit
    float m_speed;
    //planet clock to move the planet
    sf::Clock m_clock;
};

#endif // PLANET_HPP
