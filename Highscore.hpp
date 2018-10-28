#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP
#include <string>
#include <unordered_map>
#include <vector>

//Score struct to hold high scores
struct Score
{
    Score(std::string name, int amount) : Name(name), Amount(amount){}
    Score(){}

    //Name of the snake
    std::string Name;
    //Score they had
    int Amount;

    bool operator<(const Score& a) const
    {
        return Amount > a.Amount;
    }
};

class Highscore
{
public:
    Highscore();
    ~Highscore();
    //Add/Update score to the score map
    void AddScore(const std::string& name, int amount);
    //Save the scores of the game to file
    void SaveToFile();
    //Get the current scores
    const std::unordered_map<std::string,int>& GetScores(){return m_scores;}
    //Get highscores of ALL games with an amount to return
    std::vector<Score> TopScoresFromFile(int amount);
private:
    std::unordered_map<std::string,int> m_scores;
};

#endif // HIGHSCORE_HPP
