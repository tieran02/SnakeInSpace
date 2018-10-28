#include "Entity.hpp"
#include "ResourceManager.hpp"

Entity::Entity(ResourceManager& resourceManager, std::string entityName, std::string textureName, const Vector2f& pos, std::string tag) : m_resourceManager(resourceManager), m_name(entityName), m_tag(tag), m_textureName(textureName), m_spawnPos(pos)
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::Initialize()
{
    //Add the texture to the resource manager ( only one instance of the texture is stored)
    m_resourceManager.AddTexture(m_textureName);
    //get and set the texture
    sf::Texture& texture = *m_resourceManager.GetTexture(m_textureName);
    m_sprite.setTexture(texture);
    //Make the origin to the center of the sprite
    m_sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
    //Set the position to the spawn pos
    m_position = m_spawnPos;
    //Set the sprite pos to the entities pos
    m_sprite.setPosition(m_position.x, m_position.y);

}

void Entity::Update(sf::RenderWindow& window)
{
    //on each from update the sprites pos to the entities pos
    m_sprite.setPosition(m_position.x, m_position.y);
}

void Entity::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Entity::SetColor(const sf::Color& color)
{
    m_sprite.setColor(color);
}

void Entity::SetPostion(const Vector2f& pos)
{
    m_position = pos;
    m_sprite.setPosition(m_position.x, m_position.y);
}
void Entity::SetPostion(float x, float y)
{
    m_position = {x,y};
    m_sprite.setPosition(m_position.x, m_position.y);
}

bool Entity::Intersect(const Entity& other)
{
    //get the distance between this entity and the other entity
    Vector2f vec = other.m_position - m_position;
    float length = vec.Magnitude();
    //check if the two entities are intersecting by checking if the sum of the  radius is greater than the length
    if(other.m_collisionRadius + m_collisionRadius > length)
        return true;
    return false;
}

bool Entity::Intersect(const Vector2f& other)
{
    //get the distance between this entity and a world position
    Vector2f vec = other - m_position;
    float length = vec.Magnitude();
    //check if the two entities are intersecting by checking if the sum of the  radius is greater than the length
    if(1 + m_collisionRadius > length)
        return true;
    return false;
}
Vector2f Entity::GetSize()
{
    return {m_sprite.getGlobalBounds().width,m_sprite.getGlobalBounds().height};
}






