#include "Jupiter.hpp"
#include "Snake.hpp"

Jupiter::Jupiter(ResourceManager& resourceManager, Vector2f center, float distance) : Planet(resourceManager,"Jupiter", "Jupiter.png", center, distance, 0.1f, 32)
{
    //ctor
}

Jupiter::~Jupiter()
{
    //dtor
}

void Jupiter::OnCollision(Entity& other)
{
    //Check if the collided entity was a segment
    if(other.GetTag() == "Segment")
    {
        //cast the entity to snake segment and get the owner
        SnakeSegment* segment = static_cast<SnakeSegment*>(&other);
        Snake* snake = segment->GetOwner();
        //Remove all points from the snake from the collided segment
        snake->RemoveSegmentsFromPoint(*segment);
    }
    //Check if the collided entity was a snake head
    else if(other.GetTag() == "Snake")
    {
        //cast the entity to a snake and remove all segments
        Snake* snake = static_cast<Snake*>(&other);
        snake->RemoveSegement(snake->SegementCount());
    }
}
