#include "Planet.hpp"
#include "SceneManager.hpp"
#include "Snake.hpp"
#include "SnakeSegment.hpp"

Planet::Planet(ResourceManager& resourceManager, const std::string& name, const std::string& textureName, Vector2f center, float distance, float speed, float radius) : Entity(resourceManager, name, textureName,center, "Planet"), m_center(center), m_distance(distance), m_speed(speed)
{
    //set the entities collision radius equal to the radius of the planet
    m_collisionRadius = radius;
}

Planet::~Planet()
{

}


void Planet::Initialize()
{
    //Initialise base entity
    Entity::Initialize();

    //calculate the planets start position based on the distance from the sun
    m_position.x = m_center.x + cos(m_clock.getElapsedTime().asSeconds() * m_speed) * m_distance;
    m_position.y = m_center.y + sin(m_clock.getElapsedTime().asSeconds() * m_speed) * m_distance;
    m_clock.restart();
}

void Planet::Unload()
{

}

void Planet::Update(sf::RenderWindow& window)
{
    Entity::Update(window);

    //calculate the planets current position using trigonometry and multiple that by the distance from the sun
    m_position.x = m_center.x + cos(m_clock.getElapsedTime().asSeconds() * m_speed) * m_distance;
    m_position.y = m_center.y + sin(m_clock.getElapsedTime().asSeconds() * m_speed) * m_distance;

    //set the position of the planet to the calculated pos
    m_position.x = (m_position.x);
    m_position.y = (m_position.y);
}

void Planet::Draw(sf::RenderWindow& window)
{
    Entity::Draw(window);
}
