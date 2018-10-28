/*
  Snake ICA start project using SFML
    SFML documentation: http://www.sfml-dev.org/documentation/2.4.2/classes.php
  Windows build
    To build on Windows you need to have the correct version of CodeBlocks
      Download from here: http://www.codeblocks.org/downloads/26
      Must be the download titled "codeblocks-16.01mingw-setup.exe"
*/

#include <iostream>

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
    std::cout << "Starting" << std::endl;

    //Create game object
    Game game("C++ Snake ICA : T7042361", 800,640);
    //Initialise and start the game
    game.Initialize();
    game.Start();


    std::cout << "Finished" << std::endl;
    return 0;


}
