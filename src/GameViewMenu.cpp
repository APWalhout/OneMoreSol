//This is where the player views what happens onscreen.

#include "GameViewMenu.h"
#include "GameViewPlayer.h"
#include "Gun.h"
//#include <windows.h> //THIS ONLY WORKS FOR WINDOWS 
#include <time.h> //this works for linux

using namespace std;

GameViewMenu::GameViewMenu() // Menu window constructor
    : menuWindow(sf::VideoMode(1440, 900, 32), "One More Sol",sf::Style::Titlebar | sf::Style::Close)
{
    if (!menuImage.loadFromFile("assets/menuScreen.png"))
        cout << "Could not load requested image." << endl;
    if (!playBtnImg.loadFromFile("assets/playButton.png"))
        cout << "Could not load requested image." << endl;
    if (!playBtnHImg.loadFromFile("assets/playButtonH.png"))
        cout << "Could not load requested image." << endl;
    if (!storyBtnImg.loadFromFile("assets/storyButton.png"))
        cout << "Could not load requested image." << endl;
    if (!storyBtnHImg.loadFromFile("assets/storyButtonH.png"))
        cout << "Could not load requested image." << endl;
    if (!exitBtnImg.loadFromFile("assets/exitButton.png"))
        cout << "Could not load requested image." << endl;
    if (!exitBtnHImg.loadFromFile("assets/exitButtonH.png"))
        cout << "Could not load requested image." << endl;

    if (!Menu_Music.loadFromFile("assets/Menu_Music.ogg"))
        cout << "Could not load request music." << endl;
    if (!Menu_Transition.loadFromFile("assets/Menu_Transition.ogg"))
        cout << "Could not load request music." << endl;
    if (!Menu_Selection.loadFromFile("assets/Menu_Selection.ogg"))
        cout << "Could not load request music." << endl;

    //selector.setPosition(0,0);
    //cout << "0,0" << endl;

    menuMusic.setBuffer(Menu_Music);

    menuMusic.play();

    menuMusic.setLoop(true);

    menuTransition.setBuffer(Menu_Transition);

    menuSelection.setBuffer(Menu_Selection);


    background.setSize(sf::Vector2f(1,1));

    background.setPosition(0,0);
    background.setSize(sf::Vector2f(1440,900));
    background.setTexture(&menuImage);

    playBtnRec.setOrigin((1308/2),0);
    playBtnRec.setPosition(1440,400);
    playBtnRec.setSize(sf::Vector2f((1308/2),(224/2)));
    playBtnRec.setTexture(&playBtnHImg);

    storyBtnRec.setOrigin((1050/2),0);
    storyBtnRec.setPosition(1440,530);
    storyBtnRec.setSize(sf::Vector2f((1050/2),(117/2)));
    storyBtnRec.setTexture(&storyBtnImg);

    exitBtnRec.setOrigin((444),0);
    exitBtnRec.setPosition(1440,605);
    exitBtnRec.setSize(sf::Vector2f(444,(117/2)));
    exitBtnRec.setTexture(&exitBtnImg);

}

bool GameViewMenu::gameViewMenuIsOpen()
{
    updateMenu();
    selector.setPosition(0,0);
    cout << "0,0" << endl;
    while(menuWindow.isOpen()) // Menu loop
	{
		while(menuWindow.pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed)
			{
				menuWindow.close(); // Quit game
				return true;
			}

			if(Event.type == sf::Event::KeyPressed)
			{
				if(Event.key.code == sf::Keyboard::Up)
				{
					if(sf::Vector2f (0,0) == selector.getPosition())
					{
						selector.setPosition(0,2);
						selectButton(0,2);
						menuTransition.play();
						cout << "0,2" << endl;
					}
					else if(sf::Vector2f (0,1) == selector.getPosition())
					{
						selector.setPosition(0,0);
						selectButton(0,0);
						menuTransition.play();
						cout << "0,0" << endl;
					}
					else if(sf::Vector2f (0,2) == selector.getPosition())
					{
						selector.setPosition(0,1);
						selectButton(0,1);
						menuTransition.play();
						cout << "0,1" << endl;
					}
				}

				if(Event.key.code == sf::Keyboard::Down)
				{
					if(sf::Vector2f (0,0) == selector.getPosition())
					{
						selector.setPosition(0,1);
						selectButton(0,1);
						menuTransition.play();
						cout << "0,1" << endl;
					}
					else if(sf::Vector2f (0,1) == selector.getPosition())
					{
						selector.setPosition(0,2);
						selectButton(0,2);
						menuTransition.play();
						cout << "0,2" << endl;
					}
					else if(sf::Vector2f (0,2) == selector.getPosition())
					{
						selector.setPosition(0,0);
						selectButton(0,0);
						menuTransition.play();
						cout << "0,0" << endl;
					}
				}

				if(Event.key.code == sf::Keyboard::Space || Event.key.code == sf::Keyboard::Return)
				{
					if(sf::Vector2f (0,0) == selector.getPosition())
					{
						menuSelection.play();
						//Sleep(900);
                        //nanosleep(900);
						menuWindow.close();
						return false;
					}
					if(sf::Vector2f (0,1) == selector.getPosition())
					{
						menuSelection.play();
						//Sleep(900);
                        //nanosleep(900);
						menuWindow.close();
						return false;
					}
					if(sf::Vector2f (0,2) == selector.getPosition())
					{
						menuSelection.play();
						//Sleep(900);
                        //nanosleep(900);
						menuWindow.close();
						return true;
					}
				}
			}
		}
	}
}

void GameViewMenu::updateMenu(void) // Updates screen
{

    menuWindow.clear(sf::Color::Black);

    menuWindow.draw(background);
    menuWindow.draw(playBtnRec);
    menuWindow.draw(storyBtnRec);
    menuWindow.draw(exitBtnRec);

    // display
    menuWindow.display();
}

/*
* Accepts the coordinates of the selection
* and changes the shape textures to respond.
*/
void GameViewMenu::selectButton(int x, int y)
{
    if(y == 0)
    {
        playBtnRec.setTexture(&playBtnHImg);
        storyBtnRec.setTexture(&storyBtnImg);
        exitBtnRec.setTexture(&exitBtnImg);
    }
    else if(y == 1)
    {
        playBtnRec.setTexture(&playBtnImg);
        storyBtnRec.setTexture(&storyBtnHImg);
        exitBtnRec.setTexture(&exitBtnImg);
    }
    else if(y == 2)
    {
        playBtnRec.setTexture(&playBtnImg);
        storyBtnRec.setTexture(&storyBtnImg);
        exitBtnRec.setTexture(&exitBtnHImg);
    }
    updateMenu();//could this be more optimally placed?
}
