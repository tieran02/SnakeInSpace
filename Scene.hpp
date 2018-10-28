#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Entity.hpp"
#include "ResourceManager.hpp"

class Scene
{
public:
    Scene(std::string name);
    virtual ~Scene();

    //pure virtual functions for the scene
    virtual void Initialize() = 0;
    virtual void Start() = 0;
    virtual void Unload() = 0;
    virtual void Update(sf::RenderWindow& window) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    //Get the name of the scene
    const std::string& GetName() {return m_name;}
    //Set the background colour of a scene
    void SetBackgorundColor(sf::Color color) {m_backgroundColor = color;}
    //Get the background colour of the scene
    const sf::Color& GetBackgorundColor() {return m_backgroundColor;}

    void AddEntity(Entity& entity); //Add an entity by ref (Add the address the entities list
    void RemoveEntity(Entity& entity); //Remove an entity by ref (Remove the address the entities list
    Entity* GetEntityByTag(const std::string& tag); //Get an entity by a tag, returns first instance or nullptr if none found
    std::vector<Entity*> GetEntitiesByTag(const std::string& tag); //Get all entities with a tag, returns all instances or an empty vector if none found
    Entity* GetEntityByPos(const Vector2f&); //Get an entity by the position, returns first instance or nullptr if none found
    Entity* GetEntityByName(const std::string& name); //Get an entity by the name, returns first instance or nullptr if none found
    std::vector<Entity*> GetAllEntities(); //Get and return all entities in the scene

protected:
    //Name of the scene
    std::string m_name;
    //Window background colour of a scene
    sf::Color m_backgroundColor{sf::Color::Black};

    //Scenes resource manager
    ResourceManager m_resourceManager;
    //pointers to every entity in the game scene (We don't need to delete the elements as we never allocate NEW memory)
    std::list<Entity*> m_entities;

private:
    //Check collisions with all other entities
    void checkCollisions();
};

#endif // SCENE_HPP
