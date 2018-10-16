#include "GameViewPlayer.h"
#include <iostream>

using namespace std;

GameViewPlayer::GameViewPlayer() // Player window constructor
    : gameWindow(sf::VideoMode(1440, 900, 32), "One More Sol",sf::Style::Titlebar | sf::Style::Close)
{
    if(!gameFont.loadFromFile("assets/Game_Font.ttf"))
        cout << "Could not load requested font." << endl;

    if (!gameSound.loadFromFile("assets/Gamex_Music.ogg"))
        cout << "Could not load request music." << endl;

    if (!gameImage.loadFromFile("assets/playField.png"))
        cout << "Could not load requested image." << endl;

    if (!gameSky.loadFromFile("assets/skyBox.png"))
        cout << "Failed to Load Skybox." << endl;

    if (!lockIcon.loadFromFile("assets/lockIcon.png"))
        cout << "Failed to Load Lock Icon." << endl;

    sky.setRadius(894);
    sky.setOrigin(894,894);
    sky.setPosition(720, 450);
    sky.setTexture(&gameSky);

    background.setOrigin(0,724);
    background.setPosition(0,900);                    // Applies textures to ball, paddles and background
    background.setSize(sf::Vector2f(1440,724));
    background.setTexture(&gameImage);

    weapon1.setSize(sf::Vector2f(75,75));
    weapon2.setSize(sf::Vector2f(335,335));
    weapon3.setSize(sf::Vector2f(335,335));
    weapon4.setSize(sf::Vector2f(335,335));
    weapon5.setSize(sf::Vector2f(335,335));
    weapon6.setSize(sf::Vector2f(335,335));
    weapon7.setSize(sf::Vector2f(335,335));
    weapon1.setPosition(295, 790);
    /*weapon2
    weapon3
    weapon4
    weapon5
    weapon6
    weapon7*/
    weapon1.setTexture(&lockIcon);

    gameMusic.setBuffer(gameSound);
    gameMusic.play();
    gameMusic.setLoop(true);

}

bool GameViewPlayer::playerViewIsOpen()
{
    updateGame();
    while(gameWindow.isOpen())
    {
         while(gameWindow.pollEvent(Event))
            {
                if(Event.type == sf::Event::Closed)
                {
                    gameWindow.close(); // Quit game
                    return true;
                }
            }
    }
    return false;
}

void GameViewPlayer::movePlayer(float timePassed)
{

}

void GameViewPlayer::moveEnemy(float timePassed)
{

}

void GameViewPlayer::updateGame(void) // Draws all elements of screen
{

    gameWindow.clear(sf::Color::Black);

    gameWindow.draw(sky);
    gameWindow.draw(background);
    gameWindow.draw(weapon1);

    gameWindow.display();
}

void GameViewPlayer::deleteObjects(void)
{
    delete currentPlayer;
}
