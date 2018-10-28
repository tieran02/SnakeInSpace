#include "Highscore.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>


Highscore::Highscore()
{
    //ctor
}

Highscore::~Highscore()
{
    //dtor
}

void Highscore::AddScore(const std::string& name, int amount)
{
    //Add or update score to the map
    m_scores[name] = amount;
}

void Highscore::SaveToFile()
{
    //create and open the output file
    std::ofstream outfile;
    outfile.open("Highscores.txt", std::ios_base::app); //append to the scores instead of overwrite

    //loop through the scores map
    for(const auto& score : m_scores)
    {
        //add the name and score line by line
        outfile << score.first << " " << score.second << std::endl;
    }
    //close the file
    outfile.close();
}

std::vector<Score> Highscore::TopScoresFromFile(int amount)
{
    //high scores to return
    std::vector<Score> scores;

    //open the file
    std::ifstream infile("Highscores.txt");
    //check if file opened successfully
    if(infile.fail())
    {
        std::cout << "Can't open highscores file\n";
        return scores;
    }

    //Add all scores to vector to sort
    for( std::string line; getline( infile, line );)
    {
        std::string name;
        int amount;
        infile >> name >> amount;
        Score score(name,amount);
        scores.push_back(score);
    }

    //sort by highest to lowest
    std::sort(scores.begin(),scores.end());
    //remove all scores after amount
    if(scores.size() > (size_t)amount)
    {
        scores.erase(scores.begin()+amount,scores.end());
    }

    return scores;
}
