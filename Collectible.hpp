#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include <string>
#include "Snake.hpp"

class Collectible : public Entity
{
    public:
        Collectible(ResourceManager& resourceManager, std::string name, std::string textureName, float x, float y, float activeTimer, int score = 10);
        virtual ~Collectible();
        //Spawn the collectible
        void Spawn();
        void SetAlive(bool alive);
        const bool& IsAlive() {return m_alive;}
        const float& TimeLeft() {return m_activeTimer;}
        //update the timer by a set amount
        void UpdateTimer(float amount);
        //Draw the entity
        void Draw(sf::RenderWindow& window) override;
        //Called when an entity collides with the collectible
        void OnCollision(Entity& other) override;
        //Called when a snake has picked up the collectible
        virtual void OnPickUp(Entity& other) = 0;
    protected:
        float m_activeTimer;
        float m_currentTimer;
        int m_score = 0;
        bool m_alive {false};
};

#endif // COLLECTIBLE_HPP

