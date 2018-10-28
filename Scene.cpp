#include "Scene.hpp"

Scene::Scene(std::string name) : m_name(name)
{
    //ctor
}

Scene::~Scene()
{

}

void Scene::Update(sf::RenderWindow& window)
{
    //check for collisions every frame
    checkCollisions();
}

void Scene::AddEntity(Entity& entity)
{
    //Add entity to entities vector
    m_entities.push_back(&entity);
}
void Scene::RemoveEntity(Entity& entity)
{
    //Remove and entity from vector
    m_entities.remove(&entity);
}

Entity* Scene::GetEntityByTag(const std::string& tag)
{
    //loop through all entities
    for(const auto& entity : m_entities)
    {
        //check if entity tag equals the tag given and if true return that entity
        if(entity->GetTag() == tag)
            return entity;
    }
    return nullptr;
}

std::vector<Entity*> Scene::GetEntitiesByTag(const std::string& tag)
{
    //vector of entities to hold all the entities that are found
    std::vector<Entity*> entities;
    //loop through all entities
    for(const auto& entity : m_entities)
    {
        //if entity has the same tag add it to the entities vector
        if(entity->GetTag() == tag)
            entities.push_back(entity);
    }
    return entities;
}

Entity* Scene::GetEntityByName(const std::string& name)
{
    //loop through all entities
    for(const auto& entity : m_entities)
    {
        //check if entity name equals the name given and if true return that entity
        if(entity->GetName() == name)
            return entity;
    }
    return nullptr;
}

Entity* Scene::GetEntityByPos(const Vector2f& pos)
{
    //loop through all entities
    for(const auto& entity : m_entities)
    {
        //check if entity intersects with the position given
        if(entity->Intersect(pos))
            return entity;
    }
    return nullptr;
}

std::vector<Entity*> Scene::GetAllEntities()
{
    std::vector<Entity*> entities;
    //populate the entities vector with the entity list
    if(m_entities.size() > 0)
        entities.insert(entities.begin(), m_entities.begin(),m_entities.end());
    return entities;
}



void Scene::checkCollisions()
{
    //if there is less than two entities then return
    if(m_entities.size() < 2)
        return;

    //check all entities for collisions
    for(size_t i =0;i < m_entities.size(); i++)
    {
        //get the current entity
        auto it = m_entities.begin();
        std::advance(it, i);
        Entity* currentEntity = *it;

        if(currentEntity == nullptr)
            return;

        for(size_t j =0;j < m_entities.size(); j++)
        {
            //check current entities against all other entities
            std::list<Entity*>::iterator it = m_entities.begin();
            std::advance(it, j);
            Entity* otherEntity = *it;

            if(otherEntity == nullptr)
                return;

            //if entity equals current entity skip
            if(otherEntity == currentEntity)
                continue;

            if(currentEntity->Intersect(*otherEntity))
            {
                //collision detected
                currentEntity->OnCollision(*otherEntity);
            }
        }
    }
}
