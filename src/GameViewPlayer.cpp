#include "GameViewPlayer.h"
#include <iostream>
#include <fstream>

GameViewPlayer::GameViewPlayer() // Player window constructor
{
    if(!initialized)
    {
        std::cout << "initializing" << std::endl;
        initializeMenuState();
        initializePlayState();
        logic = new GameLogic();
        //loadedAudio = new AudioLoader();
        majorTom = new MajorTom(loadedTextures);
    }
    initialized = true;
}

/** \brief
 *
 * \return void
 *
 */
void GameViewPlayer::initializeMenuState()
{

    loadedTextures = new TextureLoader();
    loadedAudio = new AudioLoader();

    //sound was a bit loud so I adjusted it
    menuSelection.setVolume(75);
    menuTransition.setVolume(75);
    gameMusic.setVolume(45);
    textMusic.setVolume(40);

    menuTransition.setBuffer(loadedAudio -> soundTrack[21]);
    menuSelection.setBuffer(loadedAudio -> soundTrack[22]);

    menuBackground.setSize(sf::Vector2f(1,1));

    menuBackground.setPosition(0,0);
    menuBackground.setSize(sf::Vector2f(1440,900));
    menuBackground.setTexture(&(loadedTextures -> textureArray[4]));

    playBtnRec.setOrigin((1308/2),0);
    playBtnRec.setPosition(1440,400);
    playBtnRec.setSize(sf::Vector2f((1308/2),(224/2)));
    playBtnRec.setTexture(&(loadedTextures -> textureArray[6]));

    storyBtnRec.setOrigin((1050/2),0);
    storyBtnRec.setPosition(1440,530);
    storyBtnRec.setSize(sf::Vector2f((1050/2),(117/2)));
    storyBtnRec.setTexture(&(loadedTextures -> textureArray[7]));

    exitBtnRec.setOrigin((444),0);
    exitBtnRec.setPosition(1440,605);
    exitBtnRec.setSize(sf::Vector2f(444,(117/2)));
    exitBtnRec.setTexture(&(loadedTextures -> textureArray[9]));
}

/** \brief
 *
 * \return void
 *
 */
void GameViewPlayer::initializePlayState()
{
    if(!gameFont.loadFromFile("../assets/impact.ttf"))
        std::cout << "Could not load requested font." << std::endl;

    if (!lockIcon.loadFromFile("../assets/lockIcon.png"))
        std::cout << "Failed to Load Lock Icon." << std::endl;

    //Store the reload rectangles into the array
    reloadRect[0] = reload1;
    reloadRect[1] = reload2;
    reloadRect[2] = reload3;
    reloadRect[3] = reload4;
    reloadRect[4] = reload5;
    reloadRect[5] = reload6;
    reloadRect[6] = reload7;

    sky.setRadius(894);
    sky.setOrigin(894,894);
    sky.setPosition(720, 450);
    sky.setTexture(&(loadedTextures->textureArray[2]));

    nightSky.setPosition(0,0);
    nightSky.setSize(sf::Vector2f(1440,760));
    nightSky.setFillColor(sf::Color(255,255,255,0));
    nightSky.setTexture(&(loadedTextures->textureArray[16]));

    fogSky.setPosition(0,0);
    fogSky.setSize(sf::Vector2f(1440,760));
    fogSky.setFillColor(sf::Color(255,255,255,100));
    fogSky.setTexture(&(loadedTextures->textureArray[24]));

    background.setOrigin(0,724);
    background.setPosition(0,900);
    background.setSize(sf::Vector2f(1440,724));
    background.setTexture(&(loadedTextures -> textureArray[1]));

    lossScreen.setOrigin(0,900);
    lossScreen.setPosition(0,900);
    lossScreen.setSize(sf::Vector2f(1440,900));
    lossScreen.setTexture(&(loadedTextures -> textureArray[11]));

    winScreen.setOrigin(0,900);
    winScreen.setPosition(0,900);
    winScreen.setSize(sf::Vector2f(1440,900));
    winScreen.setTexture(&loadedTextures -> textureArray[17]);

    menuBtnRec.setPosition(215,780);
    menuBtnRec.setSize(sf::Vector2f(366,79));
    menuBtnRec.setTexture(&loadedTextures->textureArray[20]);

    winBtnRec.setPosition(900,780);
    winBtnRec.setSize(sf::Vector2f(366,79));
    winBtnRec.setTexture(&loadedTextures->textureArray[21]);

    retryBtnRec.setPosition(200, 600);
    retryBtnRec.setSize(sf::Vector2f(366, 79));
    retryBtnRec.setTexture(&(loadedTextures->textureArray[13]));

    giveUpBtnRec.setPosition(900, 600);
    giveUpBtnRec.setSize(sf::Vector2f(366,79));
    giveUpBtnRec.setTexture(&(loadedTextures->textureArray[14]));

    //Weapon icon and reload rectangle inits
    weapon1.setTextureRect(sf::IntRect(256,0,32,32));
    weapon2.setTextureRect(sf::IntRect(256,32,32,32));
    weapon3.setTextureRect(sf::IntRect(288,0,32,32));
    weapon4.setTextureRect(sf::IntRect(288,32,32,32));
    //the following x values were adjusted as the sprites overlapped for some reason
    weapon5.setTextureRect(sf::IntRect(322,0,32,32));
    weapon6.setTextureRect(sf::IntRect(322,32,32,32));
    weapon7.setTextureRect(sf::IntRect(353,0,32,32));
    weapon1.setPosition(295,790);
    reloadRect[0].setPosition(376,867);
    weapon2.setPosition(423,790);
    reloadRect[1].setPosition(503,867);
    weapon3.setPosition(551,790);
    reloadRect[2].setPosition(632,867);
    weapon4.setPosition(679,790);
    reloadRect[3].setPosition(760,867);
    weapon5.setPosition(807,790);
    reloadRect[4].setPosition(888,867);
    weapon6.setPosition(935,790);
    reloadRect[5].setPosition(1016,867);
    weapon7.setPosition(1063,790);
    reloadRect[6].setPosition(1143,867);
    weapon1.setTexture(loadedTextures->textureArray[0]);
    weapon2.setTexture(loadedTextures->textureArray[0]);
    weapon3.setTexture(loadedTextures->textureArray[0]);
    weapon4.setTexture(loadedTextures->textureArray[0]);
    weapon5.setTexture(loadedTextures->textureArray[0]);
    weapon6.setTexture(loadedTextures->textureArray[0]);
    weapon7.setTexture(loadedTextures->textureArray[0]);
    weapon1.setScale(sf::Vector2f(2.5f,2.5f));
    weapon2.setScale(sf::Vector2f(2.5f,2.5f));
    weapon3.setScale(sf::Vector2f(2.5f,2.5f));
    weapon4.setScale(sf::Vector2f(2.5f,2.5f));
    weapon5.setScale(sf::Vector2f(2.5f,2.5f));
    weapon6.setScale(sf::Vector2f(2.5f,2.5f));
    weapon7.setScale(sf::Vector2f(2.5f,2.5f));

    for(int i = 0; i<7; ++i)
    {
        reloadRect[i].setFillColor(sf::Color(255,255,255,51));
        reloadRect[i].setSize(sf::Vector2f(64,0));
        reloadRect[i].setScale(sf::Vector2f(1.25f,1.25f));
        reloadRect[i].setRotation(180.f);
    }

    //Box around the selected weapon
    selectionBox.setTexture(loadedTextures->textureArray[0]);
	selectionBox.setTextureRect(sf::IntRect(0,896,95,95));
	selectionBox.setPosition(285,780);//init the selection box onto the first weapon

    //Survivor Count Display
    survivorCnt.setFont(gameFont);
    survivorCnt.setCharacterSize(22);
    survivorCnt.setString("20/20 Survivors");//might be able to take this out after survivor count is looped in updater
    survivorCnt.setFillColor(sf::Color(0,0,0,255));
    survivorCnt.setPosition(75,860);

    //Score count display
    scoreCnt.setFont(gameFont);
    scoreCnt.setCharacterSize(22);
    scoreCnt.setString("0");//might be able to take out due to updater code redundancy
    scoreCnt.setFillColor(sf::Color(0,0,0,255));
    scoreCnt.setPosition(1215,860);

    //Level count display
    levelCnt.setFont(gameFont);
    levelCnt.setCharacterSize(22);
    levelCnt.setString("/20");//might be able to take out due to updater code redundancy
    levelCnt.setFillColor(sf::Color(0,0,0,255));
    levelCnt.setPosition(1215,770);

    //Major Tom Health Display
	majorTomHealth.setFont(gameFont);
	majorTomHealth.setCharacterSize(22);
	majorTomHealth.setString("100/100 Health");//might be able to take this out after survivor count is looped in updater
	majorTomHealth.setFillColor(sf::Color(0,0,0,255));
	majorTomHealth.setPosition(75,770);

	//Paused message
    pausedMsg.setFont(gameFont);
    pausedMsg.setCharacterSize(22);
    pausedMsg.setString("Game Paused\nPress P to continue.");//might be able to take out due to updater code redundancy
    pausedMsg.setFillColor(sf::Color(0,0,0,255));
    pausedMsg.setPosition(680,113);

}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return bool
 *
 */
bool GameViewPlayer::menuViewIsOpen(sf::RenderWindow& window)
{
    gameMusic.stop();
    gameMusic.setBuffer(loadedAudio -> soundTrack[20]);
    gameMusic.play();
    gameMusic.setLoop(true);
    menuSelector.setPosition(0,0);
    returnToMenu = false;
    timesDied = 0;
    while(window.isOpen()) // Menu loop
	{
        updateMenu(window);
		while(window.pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed)
			{
				window.close(); // Quit game
				return true;
			}

			if(Event.type == sf::Event::KeyPressed)
			{
				if(Event.key.code == sf::Keyboard::Up)
				{
					if(sf::Vector2f (0,0) == menuSelector.getPosition())
					{
						menuSelector.setPosition(0,2);
						selectMenuButton(window,2);
						menuTransition.play();
					}
					else if(sf::Vector2f (0,1) == menuSelector.getPosition())
					{
						menuSelector.setPosition(0,0);
						selectMenuButton(window,0);
						menuTransition.play();
					}
					else if(sf::Vector2f (0,2) == menuSelector.getPosition())
					{
						menuSelector.setPosition(0,1);
						selectMenuButton(window,1);
						menuTransition.play();
					}
				}

				if(Event.key.code == sf::Keyboard::Down)
				{
					if(sf::Vector2f (0,0) == menuSelector.getPosition())
					{
						menuSelector.setPosition(0,1);
						selectMenuButton(window,1);
						menuTransition.play();
					}
					else if(sf::Vector2f (0,1) == menuSelector.getPosition())
					{
						menuSelector.setPosition(0,2);
						selectMenuButton(window,2);
						menuTransition.play();
					}
					else if(sf::Vector2f (0,2) == menuSelector.getPosition())
					{
						menuSelector.setPosition(0,0);
						selectMenuButton(window,0);
						menuTransition.play();
					}
				}

				if(Event.key.code == sf::Keyboard::Return)
				{
					if(sf::Vector2f (0,0) == menuSelector.getPosition())
					{
						menuSelection.play();
						sf::sleep(sf::milliseconds(900)); //the fix
						gameMusic.stop();
						return false;
					}
					if(sf::Vector2f (0,1) == menuSelector.getPosition())
					{
						menuSelection.play();
						sf::sleep(sf::milliseconds(900)); //the fix
						storyViewIsOpen(window);
					}
					if(sf::Vector2f (0,2) == menuSelector.getPosition())
					{
						menuSelection.play();
						sf::sleep(sf::milliseconds(900)); //the fix
						window.close();
						menuExit = true;
						return true;
					}
				}
			}
		}
	}
	return false;
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return bool
 *
 */
bool GameViewPlayer::storyViewIsOpen(sf::RenderWindow& window)
{
    controlScreen.setPosition(450,25);
    controlScreen.setTexture(&loadedTextures -> textureArray[23]);
    controlScreen.setSize(sf::Vector2f(658,839));

    window.draw(controlScreen);
    window.display();

    while(window.isOpen())
    {
        while(window.pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed)
			{
				window.close(); // Quit game
				return true;
			}

			if(Event.type == sf::Event::KeyPressed)
			{
			    if(Event.key.code == sf::Keyboard::Return || Event.key.code == sf::Keyboard::Escape)
                {
                    menuSelection.play();
                    return false;
                }
			}
		}
    }
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return void
 *
 */
void GameViewPlayer::updateMenu(sf::RenderWindow& window) // Updates screen
{
    window.clear(sf::Color::Black);
    window.draw(menuBackground);
    window.draw(playBtnRec);
    window.draw(storyBtnRec);
    window.draw(exitBtnRec);

    // display
    window.display();
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return bool
 *
 */
bool GameViewPlayer::gameViewIsOpen(sf::RenderWindow& window)
{
    currentLevel = logic -> getLevel() - 1;

    sf::Clock fireRate1;
    sf::Clock fireRate2;

    float fireGun = fireRate1.getElapsedTime().asSeconds();


    sf::Clock gameClock;
    float delta;

    bool keepMovingUp = false;
    bool keepMovingDown = false;
    bool lockOutKeyboard = false;

    while(window.isOpen())
    {
        if(logic -> isTankBossDead())
        {
            bool exit;
            exit = winViewIsOpen(window);
            return exit;
        }

        updateGame(window);
        delta = gameClock.getElapsedTime().asSeconds();

        if (!window.hasFocus())
        {
        	paused = true;
        }

        if(paused)
        {
        	delta = 0;
        	gameMusic.pause();
        	lockOutKeyboard = true;
        }


        gameClock.restart();

//-----------------------------------------------------------------

        if (logic -> checkEnd(majorTom))
        {
            logic -> clearAssets();
            break;
        }

        if (logic -> currentLevelEnd())
        {
            logic -> pauseGame();
            logic -> levelWon = false;
            if(textAdventureIsOpen(window))
                return true;
        }

        if(currentLevel < logic -> getLevel())
        {
            gameMusic.stop();
            gameMusic.setBuffer(loadedAudio->soundTrack[logic -> getLevel() - 1]);
            gameMusic.play();
            gameMusic.setLoop(true);
        }

        currentLevel = logic -> getLevel();

        logic -> pauseGame();

        if (!paused)
        {
			logic -> runLevel(sky, majorTom, delta, nightSky, fogSky);
			logic -> updateKoratOrder();
			logic -> updateBulletOrder(); //Bullets generation and drawing
			logic -> updateDyingKorat(majorTom);
			logic -> moveKorat(delta, majorTom);
			logic -> queryKoratFiring();


			if (logic -> getLevel() == 10)
			{
				logic -> moveBikeBoss(sky, majorTom, delta);
				logic -> queryBikeFiring();
				logic -> updateDyingBikeBoss(majorTom);
			}
			if (logic -> getLevel() == 20)
			{
				logic -> moveTankBoss(sky, majorTom, delta);
				logic -> queryTankFiring();
				logic -> updateDyingTankBoss(majorTom);
			}

			logic -> moveBullet(delta);
			logic -> moveKoratBullet(delta, majorTom);
            logic -> updateDyingTankBoss(majorTom);
        }

        int logicKilledKorat = logic -> getKilledKorat();
        if (logicKilledKorat > koratKilled)
        {
        	//for loop to count how many times to play death sound
        for(logicKilledKorat; logicKilledKorat > koratKilled; koratKilled++)
        {
				koratDyingSound.stop();
				koratDyingSound.setBuffer(loadedAudio->soundTrack[25]);
				koratDyingSound.setVolume(60);
				koratDyingSound.play();
        }
        }

        int logicJackalBulletsFired = logic -> getJackalBulletsFired();
		if (logicJackalBulletsFired > jackalBulletsFired)
		{
        for(logicJackalBulletsFired; logicJackalBulletsFired > jackalBulletsFired; jackalBulletsFired++)
        {
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[27]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
        }
		}

        int logicEliteBulletsFired = logic -> getEliteBulletsFired();
		if (logicEliteBulletsFired > eliteBulletsFired)
		{
			for(logicEliteBulletsFired; logicEliteBulletsFired > eliteBulletsFired; eliteBulletsFired++)
			{
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[27]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
			}
		}

        int logicBruteBulletsFired = logic -> getBruteBulletsFired();
		if (logicBruteBulletsFired > bruteBulletsFired)
		{
			for(logicBruteBulletsFired; logicBruteBulletsFired > bruteBulletsFired; bruteBulletsFired++)
			{
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[28]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
			}
		}

        int logicHunterBulletsFired = logic -> getHunterBulletsFired();
		if (logicHunterBulletsFired > hunterBulletsFired)
		{
			for(logicHunterBulletsFired; logicHunterBulletsFired > hunterBulletsFired; hunterBulletsFired++)
			{
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[40]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
			}
		}

        int logicBikerBulletsFired = logic -> getBikerBulletsFired();
		if (logicBikerBulletsFired > bikerBulletsFired)
		{
			for(logicBikerBulletsFired; logicBikerBulletsFired > bikerBulletsFired; bikerBulletsFired++)
			{
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[29]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
			}
		}
        int logicBombersExploded = logic -> getBombersExploded();
		if (logicBombersExploded > bombersExploded)
		{
			for(logicBombersExploded; logicBombersExploded > bombersExploded; bombersExploded++)
			{
				bomberExplodingSound.stop();
				bomberExplodingSound.setBuffer(loadedAudio->soundTrack[26]);
				bomberExplodingSound.setVolume(100);
				bomberExplodingSound.play();
			}
		}

		int logicKoratHitCount = logic -> getKoratHitCount();
		if (logicKoratHitCount > koratHitCount)
		{
			//for loop to count how many times to play death sound
			for(logicKoratHitCount; logicKoratHitCount > koratHitCount; koratHitCount++)
			{
				koratHitSound.stop();
				koratHitSound.setBuffer(loadedAudio->soundTrack[30]);
				koratHitSound.setVolume(60);
				koratHitSound.play();
			}
		}

		int logicKoratSurvived = logic -> getKoratSurvived();
		if (logicKoratSurvived > koratSurvived)
		{
			for(logicKoratSurvived; logicKoratSurvived > koratSurvived; koratSurvived++)
			{
				koratSurvivedSound.stop();
				koratSurvivedSound.setBuffer(loadedAudio->soundTrack[39]);
				koratSurvivedSound.setVolume(60);
				koratSurvivedSound.play();
			}
		}

		int logicTankBossBulletsFired = logic -> getTankBossBulletsFired();
		if (logicTankBossBulletsFired > tankBossBulletsFired)
		{
			for(logicTankBossBulletsFired; logicTankBossBulletsFired > tankBossBulletsFired; tankBossBulletsFired++)
			{
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[40]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
			}
		}

		int logicTopBikerBulletsFired = logic -> getTopBikerBulletsFired();
		if (logicTopBikerBulletsFired > topBikerBulletsFired)
		{
			for(logicTopBikerBulletsFired; logicTopBikerBulletsFired > topBikerBulletsFired; topBikerBulletsFired++)
			{
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[27]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
			}
		}

		int logicMiddleBikerBulletsFired = logic -> getMiddleBikerBulletsFired();
		if (logicMiddleBikerBulletsFired > middleBikerBulletsFired)
		{
			for(logicMiddleBikerBulletsFired; logicMiddleBikerBulletsFired > middleBikerBulletsFired; middleBikerBulletsFired++)
			{
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[37]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
			}
		}

		int logicBottomBikerBulletsFired = logic -> getBottomBikerBulletsFired();
		if (logicBottomBikerBulletsFired > bottomBikerBulletsFired)
		{
			for(logicBottomBikerBulletsFired; logicBottomBikerBulletsFired > bottomBikerBulletsFired; bottomBikerBulletsFired++)
			{
				koratFiringSound.stop();
				koratFiringSound.setBuffer(loadedAudio->soundTrack[29]);
				koratFiringSound.setVolume(60);
				koratFiringSound.play();
			}
		}
//-----------------------------------------------------------------
        if(keepMovingUp == true)
        {
            keepMovingUp = majorTom->keepMoving(delta, "Up");
            lockOutKeyboard = true;
        }
        else if(keepMovingDown == true)
        {
            keepMovingDown = majorTom->keepMoving(delta, "Down");
            lockOutKeyboard = true;
        }
        else if(paused)
        {
        	lockOutKeyboard = true;
        }
        else
            lockOutKeyboard = false;

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if(lockOutKeyboard == false)
                {
                     switch(majorTom -> getGun())
                    {
                        case 1:
                        	if (logic -> fireBullet(majorTom, majorTom -> pistol, delta)) //if the gun fired
                        	{
                        		playerWeaponSound.stop();
								playerWeaponSound.setBuffer(loadedAudio->soundTrack[31]); //plasma pistol sound
								playerWeaponSound.setVolume(60);
								playerWeaponSound.play();
                        	}
                        	break;
                        case 2:
                            if (logic -> getLevel() >= 3)
                            {
                                if (logic -> fireBullet(majorTom, majorTom -> shotgun, delta))
                                {
                                	playerWeaponSound.stop();
									playerWeaponSound.setBuffer(loadedAudio->soundTrack[32]);
									playerWeaponSound.setVolume(60);
									playerWeaponSound.play();
                                }
                            }
                            break;
                        case 3:
                            if (logic -> getLevel() >= 5)
                            {
                            	if (logic -> fireBullet(majorTom, majorTom -> rifle, delta))
                            	{
                                    playerWeaponSound.stop();
    								playerWeaponSound.setBuffer(loadedAudio->soundTrack[33]);
    								playerWeaponSound.setVolume(60);
    								playerWeaponSound.play();
                            	}
                            }
                            break;
                        case 4:
                            if (logic -> getLevel() >= 7)
                            {
                            	if(logic -> fireBullet(majorTom, majorTom -> minigun, delta))
                            	{
                                    playerWeaponSound.stop();
    								playerWeaponSound.setBuffer(loadedAudio->soundTrack[34]);
    								playerWeaponSound.setVolume(45);
    								playerWeaponSound.play();
                            	}
                            }
                            break;
                        case 5:
                            if (logic -> getLevel() >= 9)
                            {
                            	if (logic -> fireBullet(majorTom, majorTom -> thrower, delta))
                            	{
                                    playerWeaponSound.stop();
    								playerWeaponSound.setBuffer(loadedAudio->soundTrack[35]);
    								playerWeaponSound.setVolume(60);
    								playerWeaponSound.play();
                            	}
                            }
                            break;
                        case 6:
                            if (logic -> getLevel() >= 11)
                            {
                            	if (logic -> fireBullet(majorTom, majorTom -> sniper, delta))
                            	{
                                    playerWeaponSound.stop();
    								playerWeaponSound.setBuffer(loadedAudio->soundTrack[36]);
    								playerWeaponSound.setVolume(60);
    								playerWeaponSound.play();
                            	}
                            }
                            break;
                        case 7:
                            if (logic -> getLevel() >= 13)
                            {
                            	if (logic -> fireBullet(majorTom, majorTom -> bigFunGun, delta))
                            	{
                                    playerWeaponSound.stop();
    								playerWeaponSound.setBuffer(loadedAudio->soundTrack[37]);
    								playerWeaponSound.setVolume(60);
    								playerWeaponSound.play();
                            	}
                            }
                            break;
                        default:
                        	if (logic -> fireBullet(majorTom, majorTom -> pistol, delta)) //if the gun fired
                        	{
                        		playerWeaponSound.stop();
								playerWeaponSound.setBuffer(loadedAudio->soundTrack[31]); //plasma pistol sound
								playerWeaponSound.setVolume(60);
								playerWeaponSound.play();
                        	}
                        	break;
                    }
                }
            }

         while(window.pollEvent(Event))
            {
                if(Event.type == sf::Event::Closed)
                {
                    gameMusic.stop();
                    window.close(); // Quit game
                    return true;
                }

                if(Event.type == sf::Event::KeyPressed)
                {
                    if(Event.key.code == sf::Keyboard::Escape)
                    {
                        gameMusic.stop();
                        window.close();
                        return true;
                    }

                    if(Event.key.code == sf::Keyboard::Up)
                    {
                        if(lockOutKeyboard == false)
                        keepMovingUp = majorTom->initMove(delta, "Up");
                    }

                    if(Event.key.code == sf::Keyboard::Down)
                    {
                        if(lockOutKeyboard == false)
                        keepMovingDown = majorTom->initMove(delta, "Down");
                    }

                    if(Event.key.code == sf::Keyboard::W)
                    {
                        if(lockOutKeyboard == false)
                        keepMovingUp = majorTom->initMove(delta, "Up");
                    }

                    if(Event.key.code == sf::Keyboard::S)
                    {
                        if(lockOutKeyboard == false)
                        keepMovingDown = majorTom->initMove(delta, "Down");
                    }

                    if(Event.key.code == sf::Keyboard::Num1)
                    {
                        if(lockOutKeyboard == false)
                        {
                            majorTom->setGun(1);
                            selectionBox.setPosition(285,780);
                        }
                    }

                    if(Event.key.code == sf::Keyboard::Num2)
                    {
                        if(lockOutKeyboard == false)
                        {
                        	if (logic -> getLevel() >= 3)
                        	{
                        		majorTom->setGun(2);
								selectionBox.setPosition(413,780);
                        	}
                        }

                    }

                    if(Event.key.code == sf::Keyboard::Num3)
                    {
                        if(lockOutKeyboard == false)
                        {
                        	if (logic -> getLevel() >= 5)
                        	{
								majorTom->setGun(3);
								selectionBox.setPosition(541,780);
                        	}
                        }
                    }

                    if(Event.key.code == sf::Keyboard::Num4)
                    {
                        if(lockOutKeyboard == false)
                        {
                        	if (logic -> getLevel() >= 7)
                        	{
								majorTom->setGun(4);
								selectionBox.setPosition(669,780);
                        	}
                        }
                    }

                    if(Event.key.code == sf::Keyboard::Num5)
                    {
                        if(lockOutKeyboard == false)
                        {
                        	if (logic -> getLevel() >= 9)
                        	{
								majorTom->setGun(5);
								selectionBox.setPosition(797,780);
                        	}
                        }
                    }

                    if(Event.key.code == sf::Keyboard::Num6)
                    {
                        if(lockOutKeyboard == false)
                        {
                        	if (logic -> getLevel() >= 11)
                        	{
								majorTom->setGun(6);
								selectionBox.setPosition(925,780);
                        	}
                        }
                    }

                    if(Event.key.code == sf::Keyboard::Num7)
                    {
                        if(lockOutKeyboard == false)
                        {
                        	if (logic -> getLevel() >= 13)
                        	{
                        		majorTom->setGun(7);
                                selectionBox.setPosition(1053,780);
                        	}
                        }
                    }
                    if(Event.key.code == sf::Keyboard::K)
                    {
                        sky.rotate(150);
                    }

                    if(Event.key.code == sf::Keyboard::P)
					{
                    	paused = !paused;
                    	if (paused)
                    	{
                    		lockOutKeyboard = true;
                    		gameMusic.pause();
                    	} else {
                    		lockOutKeyboard = false;
                    		gameMusic.play();
                    	}
					}
                }
            }
        }
    return false;
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return bool
 *
 */
bool GameViewPlayer::textAdventureIsOpen(sf::RenderWindow& window)
{

    gameMusic.stop();
    gameMusic.setBuffer(loadedAudio->soundTrack[24]);
    gameMusic.play();
    gameMusic.setLoop(true);

    window.clear(sf::Color::Black);
    drawAdventure(window);

    while(window.isOpen())
    {
        if (delayClockStarted == false)
        {
            delayClock.restart();
        }
        delayClockStarted = true;
        delayClockTime = delayClock.getElapsedTime().asSeconds();

        while(window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                window.close();
                return true;
            }
            if(Event.type == sf::Event::KeyPressed)
            {
                if(Event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    return true;
                }
                if(Event.key.code == sf::Keyboard::Return)
                {
                    if(delayClockTime > 1)
                    {
                        menuSelection.play();
                        gameMusic.stop();
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return void
 *
 */
void GameViewPlayer::drawAdventure(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    std::string adventure;
    std::string sol;
    sf::Text solNum;
    std::string line;
    std::ifstream currentAdventure;
    int offset = 0;
    std::string fileString;
    fileString = "../assets/TextAdventures/Level" + std::to_string(logic->getLevel())+ ".txt";

    if (currentLevel == 10)
        fileString = "../assets/TextAdventures/Level11.txt";
    currentAdventure.open(fileString);

    journal.setPosition(450,25);
    journal.setTexture(&loadedTextures -> textureArray[18]);
    journal.setSize(sf::Vector2f(537,839));

    solNum.setFont(gameFont);
    solNum.setCharacterSize(20);
    solNum.setFillColor(sf::Color::Black);
    solNum.setPosition(475,75);
    sol = "" + std::to_string(logic -> getLevel());
    if(currentLevel == 10)
        sol = "11";
    solNum.setString(sol);

    window.draw(sky);
    window.draw(background);
    majorTom -> drawTom(window);
    window.draw(journal);
    window.draw(solNum);
    fogSky.setFillColor(sf::Color(255,255,255,100));
    window.draw(fogSky);

    textAdventure.setFont(gameFont);
    textAdventure.setCharacterSize(24);
    textAdventure.setFillColor(sf::Color::Black);

    while(getline(currentAdventure,line))
    {
        adventure = line;
        textAdventure.setString(adventure);
        textAdventure.setPosition(475, 100 + offset);
        window.draw(textAdventure);
        offset += 40;
    }
    for(int i = 0; i < 7; ++i)
    {
        for(int c = 0; c < 7; ++c)
        {
            reloadRect[c].setSize(sf::Vector2f(32.f,0.f));
        }
    }


    window.display();
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return bool
 *
 */
bool GameViewPlayer::lossViewIsOpen(sf::RenderWindow& window)
{
    gameMusic.stop();
    gameMusic.setBuffer(loadedAudio -> soundTrack[23]);
    gameMusic.play();
    gameMusic.setLoop(true);
    timesDied = timesDied + 1;

    bool retry = false;
    updateLossScreen(window);
    while(window.isOpen() && !retry)
    {

        if (delayClockStarted == false)
        {
            delayClock.restart();
        }
        delayClockStarted = true;
        delayClockTime = delayClock.getElapsedTime().asSeconds();
        while(window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                gameMusic.stop();
                window.close(); // Quit game
                return true;
            }

            if(Event.type == sf::Event::KeyPressed)
            {
                if(Event.key.code == sf::Keyboard::Escape)
                {
                    gameMusic.stop();
                    window.close();
                    return true;
                }

                if(Event.key.code == sf::Keyboard::Left || Event.key.code == sf::Keyboard::Right)
                {
                    if (selector.y == 1)
                    {
                        selector.y = 0;
                        selectButton(window, selector.y);
                    }
                    else
                    {
                        selector.y = 1;
                        selectButton(window, selector.y);
                    }
                }

                if(Event.key.code == sf::Keyboard::Return)
                {
                    menuSelection.play();
                    if(delayClockTime > 1)
                    {
                        if (selector.y == 0)
                        {
                            retry = true;
                            logic -> loseLevel(sky, majorTom);
                            return false;
                        }
                        else if (selector.y == 1)
                        {
                            gameMusic.stop();
                            majorTom -> setHealth(100);
                            majorTom -> setSurvivors(20);
                            sky.rotate(-logic -> getRotation());
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return bool
 *
 */
bool GameViewPlayer::winViewIsOpen(sf::RenderWindow& window)
{
    gameMusic.stop();
    gameMusic.setBuffer(loadedAudio -> soundTrack[38]);
    gameMusic.play();
    gameMusic.setLoop(true);

    window.clear(sf::Color::Black);

    finalScoreCnt.setFont(gameFont);
    finalScoreCnt.setPosition(sf::Vector2f(625,700));
    finalScoreCnt.setFillColor(sf::Color::White);
    finalScoreCnt.setCharacterSize(22);
    string finalScore = "Final Score: " + std::to_string(majorTom -> getScore());
    finalScoreCnt.setString(finalScore);

    koratKilledCnt.setFont(gameFont);
    koratKilledCnt.setPosition(sf::Vector2f(625, 750));
    koratKilledCnt.setFillColor(sf::Color::White);
    koratKilledCnt.setCharacterSize(22);
    int koratKilled = logic -> getKilledKorat();
    int bombersExploded = logic -> getBombersExploded();
    string koratKill = "Korat Killed: " + std::to_string(koratKilled + bombersExploded);
    koratKilledCnt.setString(koratKill);

    finalDeathCnt.setFont(gameFont);
    finalDeathCnt.setPosition(sf::Vector2f(650,800));
    finalDeathCnt.setFillColor(sf::Color::White);
    finalDeathCnt.setCharacterSize(22);
    string finalDeath = "Times Died: " + std::to_string(timesDied);
    finalDeathCnt.setString(finalDeath);


    updateWinScreen(window);
    int x = 0;


    while(window.isOpen())

    {
         while(window.pollEvent(Event))
         {
                if(Event.type == sf::Event::Closed)
                {
                    gameMusic.stop();
                    window.close(); // Quit game
                    return true;
                }
                if(Event.type == sf::Event::KeyPressed)
                {
                    if(Event.key.code == sf::Keyboard::Return)
                    {
                        menuSelection.play();
                        if(x == 0)
                        {
                            sky.rotate(-(logic -> getRotation()));
                            logic -> setLevel(1);
                            logic -> setTankBossBool(false);

                            majorTom -> setSurvivors(20);
                            majorTom -> setHealth(100);
                            majorTom -> setScore(0);

                            returnToMenu = true;
                            logic -> firstLevel = true;
                            return false;
                        }
                        if(x == 1)
                        {
                            window.close();
                            return true;
                        }
                    }

                    if(Event.key.code == sf::Keyboard::Escape)
                    {
                        gameMusic.stop();
                        window.close();
                        return true;
                    }

                    if(Event.key.code == sf::Keyboard::Left || Event.key.code == sf::Keyboard::Right)
                    {
                        if (x == 0)
                        {
                            x = 1;
                            selectWinButton(window, x);
                            updateWinScreen(window);
                        }
                        else
                        {
                            x = 0;
                            selectWinButton(window, x);
                            updateWinScreen(window);
                        }
                    }
                }
        }
    }

}

void GameViewPlayer::updateWinScreen(sf::RenderWindow& window)
{
    window.draw(winScreen);
    window.draw(finalScoreCnt);
    window.draw(koratKilledCnt);
    window.draw(finalDeathCnt);
    window.draw(winBtnRec);
    window.draw(menuBtnRec);
    window.display();
    for(int i = 0; i < 7; ++i)
    {
        for(int c = 0; c < 7; ++c)
        {
            reloadRect[c].setSize(sf::Vector2f(64.f,0.f));
        }
    }
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return void
 *
 */
void GameViewPlayer::resetGameToMenu(sf::RenderWindow& window)
{
    delete logic;
    GameLogic* logic = new GameLogic();
    logic -> pauseGame();
    menuViewIsOpen(window);
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return void
 *
 */
void GameViewPlayer::updateGame(sf::RenderWindow& window) // Draws all elements of screen
{
    window.clear(sf::Color::Black);

    window.draw(sky);
    window.draw(background);
    majorTom -> drawTom(window);

    logic -> drawKorat(window);


    if (logic -> getLevel() == 10)
    {
        logic -> drawBikeBoss(window);
    }
    if (logic -> getLevel() == 20)
    {
        logic -> drawTankBoss(window);
    }

    window.draw(nightSky);
    window.draw(fogSky);
    window.draw(selectionBox);
    window.draw(scoreCnt);
    window.draw(levelCnt);
    if(paused)
    	window.draw(pausedMsg);

    logic -> drawBullet(window);


    window.draw(survivorCnt);
    window.draw(majorTomHealth);
    window.draw(weapon1);
    if (logic -> getLevel() >= 3)
    	window.draw(weapon2);
    if (logic -> getLevel() >= 5)
    	window.draw(weapon3);
    if (logic -> getLevel() >= 7)
    	window.draw(weapon4);
    if (logic -> getLevel() >= 9)
    	window.draw(weapon5);
    if (logic -> getLevel() >= 11)
    	window.draw(weapon6);
    if (logic -> getLevel() >= 13)
    	window.draw(weapon7);

    for(int i = 0; i < 7; ++i)
    {

        if(logic->reloadStarted == true) // Draw reload symbol <----------
        {

            if (majorTom -> getGun() == savedGun)
            {
                reloadRect[majorTom->currentGun-1].setSize(sf::Vector2f(64.f,64.f));//reloadRect[majorTom->currentGun - 1].setSize(sf::Vector2f(64.f,(64.f * ((logic->reloadClock.getElapsedTime().asSeconds())-1))*2));
                reloadRect[majorTom->currentGun-1].setFillColor(sf::Color(255,0,0,125));
            }

            else
            {
                logic-> reloadStarted = false;
            }
        }

            switch(majorTom -> getGun())
            {
                case 1: if((logic -> reloadClock.getElapsedTime().asSeconds() > majorTom->pistol->getReloadSpeed()))
                        {
                            reloadRect[majorTom->currentGun-1].setSize(sf::Vector2f(64.f,0.f));
                        }
                        savedGun = 1;
                        break;
                case 2: if(logic -> reloadClock.getElapsedTime().asSeconds() > (majorTom->shotgun->getReloadSpeed()))
                        {
                            reloadRect[majorTom->currentGun-1].setSize(sf::Vector2f(64.f,0.f));
                        }
                        savedGun = 2;
                        break;
                case 3: if(logic -> reloadClock.getElapsedTime().asSeconds() > (majorTom->rifle->getReloadSpeed()))
                        {
                            reloadRect[majorTom->currentGun-1].setSize(sf::Vector2f(64.f,0.f));
                        }
                        savedGun = 3;
                        break;
                case 4: if(logic -> reloadClock.getElapsedTime().asSeconds() > (majorTom->minigun->getReloadSpeed()))
                        {
                            reloadRect[majorTom->currentGun-1].setSize(sf::Vector2f(64.f,0.f));
                        }
                        savedGun = 4;
                        break;
                case 5: if(logic -> reloadClock.getElapsedTime().asSeconds() > (majorTom->thrower->getReloadSpeed()))
                        {
                            reloadRect[majorTom->currentGun-1].setSize(sf::Vector2f(64.f,0.f));
                        }
                        savedGun = 5;
                        break;
                case 6: if(logic -> reloadClock.getElapsedTime().asSeconds() > (majorTom->sniper->getReloadSpeed()))
                        {
                            reloadRect[majorTom->currentGun-1].setSize(sf::Vector2f(64.f,0.f));
                        }
                        savedGun = 6;
                        break;
                case 7: if(logic -> reloadClock.getElapsedTime().asSeconds() > (majorTom->bigFunGun->getReloadSpeed()))
                        {
                            reloadRect[majorTom->currentGun-1].setSize(sf::Vector2f(64.f,0.f));
                        }
                        savedGun = 7;
                        break;
            }
            window.draw(reloadRect[i]);
    }

    updateSurvivorCount();
    updateMajorTomHealth();
    updateScoreCount();
    updateLevelCount();

    window.display();
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \return void
 *
 */
void GameViewPlayer::updateLossScreen(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
    window.draw(lossScreen);
    window.draw(retryBtnRec);
    window.draw(giveUpBtnRec);
    window.display();
    for(int i = 0; i < 7; ++i)
    {
        for(int c = 0; c < 7; ++c)
        {
            reloadRect[c].setSize(sf::Vector2f(64.f,0.f));
        }
    }
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \param x int
 * \return void
 *
 */
void GameViewPlayer::selectWinButton(sf::RenderWindow& window, int x)
{
    if (x == 0)
    {
        menuBtnRec.setTexture(&loadedTextures -> textureArray[20]);
        winBtnRec.setTexture(&loadedTextures -> textureArray[21]);
        menuTransition.play();
    }
    if (x == 1)
    {
        menuBtnRec.setTexture(&loadedTextures -> textureArray[19]);
        winBtnRec.setTexture(&loadedTextures -> textureArray[22]);
        menuTransition.play();
    }
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \param y int
 * \return void
 *
 */
void GameViewPlayer::selectMenuButton(sf::RenderWindow& window, int y)
{
    if(y == 0)
    {
        playBtnRec.setTexture(&(loadedTextures -> textureArray[6]));
        storyBtnRec.setTexture(&(loadedTextures -> textureArray[7]));
        exitBtnRec.setTexture(&(loadedTextures -> textureArray[9]));
    }
    else if(y == 1)
    {
        playBtnRec.setTexture(&(loadedTextures -> textureArray[5]));
        storyBtnRec.setTexture(&(loadedTextures -> textureArray[8]));
        exitBtnRec.setTexture(&(loadedTextures -> textureArray[9]));
    }
    else if(y == 2)
    {
        playBtnRec.setTexture(&(loadedTextures -> textureArray[5]));
        storyBtnRec.setTexture(&(loadedTextures -> textureArray[7]));
        exitBtnRec.setTexture(&(loadedTextures -> textureArray[10]));
    }
    updateMenu(window);//could this be more optimally placed?
}

/** \brief
 *
 * \param window sf::RenderWindow&
 * \param y int
 * \return void
 *
 */
void GameViewPlayer::selectButton(sf::RenderWindow& window, int y)
{
    if(y == 0)
    {
        retryBtnRec.setTexture(&(loadedTextures->textureArray[13]));
        giveUpBtnRec.setTexture(&(loadedTextures->textureArray[14]));
        menuTransition.play();
    }
    else if(y == 1)
    {
        retryBtnRec.setTexture(&(loadedTextures->textureArray[12]));
        giveUpBtnRec.setTexture(&(loadedTextures->textureArray[15]));
        menuTransition.play();
    }
    updateLossScreen(window);
}


void GameViewPlayer::updateSurvivorCount()
{
    string cnt = std::to_string(majorTom->getSurvivors()) + "/20 Survivors";
    survivorCnt.setString(cnt);
}

void GameViewPlayer::updateMajorTomHealth()
{
	string cnt = std::to_string(majorTom->getHealth()) + "/100 Health";
	majorTomHealth.setString(cnt);
}

void GameViewPlayer::updateScoreCount()
{
    string cnt = "Score " + std::to_string(majorTom->getScore());//Used to have + score
    scoreCnt.setString(cnt);
}

void GameViewPlayer::updateLevelCount()
{
    string cnt = "Sol " + std::to_string(logic -> getLevel()) + "/20";
    levelCnt.setString(cnt);
}
