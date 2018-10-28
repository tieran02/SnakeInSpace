#include "GameoverScene.hpp"
#include "SceneManager.hpp"
#include <sstream>

GameoverScene::GameoverScene(std::string name, Highscore& scores, std::string winner) : Scene(name), m_scores(scores), m_winningSnake(winner)
{

}

GameoverScene::~GameoverScene()
{

}

void GameoverScene::Initialize()
{
    //set bg colour
    SetBackgorundColor(sf::Color(50,50,50));
    //Add the main font
    m_resourceManager.AddFont("manaspc.ttf");
}

void GameoverScene::Start()
{

}

void GameoverScene::Unload()
{
    //On unload remove the game over scene as it was dynamically added during the game scene
    SceneManager::Instance().RemoveScene(m_name);
}

void GameoverScene::Update(sf::RenderWindow& window)
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
                case sf::Keyboard::Return:
                    //if enter pressed load the main menu scene back up
                    SceneManager::Instance().LoadScene("mainMenu");
                return;
                default:
                break;
            }
        default:
            break;
        }
    }
}

void GameoverScene::Render(sf::RenderWindow& window)
{
    //Use string stream as to_string is unavailable
    std::stringstream ss (std::stringstream::in | std::stringstream::out);

    //SFML text to hold the score
    sf::Text ScoreText;
    //Set the scores font using the resource manager
    ScoreText.setFont(*m_resourceManager.GetFont("manaspc.ttf"));
    ss.str("");
    ss << "       Game Over!\n";
    ss << "        " << m_winningSnake << " Won!\n\n";
    ss << "        Scores:\n";
    //Loop through all the scores and add them to the string stream
    for(auto score : m_scores.GetScores())
    {
        ss << "     " << score.first << " = " << score.second << std::endl;
    }
    ss << "\nPress any enter to continue\n";
    //Set the string, colour, font size.
    ScoreText.setString(ss.str());
    ScoreText.setFillColor(sf::Color::White);
    ScoreText.setCharacterSize(24);
    //center text to the middle of the screen
    sf::FloatRect textRect = ScoreText.getLocalBounds();
    ScoreText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    ScoreText.setPosition(800/2,640/2);

    //SFML text to hold the high scores from previous games
    sf::Text Highscore;
    //Set the scores font using the resource manager
    Highscore.setFont(*m_resourceManager.GetFont("manaspc.ttf"));
    ss.str("");
    ss << "High Scores:\n";
    //Loop through the top 3 high scores and add them to the string stream
    for(const auto& score : m_scores.TopScoresFromFile(3))
    {
        ss << score.Name << " = " << score.Amount << std::endl;
    }
    //Set the string, colour, font size.
    Highscore.setString(ss.str());
    Highscore.setFillColor(sf::Color::White);
    Highscore.setCharacterSize(24);
    //center text
    textRect = Highscore.getLocalBounds();
    Highscore.setPosition(550,0);

    //Draw the score and highscore
    window.draw(ScoreText);
    window.draw(Highscore);
}

