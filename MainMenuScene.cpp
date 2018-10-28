#include "MainMenuScene.hpp"
#include "SceneManager.hpp"
#include <sstream>

MainMenuScene::MainMenuScene(std::string name) : Scene(name)
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::Initialize()
{
    //set bg colour
    SetBackgorundColor(sf::Color(50,50,50));
    //Add the main font
    m_resourceManager.AddFont("manaspc.ttf");
}

void MainMenuScene::Start()
{

}

void MainMenuScene::Unload()
{

}

void MainMenuScene::Update(sf::RenderWindow& window)
{
    //poll for events
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
        break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
                case sf::Keyboard::Escape:
                    //close the game
                    window.close();
                break;
                case sf::Keyboard::Return:
                    //if enter pressed load the game scene
                    SceneManager::Instance().LoadScene("gameScene");
                break;
                default:
            break;
            }
            break;
        default:
            break;
        }
    }
}

void MainMenuScene::Render(sf::RenderWindow& window)
{
    //Use string stream as to_string is unavailable
    std::stringstream ss (std::stringstream::in | std::stringstream::out);

    sf::Text Text;
    Text.setFont(*m_resourceManager.GetFont("manaspc.ttf"));
    ss.str("");
    ss << "Giant Snakes in Space!\n\n";
    ss << " Press Enter to start\n";
    ss << " Press Escape to quit\n";
    //Set the string, colour, font size.
    Text.setString(ss.str());
    Text.setFillColor(sf::Color::White);
    Text.setCharacterSize(24);
    //center text
    sf::FloatRect textRect = Text.getLocalBounds();
    Text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    Text.setPosition(800/2,640/2);
    //draw text to the screen
    window.draw(Text);
}
