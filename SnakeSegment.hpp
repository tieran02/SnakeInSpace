#ifndef SNAKESEGMENT_HPP
#define SNAKESEGMENT_HPP

#include "Entity.hpp"
#include "Vector2.hpp"


class Snake;
class SnakeSegment : public Entity
{
public:
    SnakeSegment(ResourceManager& resourceManager, float x, float y, Snake* owner);
    ~SnakeSegment();

    //Override the virtual functions of the base class
    virtual void Initialize() override;
    virtual void Draw(sf::RenderWindow& window) override;
    //Check if the segment belongs to the given snake
    bool HasOwnership(const Snake& snake);
    //Get the owner of the segment
    Snake* GetOwner();

private:
    //owner of the snakes segment
    Snake* m_owner;
};

#endif // SNAKESEGMENT_HPP
