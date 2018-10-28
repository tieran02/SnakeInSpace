#ifndef FRUIT_HPP
#define FRUIT_HPP

#include "Collectible.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"

class Fruit : public Collectible
{
public:
    Fruit(ResourceManager& resourceManager, float x, float y);
    ~Fruit();
    //Override the virtual functions of the base class
    void Initialize() override;
    void OnPickUp(Entity& other) override;
};

#endif // FRUIT_HPP
