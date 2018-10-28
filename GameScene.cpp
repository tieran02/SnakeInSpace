#include "GameScene.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "SnakePlayer.hpp"
#include "SnakeAI.hpp"
#include "Earth.hpp"
#include "Jupiter.hpp"
#include "Fruit.hpp"
#include "GoldenFruit.hpp"
#include <iostream>
#include <sstream>
#include "GameoverScene.hpp"

GameScene::GameScene(std::string name) : Scene(name)
{

}

GameScene::~GameScene()
{

}

void GameScene::Initialize()
{
    //set bg colour
    SetBackgorundColor(sf::Color(50,50,50));

    //add font to resource manager
    m_resourceManager.AddFont("manaspc.ttf");
    //restart game clock and set timer
    m_clock.restart();
    m_gameTimer = 90.0f;

    //wall thickness
    float wallSize = 24;
    //set the wall color
    sf::Color wallColour = sf::Color(20,20,20);
    //createWalls
    m_walls[0] = sf::RectangleShape({800,wallSize}); // top
    m_walls[0].setFillColor(wallColour);
    m_walls[1] = sf::RectangleShape({wallSize,640}); // right
    m_walls[1].setPosition(800-wallSize,0);
    m_walls[1].setFillColor(wallColour);
    m_walls[2] = sf::RectangleShape({800,wallSize}); // bot
    m_walls[2].setPosition(0,640-wallSize);
    m_walls[2].setFillColor(wallColour);
    m_walls[3] = sf::RectangleShape({wallSize,640}); // left
    m_walls[3].setFillColor(wallColour);

    //Initialise planets and sun
    m_sun.Initialize();
    m_planets[0] = std::unique_ptr<Earth>(new Earth(m_resourceManager, {800/2,640/2}, 150));
    m_planets[0]->Initialize();
    m_planets[1] = std::unique_ptr<Jupiter>(new Jupiter(m_resourceManager, {800/2,640/2}, 300));
    m_planets[1]->Initialize();
    //Add planets and sun to the entity list of the scene
    AddEntity(m_sun);
    AddEntity(*m_planets[0]);
    AddEntity(*m_planets[1]);

    //Initialise create snakes
    m_Snakes[0] = std::unique_ptr<SnakePlayer>(new SnakePlayer(m_resourceManager, "Player1", 64,64));
    m_Snakes[1] = std::unique_ptr<SnakeAI>(new SnakeAI(m_resourceManager, "AI1", 608,64, sf::Color::Red, m_grid));
    m_Snakes[2] = std::unique_ptr<SnakeAI>(new SnakeAI(m_resourceManager, "AI2", 64,512, sf::Color::Blue, m_grid));
    m_Snakes[3] = std::unique_ptr<SnakeAI>(new SnakeAI(m_resourceManager, "AI3", 608,512, sf::Color::Magenta, m_grid));
    //Initialise snakes and add them as entities
    for(auto& snake : m_Snakes)
    {
        snake->Initialize();
        AddEntity(*snake);
    }
    //initialise collectibles
    initCollectibles();

    //Create grid for the A* pathfinding and initialise it
    m_grid = Grid(800,640,16,m_walls);
    m_grid.Initialize();
    m_grid.UpdateNodes();
}


void GameScene::Start()
{
    //At the start add 3 segments to all snakes
    for(auto& snake : m_Snakes)
    {
        snake->AddSegement(3);
    }
}

void GameScene::Unload()
{
    //unload all snakes
    for(auto& snake : m_Snakes)
    {
        snake->Unload();
    }
    //unload all collectibles
    for(auto& collectible : m_collectibles)
    {
            collectible->Unload();
    }
    //unload all planets
    for(auto& planet : m_planets)
    {
            planet->Unload();
    }
    //Clear entities
    m_entities.clear();
}

void GameScene::Update(sf::RenderWindow& window)
{
    Scene::Update(window);

    //Spawn collectibles
    spawnCollectibles();
    //Update nodes for A* grid
    m_grid.UpdateNodes();

    //input loop
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
                case sf::Keyboard::F5:
                    //if F5 pressed reload the game scene
                    SceneManager::Instance().ReloadScene();
                break;
                case sf::Keyboard::Escape:
                    //if escape pressed change scene to main menu
                    SceneManager::Instance().LoadScene("mainMenu");
                break;
                default:
                break;
            }
            break;
        default:
            break;
        }
    }

    //Update planets
    for(const auto& planet : m_planets)
    {
        planet->Update(window);
    }

    //loop through all the snakes
    for(auto& snake : m_Snakes)
    {
        //snake is dead so continue to next snake
        if(!snake->IsAlive())
            continue;
        //loop through all the walls and check if the bounds of the wall contains the snake pos
        for(const auto& wall : m_walls)
        {
            if(wall.getGlobalBounds().contains(snake->GetPosition().x,snake->GetPosition().y))
            {
                //snake collided with wall so kill the snake
                snake->Kill();
            }
        }
        //update the snake
        snake->Update(window);
        //add or update score
        m_highscore.AddScore(snake->GetName(), snake->GetScore());
    }

    //update collectible timers
    for(const auto& collectible : m_collectibles)
    {
        collectible->UpdateTimer(m_clock.getElapsedTime().asSeconds());
    }

    //win check
    winCheck();

    // Loop until time passed
    while (m_clock.getElapsedTime().asMilliseconds()<100);
    m_gameTimer -= m_clock.getElapsedTime().asSeconds(); //Takeaway time elapsed from game time
    m_clock.restart();

}

void GameScene::Render(sf::RenderWindow& window)
{
    //draw all the snakes
    for(const auto& snake : m_Snakes)
    {
        if(!snake->IsAlive())
            continue;
        snake->Draw(window);
    }

    //draw collectibles
    for(const auto& collectible : m_collectibles)
    {
        collectible->Draw(window);
    }

    //draw sun and planets
    m_sun.Draw(window);
    for(const auto& planet : m_planets)
    {
        planet->Draw(window);
    }

    //draw walls
    for(const auto& wall : m_walls)
    {
        window.draw(wall);
    }

    //_grid.DebugDraw(window);
    drawUI(window);

}

void GameScene::initCollectibles()
{
    //Add one golden fruit
    m_collectibles[0] = std::unique_ptr<Collectible>(new GoldenFruit(m_resourceManager, 0,0));
    m_collectibles[0]->Initialize();
    AddEntity(*m_collectibles[0]);
    //add 4 normal fruits
    for(int i = 1; i < 5; i++)
    {
        m_collectibles[i] = std::unique_ptr<Collectible>(new Fruit(m_resourceManager, 0,0));
        m_collectibles[i]->Initialize();
        AddEntity(*m_collectibles[i]);
    }
}

void GameScene::spawnCollectibles()
{
    //loop through all collectibles
    for(const auto& collectible : m_collectibles)
    {
        //check if the collectible is not alive and spawn collectible at random times
        if(!collectible->IsAlive())
        {
            if(rand()%30==0)
            {
                collectible->Spawn();
            }
        }
    }
}

void GameScene::winCheck()
{
    //number of alive snakes
    int alive = 0;
    //check if snake is alive and append it to the alive counter if it is.
    for(const auto& snake : m_Snakes)
    {
        if(snake->IsAlive())
            alive++;
    }

    //check if one snake or less is alive or if time has ended
    if(alive <= 1 || m_gameTimer <= 0)
    {
        //only one snake alive, that snake wins
        m_highscore.SaveToFile();

        std::string Winner = "winner;";
        float Score = 0;
        //find the winning snake
        for(const auto& snake : m_Snakes)
        {
            if(alive == 1 && snake->IsAlive())
            {
                Winner = snake->GetName();
                break;
            }
            else if(alive == 0)
            {
                //winningName = "ALL snakes died";
                if(snake->GetScore() > Score)
                {
                    Winner = snake->GetName();
                    Score = snake->GetScore();
                }
            }
        }
        //Add a new gameover scene to the scene manger and pass through the highscores and winning snake
        SceneManager::Instance().AddScene(std::make_shared<GameoverScene>("GameOver", m_highscore,Winner));
        //load the game over scene
        SceneManager::Instance().LoadScene("GameOver");

    }
}

void GameScene::drawUI(sf::RenderWindow& window)
{
    //Setup timer and draw it
    sf::Text timerText;
    timerText.setFont(*m_resourceManager.GetFont("manaspc.ttf"));
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << "Time left = " << (int)m_gameTimer;
    timerText.setString(ss.str());
    timerText.setFillColor(sf::Color::White);
    timerText.setCharacterSize(24);
    window.draw(timerText);

    //Setup scores and draw it
    sf::Text ScoreText;
    ScoreText.setFont(*m_resourceManager.GetFont("manaspc.ttf"));
    ss.str("");
    ss << "Scores:\n";
    for(auto score : m_highscore.GetScores())
    {
        ss << score.first << " = " << score.second << std::endl;
    }
    ScoreText.setString(ss.str());
    ScoreText.setFillColor(sf::Color::White);
    ScoreText.setCharacterSize(12);
    ScoreText.setPosition(680,0);
    window.draw(ScoreText);
}

