#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include "Scene.hpp"


class MainMenuScene : public Scene
{
public:
    MainMenuScene(std::string name);
    ~MainMenuScene();

    //Override scenes virtual function
    void Initialize() override;
    void Start() override;
    void Unload() override;
    void Update(sf::RenderWindow& window) override;
    void Render(sf::RenderWindow& window) override;
};

#endif // MAINMENUSCENE_HPP
