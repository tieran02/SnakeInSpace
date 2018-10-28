#include "Game.hpp"
#include "GameScene.hpp"
#include "MainMenuScene.hpp"
#include <iostream>
#include <stdlib.h>

Game::Game(std::string name, int width, int height) : m_name(name), m_width(width), m_height(height)
{
    //ctor
    std::cout << "Game constructor called" << std::endl;
    srand(time(NULL));
}

Game::~Game()
{
    std::cout << "Game destructor called and destroying window" << std::endl;
    //delete window from the heap
    delete window;
}

void Game::Initialize()
{
    //create the window
    createWindow();
    //Add the game scene
    SceneManager::Instance().AddScene(std::make_shared<MainMenuScene>("mainMenu"));
    SceneManager::Instance().AddScene(std::make_shared<GameScene>("gameScene"));
}

void Game::Start()
{
    //Load the main menu scene
    SceneManager::Instance().LoadScene("mainMenu");
    //start game loop
    gameLoop();
}

void Game::createWindow()
{
    //dynamically create render window
    window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_name);
}

void Game::gameLoop()
{
    //whilst window is open update the scene and render it
    while (window->isOpen())
    {
        SceneManager::Instance().Update(*window);
        SceneManager::Instance().Render(*window);
    }
}
