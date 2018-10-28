#ifndef JUPITER_HPP
#define JUPITER_HPP
#include "Planet.hpp"


class Jupiter : public Planet
{
public:
    Jupiter(ResourceManager& resourceManager, Vector2f center, float distance);
    ~Jupiter();

    //Override the virtual functions of the base class
    void OnCollision(Entity& other) override;
};

#endif // JUPITER_HPP
