#ifndef GAMEOVERSCENE_HPP
#define GAMEOVERSCENE_HPP

#include "Scene.hpp"
#include <string>
#include <unordered_map>
#include "Highscore.hpp"
#include "Snake.hpp"


class GameoverScene : public Scene
{
public:
    GameoverScene(std::string name, Highscore& scores, std::string winner);
    ~GameoverScene();

    //Override scenes virtual function
    void Initialize() override;
    void Start() override;
    void Unload() override;
    void Update(sf::RenderWindow& window) override;
    void Render(sf::RenderWindow& window) override;

private:
    //Scores to display
    Highscore& m_scores;
    //The name of the winning snake
    std::string m_winningSnake;
};

#endif // GAMEOVERSCENE_HPP
