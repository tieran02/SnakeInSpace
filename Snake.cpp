#include "Snake.hpp"
#include <iostream>
#include "SceneManager.hpp"
#include "Fruit.hpp"
#include <iostream>

Snake::Snake(ResourceManager& resourceManager, std::string name, float x, float y, const sf::Color& color)
 : Entity(resourceManager, name, "SnakeHead.png", {x,y}, "Snake"), m_snakeColor(color) , m_lastPos(m_position)
{

}

Snake::~Snake()
{
    //dtor
}

void Snake::ChangeDirection(EDirection dir)
{
    m_direction = dir;
}

void Snake::AddSegement(int amount)
{
    //for each segment to add
    for(int i = 0; i < amount ; i++)
    {
        //Create new segment and set the position the the snakes last position
        SnakeSegment segment(m_resourceManager,m_lastPos.x,m_lastPos.y, this);
        //Initialise segment
        segment.Initialize();
        //set the segments colour to the snakes colour
        segment.SetColor(m_snakeColor);
        //add the segment to the back of the list
        m_segments.push_back(SnakeSegment(segment));
        //add the segment to the current scenes entity list (used to check collisions with all entities)
        SceneManager::Instance().GetCurrentScene()->AddEntity(m_segments.back());
    }
    std::cout << "Added " << amount << " Segments\n";
}

void Snake::RemoveSegement(int amount)
{
    //if segments is less than one there are no segments to remove
    if(m_segments.size() < 1)
        return;

    //for each segment to remove
    for(int i = 0; i < amount ; i++)
    {
        //remove the segment from the current scenes entity list
        SceneManager::Instance().GetCurrentScene()->RemoveEntity(m_segments.back());
        //pop back the segment to remove it
        m_segments.pop_back();
    }
    std::cout << "Removed " << amount << " Segments\n";
}

void Snake::RemoveSegmentsFromPoint(SnakeSegment& segment)
{
    if(segment.HasOwnership(*this))
    {
        //Get segment pos

        //use an iterator to loop through list from beginning
        auto it = m_segments.begin();
        for(size_t i = 0; i < m_segments.size(); i++)
        {
            //check if the memory address of the iterator equals the segments address
            if(&(*it) == &segment)
            {
                //found segment and remove all segments behind it
                RemoveSegement(m_segments.size()-i);
                break;
            }
            //go to next segment in list
            it++;
        }
    }
}

void Snake::updateSegments()
{
    if(m_segments.size() == 0)
        return;

    //Create new segment and set the position the the snakes last position
    SnakeSegment segment(m_resourceManager, m_lastPos.x,m_lastPos.y, this);
    //Initialise segment and set colour
    segment.Initialize();
    segment.SetColor(m_snakeColor);

    //remove the old segment to the scenes entity list
    SceneManager::Instance().GetCurrentScene()->RemoveEntity(m_segments.back());
    //remove the last segment
    m_segments.pop_back();
    //add the new segment to the front of the segments list
    m_segments.push_front(segment);
    //add the new segment to the scenes entity list
    SceneManager::Instance().GetCurrentScene()->AddEntity(m_segments.front());
}

void Snake::Initialize()
{
    //Initialise the base entity
    Entity::Initialize();
    //clear all segments
    m_segments.clear();
    //Set the start direction to east
    m_direction = EDirection::eEast;
    //set score to 0
    m_score = 0;
    //set snake colour
    SetColor(m_snakeColor);

    m_lastPos = {0,0}; //set lastPos to 0,0 at the start of a new game
    m_alive = true; //set alive to true in case snake died last game
}

void Snake::Unload()
{
    m_segments.clear();
}

void Snake::OnCollision(Entity& other)
{
    //check if the other entity that collided was a segment
    if(other.GetTag() == "Segment")
    {
        //kill this snake as it collided with a segment
        Kill();
    }
    //check if the other entity that collided was a snake
    else if(other.GetTag() == "Snake")
    {
        //kill this snake and the other snake it collided with
        Kill();
        Snake* otherSnake = static_cast<Snake*>(&other);
        otherSnake->Kill();
    }
}

void Snake::Kill()
{
    //check if snake is alive
    if(m_alive)
    {
        //set alive to false
        m_alive = false;
        std::cout << "Snake " << GetName() << " died!\n";

        //remove entities from entity list
        for(auto& segment : m_segments)
            SceneManager::Instance().GetCurrentScene()->RemoveEntity(segment);
        //remove the snake from the entities list
        SceneManager::Instance().GetCurrentScene()->RemoveEntity(*this);
    }
    else
        std::cout << "Snake " << GetName() << " is already dead!\n";
}

void Snake::Update(sf::RenderWindow& window)
{
    //set the last pos to current pos
    m_lastPos = m_position;

    //Move in the correct direction
    switch(m_direction)
    {
    case(EDirection::eNorth):
        m_position.y -= MOVE_AMOUNT;
        m_sprite.setRotation(0);
        break;
    case(EDirection::eEast):
        m_position.x += MOVE_AMOUNT;
        m_sprite.setRotation(90);
        break;
    case(EDirection::eSouth):
        m_position.y += MOVE_AMOUNT;
        m_sprite.setRotation(180);
        break;
    case(EDirection::eWest):
        m_position.x -= MOVE_AMOUNT;
        m_sprite.setRotation(270);
        break;
    }

    //update the base entity
    Entity::Update(window);
    updateSegments();
}

void Snake::Draw(sf::RenderWindow& window)
{
    //draw the base entity
    Entity::Draw(window);
    //draw all the snakes segments
    for(auto segment : m_segments)
    {
        segment.Draw(window);
    }
}

