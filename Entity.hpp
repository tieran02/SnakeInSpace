#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "ResourceManager.hpp"
#include "Vector2.hpp"
#include <SFML/Graphics.hpp>

class Entity
{
public:
    /*
        ResourceManager is passed through as ref to add textures
        entityName is the name of the entity
        textureName is the name of the texture to be loaded
        pos is the initial starting position of the entity DEFAULT(0,0)
        tag is used to categorise entities by a set tag (DEFAULT NULL)
    */
    Entity(ResourceManager& resourceManager, std::string entityName, std::string textureName, const Vector2f& pos = {0,0}, std::string tag = "");
    virtual ~Entity();

    const std::string& GetName()
    {
        return m_name;
    }
    const std::string& GetTag()
    {
        return m_tag;
    }
    const Vector2f& GetPosition()
    {
        return m_position;
    }
    void SetPostion(const Vector2f& pos);
    void SetPostion(float x, float y);

    virtual void Initialize() = 0;
    virtual void Start() {}
    virtual void Unload() {}
    virtual void Update(sf::RenderWindow& window);
    virtual void Draw(sf::RenderWindow& window);

    void SetColor(const sf::Color& color);
    //checks if entity collides with another entity using the entity list from the scene and returns the collided entity
    bool Intersect(const Entity& other);
    bool Intersect(const Vector2f& other);
    //Called when a collision occurs
    virtual void OnCollision(Entity& other) {}
    //Get the size of the entity (uses sprite size)
    Vector2f GetSize();


protected:
    //All entities have the reference to the resource manager in case they need to access any resources
    ResourceManager& m_resourceManager;
    //entity name
    std::string m_name;
    //entity tag (Can be used to tag an entity with the type to cast to the derived type)
    std::string m_tag;
    //Entity texture name has to equal the image name without the extension (E.G Snake)
    std::string m_textureName;
    //position of the entity (using custom math vector class)
    Vector2f m_position;
    //a constant vector to hold the initial spawn point (Used when reloading a scene);
    const Vector2f m_spawnPos;
    //Collision radius is used to check for collisions (8 by default as the base size is 16)
    float m_collisionRadius = 8;
    //SFML sprite for the entity
    sf::Sprite m_sprite;
};

#endif // ENTITY_HPP
