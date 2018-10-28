#ifndef GOLDENFRUIT_HPP
#define GOLDENFRUIT_HPP

#include "Collectible.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"

class GoldenFruit : public Collectible
{
    public:
        GoldenFruit(ResourceManager& resourceManager, float x, float y);
        ~GoldenFruit();
        //Override the virtual functions of the base class
        void Initialize() override;
        void OnPickUp(Entity& other) override;
};

#endif // GOLDENFRUIT_HPP
