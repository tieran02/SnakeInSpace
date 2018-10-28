#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Entity.hpp"
#include "SnakeSegment.hpp"
#include <list>

enum class EDirection
{
    eNorth,
    eEast,
    eSouth,
    eWest
};

class Snake : public Entity
{
public:
    Snake(ResourceManager& resourceManager, std::string name, float x, float y, const sf::Color& color = sf::Color::Green);
    virtual ~Snake();

    //Override the virtual functions of the base class
    void Initialize() override;
    void Unload() override;
    void Update(sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;
    void OnCollision(Entity& other) override;

    //Check if snake is alive
    const bool IsAlive(){return m_alive;}
    //Kill the snake (set alive to false)
    void Kill();

    //Change the direction of the snake
    void ChangeDirection(EDirection dir);
    //Add a set amount of segments to the snake
    void AddSegement(int amount);
    //Remove a set amount of segments to the snake
    void RemoveSegement(int amount);
    //Remove all segments from beyond a given segment
    void RemoveSegmentsFromPoint(SnakeSegment& segement);
    //Return the segment count
    int SegementCount() {return m_segments.size();}

    //Increase score of the snake
    void IncreaseScore(int amount) { m_score += amount;}
    //Get the score of the snake
    const float& GetScore() {return m_score;}

protected:
    //amount to move the snake per turn
    const int MOVE_AMOUNT{16};
    //Snakes colour
    sf::Color m_snakeColor;
    //current direction of the snake
    EDirection m_direction;
    //current score of the snake
    float m_score {0};
    //is the snake alive
    bool m_alive {true};

private:
    //list of segments of the snake
    std::list<SnakeSegment> m_segments;
    //last pos of the snake
    Vector2f m_lastPos;
    //update all the snake segments
    void updateSegments();
};

#endif // SNAKE_HPP
