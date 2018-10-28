#ifndef EARTH_HPP
#define EARTH_HPP

#include "Planet.hpp"


class Earth : public Planet
{
    public:
        Earth(ResourceManager& resourceManager, Vector2f center, float distance);
        ~Earth();
        void OnCollision(Entity& other) override;
};

#endif // EARTH_HPP
