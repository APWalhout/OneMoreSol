/*
GameLogic.cpp

*/
#include "GameLogic.h"
#include "KoratBullet.h"
#include <iostream>
#include <typeinfo>

using namespace std;

GameLogic::GameLogic()
{
    loadedTextures = new TextureLoader();
    levelWon = true;
    if(currentLevel == 10)
    {
        startBikeBoss(loadedTextures);
    }
    if(currentLevel == 20)
    {
        startTankBoss(loadedTextures);
    }

}

bool GameLogic::currentLevelEnd()
{
    return levelWon;
}

bool GameLogic::checkEnd(MajorTom *majorTom)
{
    if(majorTom -> getSurvivors() <= 0 || majorTom -> getHealth() <= 0)
    {
        return true;
    }

    return false;
}

void GameLogic::updateKoratOrder()
{
    for (int i = 0; i < currentKorat.size(); i ++)
        {
            for (int j = 0; j < currentKorat[i].size(); j++)
            {
                if (j + 1 < currentKorat[i].size())
                {
                    if(currentKorat[i][j] -> getPositionX() > currentKorat[i][j+1] -> getPositionX())
                    {
                        currentKorat[i][j].swap(currentKorat[i][j+1]);
                    }
                }
            }
        }
}

void GameLogic::moveKorat(float timePassed, MajorTom* majorTom)
{
    if(!isPaused)
    {
        for (int i = 0; i < currentKorat.size(); i ++)
        {
            for (int j = 0; j < currentKorat[i].size(); j++)
            {
                if (currentKorat[i][j] -> checkSurvive() == false)
                {
                    if (currentKorat[i][j] -> checkDeath() == false)
                    {
                        if (currentKorat[i][j] -> getSpeed() == 0)
                        {
                            majorTom -> setScore(majorTom -> getScore()+20);
                            dyingKorat.emplace_back(move(currentKorat[i][j]));
                            currentKorat[i].erase(currentKorat[i].begin() + j);
                        }
                        else
                        {
                        currentKorat[i][j] -> moveCurrentKorat(timePassed);
                        }
                    }
                    else
                    {
                        // This will never be true!
                    }
                }
                else
                {
                    if(currentKorat[i][j] -> getName() == "Bomber")
                    {
                        majorTom -> setSurvivors(0);
                        break;
                    }
                    currentKorat[i].erase(currentKorat[i].begin() + j);
                    currentKoratCount--;
                    //update the gameviewplayer to reflect decremented survivors
                    majorTom -> setSurvivors(majorTom -> getSurvivors()-1);
                    std::cout << "survivor count = " << majorTom -> getSurvivors() << std::endl;
                }
            }
        }
    }
}

void GameLogic::updateDyingKorat(MajorTom* majorTom)
{
    for (int i = 0; i < dyingKorat.size(); i++)
    {
        if (dyingKorat[i] -> checkDeath() == true)
        {
            if (dyingKorat[i] -> getName() == "Bomber")
            {
                explode(*dyingKorat[i], majorTom);
            }
            dyingKorat.erase(dyingKorat.begin() + i);
            currentKoratCount--;
        }
    }
}

void GameLogic::explode(KoratEmpire &bomber, MajorTom* majorTom)
{
    for (int i = 0; i < currentKorat.size(); i ++)
    {
        cout << "Bomber's lane: " << bomber.getLane() - 1 << endl;
            for (int j = 0; j < currentKorat[i].size(); j++)
            {
                if ((bomber.getPositionX() - currentKorat[i][j] -> getPositionX()) <= 200
                    && bomber.getPositionX() - currentKorat[i][j] -> getPositionX() >= -200
                    && bomber.getLane() - currentKorat[i][j] -> getLane() <= 100
                    && bomber.getLane() - currentKorat[i][j] -> getLane() >= -100 )
                {
                    currentKorat[i][j] -> wasShot(200);
                }
                if (majorTom -> getTomPosition() - currentKorat[i][j] -> getLane() <= 100 &&
                    majorTom -> getTomPosition() - currentKorat[i][j] -> getLane() >= - 100 &&
                    majorTom -> getTomPositionX() - currentKorat[i][j] -> getPositionX() <= 200 &&
                    majorTom -> getTomPositionX() - currentKorat[i][j] -> getPositionX() >= -200)
                {
                    majorTom -> setHealth(majorTom->getHealth() - 50);
                }
            }

    }
}

void GameLogic::drawKorat(sf::RenderWindow& window)
{
    for (int i = 0; i < currentKorat.size(); i ++)
    {
        for (int j = 0; j < currentKorat[i].size(); j++)
        {
                currentKorat[i][j] -> drawCurrentKorat(window);
        }
    }
    for (int i = 0; i < dyingKorat.size(); i++)
    {
        dyingKorat[i] -> drawCurrentKorat(window);
    }
}

void GameLogic::selectKorat()
{
    koratSpawnLane = decideKoratLane();

    /*
        checks what level the player is on and
        decides what pool of types to randomly
        pick from excluding levels 10 and 20
        because they are boss levels
    */
    if(currentLevel < 3)
        koratSpawnType = decideKoratType(enemyPool1);
    else if(currentLevel >= 3 && currentLevel < 6)
        koratSpawnType = decideKoratType(enemyPool2);
    else if(currentLevel >= 6 && currentLevel < 9)
        koratSpawnType = decideKoratType(enemyPool3);
    else if(currentLevel == 9)
        koratSpawnType = decideKoratType(enemyPool4);
    else if(currentLevel == 11)
        koratSpawnType = decideKoratType(enemyPool5);
    else if(currentLevel >= 12 && currentLevel < 15)
        koratSpawnType = decideKoratType(enemyPool6);
    else if(currentLevel >= 15 && currentLevel < 20)
        koratSpawnType = decideKoratType(enemyPool7);
    spawnKorat();
}

void GameLogic::spawnKorat()
{
    KoratEmpire* newKorat;
    bool print;

    switch(koratSpawnType)
    {
        case 1:
            newKorat = new Grunt(koratSpawnLane, loadedTextures);
            break;
        case 2:
            newKorat = new Jackal(koratSpawnLane, loadedTextures);
            break;
        case 3:
            newKorat = new Elite(koratSpawnLane, loadedTextures);
            break;
        case 4:
            newKorat = new Hunter(koratSpawnLane, loadedTextures);
            break;
        case 5:
            newKorat = new Brute(koratSpawnLane, loadedTextures);
            break;
        case 6:
            newKorat = new Bomber(koratSpawnLane, loadedTextures);
            break;
        case 7:
            newKorat = new Biker(koratSpawnLane, loadedTextures);
            break;
        default:
            newKorat = new Grunt(koratSpawnLane, loadedTextures);
            std::cout << "Break Case Activated" << std::endl;
            break;

    }
    currentKorat[koratSpawnLane - 1].emplace_back(newKorat);
    currentKoratCount++;
    //std::cout << "currentKoratCount = " << currentKoratCount << std::endl;

    //std::cout << "==============================" << std::endl;
    for (int i = 0; i < currentKorat.size(); i ++)
    {

        for (int j = 0; j < currentKorat[i].size(); j++)
        {
            //cout << currentKorat[i][j] -> getName() << ' ';
            if (currentKorat[i][j] -> getLane() == 680)
            {
                 print = false;
            }
            else
                 print = true;

        }
        //if(print == true)
        //cout << endl << "------------------------------" << endl;
        //else
            //cout << endl;
    }
   // cout << "==============================" << endl;
}

int GameLogic::decideKoratLane()
{

    double lane = Random() * 5;
    if (lane >= 0 && lane <= 1)
        lane = 1;
    else if (lane > 1 && lane <= 2)
        lane = 2;
    else if (lane > 2 && lane <= 3)
        lane = 3;
    else if (lane > 3 && lane <= 4)
        lane = 4;
    else
        lane = 5;

    lane = (int) lane;
    return lane;
}

int GameLogic::decideKoratType(std::vector<int> enemyPool)
{
    double enemyType = Random() * enemyPool.size();
    enemyType = (int) enemyType;
    return enemyPool[enemyType];
}

//----------------------------------------------------------
//Bullets generation and drawing

void GameLogic::updateBulletOrder()
{
    for (int i = 0; i < currentBullet.size(); i ++)
        {
            for (int j = 0; j < currentBullet[i].size(); j++)
            {
                if (j - 1 >= 0)
                {
                    if(currentBullet[i][j] -> getPositionX() < currentBullet[i][j-1] -> getPositionX())
                    {
                        currentBullet[i][j].swap(currentBullet[i][j-1]);
                    }
                }
            }
        }
}

void GameLogic::fireBullet(MajorTom* majorTom, Gun* currentGun, float timePassed)
{
    lastBulletFired = fireBulletClock.getElapsedTime().asSeconds();

    if((lastBulletFired > currentGun -> getFireRate()) &&
       (currentGun -> getShotsFired() != currentGun -> getClipSize()))
    {
           currentGun -> shotsFiredPlusOne();
           selectBullet(majorTom, currentGun, timePassed);
           fireBulletClock.restart();
    }
    else if(currentGun -> getShotsFired() == currentGun -> getClipSize())
    {
        if (reloadCurrentGun(currentGun) == true)
        {
                currentGun -> shotsFiredPlusOne();
                selectBullet(majorTom, currentGun, timePassed);
                fireBulletClock.restart();
        }
    }

}

/** \brief
 * Reload function to calculate reload times.
 * \param Pointer to current gun to find reload times
 * \return Bool
 *
 */
bool GameLogic::reloadCurrentGun(Gun* currentGun)//needs to communicate to gameview to visualize reload time
{
    if(reloadStarted == false)
    {
        reloadClock.restart();
        reloadTime = reloadClock.getElapsedTime().asSeconds();
        reloadStarted = true;
    }
    if(reloadTime > currentGun -> getReloadSpeed() && reloadStarted == true)
    {
        currentGun -> resetShotsFired();
        reloadClock.restart();
        reloadStarted = false;
        return true;

    }
    else
    {
        reloadTime = reloadClock.getElapsedTime().asSeconds();
        if(reloadTime > currentGun -> getReloadSpeed() && reloadStarted == true)
        {
            currentGun -> resetShotsFired();
            reloadClock.restart();
            reloadStarted = false;
            return true;
        }
        cout << reloadTime << endl;//this is a scaler for the reload visual
        return false;
    }
}

void GameLogic::moveBullet(float timePassed)
{
    if(currentLevel != 10 && currentLevel != 20)
    {
        for (int i = 0; i < currentBullet.size(); i ++)
        {
            for (int j = 0; j < currentBullet[i].size(); j++)
            {
                if (currentKorat[i].size() >= 3)
                {
                    if(currentBullet[i][j] -> getBullet().getGlobalBounds().intersects(currentKorat[i][0] -> getKorat().getGlobalBounds()))
                    {
                        if(currentBullet[i][j] -> getBullet().getPosition().x > currentKorat[i][0] -> getKorat().getPosition().x)
                        {
                            currentKorat[i][0] -> wasShot(currentBullet[i][j] -> getDamage());
                            currentBullet[i].erase(currentBullet[i].begin() + j);
                        }
                        else
                        {
                            bulletLeftScreen(timePassed, i, j);
                        }
                    }
                    else if(currentBullet[i][j] -> getBullet().getGlobalBounds().intersects(currentKorat[i][1] -> getKorat().getGlobalBounds()))
                    {
                        if(currentBullet[i][j] -> getBullet().getPosition().x > currentKorat[i][1] -> getKorat().getPosition().x)
                        {
                            currentKorat[i][1] -> wasShot(currentBullet[i][j] -> getDamage());
                            currentBullet[i].erase(currentBullet[i].begin() + j);
                        }
                        else
                        {
                            bulletLeftScreen(timePassed, i, j);
                        }
                    }
                    else if(currentBullet[i][j] -> getBullet().getGlobalBounds().intersects(currentKorat[i][2] -> getKorat().getGlobalBounds()))
                    {
                        if(currentBullet[i][j] -> getBullet().getPosition().x > currentKorat[i][2] -> getKorat().getPosition().x)
                        {
                            currentKorat[i][2] -> wasShot(currentBullet[i][j] -> getDamage());
                            currentBullet[i].erase(currentBullet[i].begin() + j);
                        }
                        else
                        {
                            bulletLeftScreen(timePassed, i, j);
                        }
                    }
                    else
                    {
                        bulletLeftScreen(timePassed, i, j);
                    }
                }
                else if (currentKorat[i].size() == 2)
                {
                    if(currentBullet[i][j] -> getBullet().getGlobalBounds().intersects(currentKorat[i][0] -> getKorat().getGlobalBounds()))
                    {
                        if(currentBullet[i][j] -> getBullet().getPosition().x > currentKorat[i][0] -> getKorat().getPosition().x)
                        {
                            currentKorat[i][0] -> wasShot(currentBullet[i][j] -> getDamage());
                            currentBullet[i].erase(currentBullet[i].begin() + j);
                        }
                        else
                        {
                            bulletLeftScreen(timePassed, i, j);
                        }
                    }
                    else if(currentBullet[i][j] -> getBullet().getGlobalBounds().intersects(currentKorat[i][1] -> getKorat().getGlobalBounds()))
                    {
                        if(currentBullet[i][j] -> getBullet().getPosition().x > currentKorat[i][1] -> getKorat().getPosition().x)
                        {
                            currentKorat[i][1] -> wasShot(currentBullet[i][j] -> getDamage());
                            currentBullet[i].erase(currentBullet[i].begin() + j);
                        }
                        else
                        {
                            bulletLeftScreen(timePassed, i, j);
                        }
                    }
                    else
                    {
                        bulletLeftScreen(timePassed, i, j);
                    }
                }
                else if (currentKorat[i].size() == 1)
                {
                    if(currentBullet[i][j] -> getBullet().getGlobalBounds().intersects(currentKorat[i][0] -> getKorat().getGlobalBounds()))
                    {
                        if(currentBullet[i][j] -> getBullet().getPosition().x > currentKorat[i][0] -> getKorat().getPosition().x)
                        {
                            currentKorat[i][0] -> wasShot(currentBullet[i][j] -> getDamage());
                            currentBullet[i].erase(currentBullet[i].begin() + j);
                        }
                        else
                        {
                            bulletLeftScreen(timePassed, i, j);
                        }
                    }
                    else
                    {
                        bulletLeftScreen(timePassed, i, j);
                    }
                }
                else //check and see if the bullet is out of bounds
                {
                    bulletLeftScreen(timePassed, i, j);
                }
            }
        }
    }
    //on level 10 first boss checks for intersection with the boss, instead of using old collision
    //plug in sfml collision with rects
    else if (currentLevel == 10)
    {
        for (int i = 0; i < currentBullet.size(); i++)
        {
            for (int j = 0; j < currentBullet[i].size(); j++)
            {
                for (int z = 0; z < currentBikeBoss.size(); z++)
                {
                    if(currentBullet[i][j] -> getBullet().getGlobalBounds().intersects(currentBikeBoss[z] -> getBoss().getGlobalBounds()))
                    {
                        if(currentBullet[i][j] -> getBullet().getPosition().x > currentBikeBoss[z] -> getBoss().getPosition().x - 50)
                        {
                            currentBikeBoss[z] -> wasShot(currentBullet[i][j] -> getDamage());
                            currentBullet[i].erase(currentBullet[i].begin() + j);
                        }
                        else
                        {
                            bulletLeftScreen(timePassed, i, j);
                        }
                    }
                    else
                    {
                        bulletLeftScreen(timePassed, i, j);
                    }
                }
                if(currentBikeBoss.size() == 0)
                {
                    bulletLeftScreen(timePassed, i, j);
                }
            }
        }
    }
    else if (currentLevel == 20)
    {
        for (int i = 0; i < currentBullet.size(); i++)
        {
            for (int j = 0; j < currentBullet[i].size(); j++)
            {
                for (int z = 0; z < currentTankBoss.size(); z++)
                {
                    if(currentBullet[i][j] -> getBullet().getGlobalBounds().intersects(currentTankBoss[z] -> getBoss().getGlobalBounds()))
                    {
                        if(currentBullet[i][j] -> getBullet().getPosition().x > (currentTankBoss[z] -> getBoss().getPosition().x))
                        {
                        currentTankBoss[z] -> wasShot(currentBullet[i][j] -> getDamage());
                        currentBullet[i].erase(currentBullet[i].begin() + j);
                        }
                        else
                        {
                            bulletLeftScreen(timePassed, i, j);
                        }
                    }
                    else
                    {
                        bulletLeftScreen(timePassed, i, j);
                    }
                }
                if(currentTankBoss.size() == 0)
                {
                    bulletLeftScreen(timePassed, i, j);
                }
            }
        }
    }
}

void GameLogic::bulletLeftScreen(float timePassed, int i, int j)
{
    if (currentBullet[i][j] -> getOutOfBounds() == false)
    {
        currentBullet[i][j] -> moveCurrentBullet(timePassed);
    }
    else
    {
        currentBullet[i].erase(currentBullet[i].begin() + j);
    }
}

void GameLogic::moveKoratBullet(float timePassed, MajorTom* majorTom)
{
	//! KORAT BULLETS
	for (int i = 0; i < currentKoratBullet.size(); i ++)
	{
		for (int j = 0; j < currentKoratBullet[i].size(); j++)
		{
			if (currentKoratBullet[i][j] -> getBullet().getGlobalBounds().intersects(majorTom -> getTom().getGlobalBounds()))
			{
			    if(currentKoratBullet[i][j] -> getBullet().getPosition().x < majorTom -> getTomPositionX())
                {
                    majorTom -> wasShot(currentKoratBullet[i][j] -> getDamage());
                    currentKoratBullet[i].erase(currentKoratBullet[i].begin() + j);
                }
                else
                {
                    currentKoratBullet[i][j] -> moveCurrentBullet(timePassed);
                }
			}
			else
            {
				if (currentKoratBullet[i][j] -> getOutOfBounds() == false)
				{
					currentKoratBullet[i][j] -> moveCurrentBullet(timePassed);
				}
				else
				{
					currentKoratBullet[i].erase(currentKoratBullet[i].begin() + j);
				}
			}
		}
	}
}

void GameLogic::drawBullet(sf::RenderWindow& window)
{
    for (int i = 0; i < currentBullet.size(); i ++)
    {
        for (int j = 0; j < currentBullet[i].size(); j++)
        {
                currentBullet[i][j] -> drawCurrentBullet(window);

        }
    }

    for (int i = 0; i < currentKoratBullet.size(); i ++)
	{
		for (int j = 0; j < currentKoratBullet[i].size(); j++)
		{
				currentKoratBullet[i][j] -> drawCurrentBullet(window);

		}
	}
}

void GameLogic::selectBullet(MajorTom* majorTom, Gun* currentGun, float timePassed)
{
    bulletSpawnLane = decideBulletLane(majorTom);

    bulletSpawnType = decideBulletType(currentGun);

    spawnBullet(timePassed);
}

void GameLogic::spawnBullet(float timePassed)
{
    Bullet* newBullet1 = 0;
    Bullet* newBullet2 = 0;
    Bullet* newBullet3 = 0;

    switch(bulletSpawnType)
    {
        case 1:
            newBullet1 = new PlasmaPistolBullet(bulletSpawnLane, loadedTextures);
            break;
        case 2:
            newBullet1 = new PlasmaShotgunBullet(bulletSpawnLane, loadedTextures);
            newBullet2 = new PlasmaShotgunBullet(bulletSpawnLane - 1, loadedTextures);
            newBullet3 = new PlasmaShotgunBullet(bulletSpawnLane + 1, loadedTextures);
            break;
        case 3:
            newBullet1 = new LaserRifleBullet(bulletSpawnLane, loadedTextures);
            break;
        case 4:
            newBullet1 = new LaserMinigunBullet(bulletSpawnLane, loadedTextures);
            break;
        case 5:
            newBullet1 = new ArcBullet(bulletSpawnLane, loadedTextures);
            newBullet2 = new ArcBullet(bulletSpawnLane - 1, loadedTextures);
            newBullet3 = new ArcBullet(bulletSpawnLane + 1, loadedTextures);
            break;
        case 6:
            newBullet1 = new GaussBullet (bulletSpawnLane, loadedTextures);
            break;
        case 7:
            newBullet1 = new BFGBullet (bulletSpawnLane, loadedTextures);
            break;
        default:
            newBullet1 = new PlasmaPistolBullet(bulletSpawnLane, loadedTextures);
            cout << "Break Case Activated" << endl;
            break;

    }
    currentBullet[bulletSpawnLane - 1].emplace_back(newBullet1);
    if (bulletSpawnType == 2 || bulletSpawnType == 5)
    {
        if (bulletSpawnLane != 1)
        {
            currentBullet[bulletSpawnLane - 2].emplace_back(newBullet2);
        }
        else
        {
            delete newBullet2;
        }

        if (bulletSpawnLane != 5)
        {
            currentBullet[bulletSpawnLane].emplace_back(newBullet3);
        }
        else
        {
            delete newBullet3;
        }
    }
    else
    {
        delete newBullet2;
        delete newBullet3;
    }
}

int GameLogic::decideBulletLane(MajorTom* majorTom)
{
    if (majorTom->getTomPosition() == lane1)
        return 1;
    else if (majorTom->getTomPosition() == lane2)
        return 2;
    else if (majorTom->getTomPosition() == lane3)
        return 3;
    else if (majorTom->getTomPosition() == lane4)
        return 4;
    else if (majorTom->getTomPosition() == lane5)
        return 5;
    else
        cout << "bullet shit is broken" << endl;
}

int GameLogic::decideBulletLaneKorat(int givenLane)
{
    if (givenLane == lane1)
        return 1;
    else if (givenLane == lane2)
        return 2;
    else if (givenLane == lane3)
        return 3;
    else if (givenLane == lane4)
        return 4;
    else if (givenLane == lane5)
        return 5;
    else
        cout << "bullet shit is broken 2" << endl;
}

int GameLogic::decideBulletType(Gun* currentGun)
{
    return currentGun -> getBulletType();
}


//----------------------------------------------------------

void GameLogic::runLevel(sf::CircleShape& gameSky, MajorTom* majorTom, float timePassed)
{
    if(!isPaused)
    {
        rotation = gameSky.getRotation();
        spawnTime = spawnClock.getElapsedTime().asSeconds();

        long now;
        now = ((unsigned long) time((time_t *) NULL)) % 255;
        SelectStream((int) now);

        //-------------------------------------------------------------
        // lose game check
        if (checkEnd(majorTom))
        {
            loseLevel(gameSky, majorTom);
        }

        //-------------------------------------------------------------

        if (rotation >= sunSetOrientation) // if the sun has set
        {
            if (currentKoratCount == 0)
            {
                gameSky.rotate(-rotation); //rotate the sun back to the beginning
                currentLevel++;
                survivorCountSaved = majorTom->getSurvivors();
                cout << "Survivor Count Saved: " << survivorCountSaved << endl;
                levelSpeedModifier = levelSpeedModifier * 15/16; //cut the speed of the sun down by 15/16ths
                levelSpawnModifier = levelSpawnModifier * 15/16; //

                majorTom ->  setTomPositionX(156);

                majorTom -> setTomPositionY(508);

                cout << "Current Level = " << currentLevel << endl;
                levelWon = true;
                // start text adventure

                clearAssets();

                if(currentLevel == 10)
                {
                    startBikeBoss(loadedTextures);
                }

                if(currentLevel == 20)
                {
                    startTankBoss(loadedTextures);
                }

            }
        }
        else if(currentLevel == 10 | currentLevel == 20)
        {
            gameSky.rotate(timePassed * levelSpeedModifier);
            levelWon = false;
        }
        else
        {
            levelWon = false;
            gameSky.rotate(timePassed * levelSpeedModifier);

            if (spawnTime >= levelSpawnModifier)
            {
                selectKorat();
                spawnClock.restart();
            }
        }
    }
}

void GameLogic::clearAssets()
{
    for (int i = 0; i < currentBullet.size(); i++)
    {
        currentBullet[i].clear();
    }
    for (int i = 0; i < currentKorat.size(); i++)
    {
        currentKorat[i].clear();
    }
    for (int i = 0; i < currentKoratBullet.size(); i++)
    {
        currentKoratBullet[i].clear();
    }
    currentBikeBoss.clear();
    currentTankBoss.clear();
}

void GameLogic::loseLevel(sf::CircleShape& gameSky, MajorTom* majorTom)
{
    clearAssets();

    majorTom -> setTomPositionX(156);

    majorTom -> setTomPositionY(508);

    currentKoratCount = 0;

    gameSky.rotate(-rotation); //rotate the sun back to the beginning

    std::cout << "Current Level = " << currentLevel << std::endl;

    if(currentLevel == 10)
    {
        startBikeBoss(loadedTextures);
    }

    if(currentLevel == 20)
    {
        startTankBoss(loadedTextures);
    }
    cout << "Suvivor Count Saved: " << survivorCountSaved << endl;
    majorTom->setSurvivors(survivorCountSaved);
    majorTom->setHealth(100);

}

void GameLogic::startBikeBoss(TextureLoader* loadedTextures)
{
    BikeBoss* bikeBoss = new BikeBoss(loadedTextures);
    currentBikeBoss.emplace_back(bikeBoss);
    currentKoratCount = 1;
}

void GameLogic::drawBikeBoss(sf::RenderWindow& window)
{
    for(int i = 0; i < currentBikeBoss.size(); i++)
    {
        currentBikeBoss[i] -> drawBoss(window);
    }
    for(int j = 0; j < dyingBikeBoss.size(); j++)
    {
        dyingBikeBoss[j] -> drawBoss(window);
    }
}

void GameLogic::updateDyingBikeBoss()
{
    for (int i = 0; i < dyingBikeBoss.size(); i++)
    {
        if (dyingBikeBoss[i] -> checkDeath() == true)
        {
            dyingBikeBoss.erase(dyingBikeBoss.begin() + i);
            currentKoratCount--;

        }
    }
}

void GameLogic::moveBikeBoss(sf::CircleShape& gameSky, MajorTom* majorTom, float timePassed)
{
    for(int i = 0; i < currentBikeBoss.size(); i++)
    {
        if(currentBikeBoss[i] -> getBoss().getGlobalBounds().intersects(majorTom -> getTom().getGlobalBounds()))
        {
            majorTom -> setHealth(0);
        }
        if (currentBikeBoss[i] -> checkSurvive() == false)
        {
            if (currentBikeBoss[i] -> checkDeath() == false)
            {
                if (currentBikeBoss[i] -> getSpeed() == 0)
                {
                        dyingBikeBoss.emplace_back(move(currentBikeBoss[i]));
                        currentBikeBoss.erase(currentBikeBoss.begin() + i);
                        movingUp = false;
                        movingDown = false;
                        directMove = 1;
                }
                else if (movingUp == false && movingDown == false)
                {
                    if (directMove < 1998)
                    {
                        directMove = Random() * 2000;
                        currentBikeBoss[i] -> moveBoss(timePassed);
                    }
                    else if (directMove >= 1998 && directMove < 1999)
                    {
                        directMove = Random() * 2000;
                        currentBikeBoss[i] -> initBossUp();
                        movingUp = true;
                        movingDown = false;
                    }
                    else if (directMove >= 1999)
                    {
                        directMove = Random() * 2000;
                        currentBikeBoss[i] -> initBossDown();
                        movingUp = false;
                        movingDown = true;
                    }
                }
                else if(movingUp == true)
                {
                    if (currentBikeBoss[i] -> moveBossUp(timePassed) == true)
                    {
                        movingUp = false;
                        movingDown = false;
                    }
                    currentBikeBoss[i] -> moveBoss(timePassed);
                }
                else if(movingDown == true)
                {
                    if (currentBikeBoss[i] -> moveBossDown(timePassed) == true)
                    {
                        movingUp = false;
                        movingDown = false;
                    }
                    currentBikeBoss[i] -> moveBoss(timePassed);
                }
            }
            else
            {
                // nothing happens will never trigger
            }
        }
        else
        {
            currentBikeBoss.erase(currentBikeBoss.begin() + i);
            currentKoratCount--;
            majorTom -> setHealth(0);
        }
    }
}


void GameLogic::startTankBoss(TextureLoader* loadedTextures)
{
    TankBoss* tankBoss = new TankBoss(loadedTextures);
    currentTankBoss.emplace_back(tankBoss);
    currentKoratCount = 1;
}

void GameLogic::drawTankBoss(sf::RenderWindow& window)
{
     for(int i = 0; i < currentTankBoss.size(); i++)
    {
        currentTankBoss[i] -> drawBoss(window);
    }
    for(int j = 0; j < dyingTankBoss.size(); j++)
    {
        dyingTankBoss[j] -> drawBoss(window);
    }
}

void GameLogic::updateDyingTankBoss()
{
    for (int i = 0; i < dyingTankBoss.size(); i++)
    {
        if (dyingTankBoss[i] -> checkDeath() == true)
        {
            dyingTankBoss.erase(dyingTankBoss.begin() + i);
            currentKoratCount--;

        }
    }
}

void GameLogic::moveTankBoss(sf::CircleShape& gameSky, MajorTom* majorTom, float timePassed)
{
    for(int i = 0; i < currentTankBoss.size(); i++)
    {
        if (currentTankBoss[i] -> checkSurvive() == false)
        {
            if (currentTankBoss[i] -> checkDeath() == false)
            {
                if (currentTankBoss[i] -> getSpeed() == 0)
                {
                        dyingTankBoss.emplace_back(move(currentTankBoss[i]));
                        currentTankBoss.erase(currentTankBoss.begin() + i);
                }
                else
                {
                    currentTankBoss[i] -> moveBoss(timePassed);
                    if(currentTankBoss[i] -> getBoss().getGlobalBounds().intersects(majorTom -> getTom().getGlobalBounds()))
                    {
                        majorTom -> setHealth(0);
                    }
                }
            }
            else
            {
                // nothing happens will never trigger
            }
        }
        else
        {
            currentBikeBoss.erase(currentBikeBoss.begin() + i);
            currentKoratCount--;
            majorTom -> setHealth(0);
        }
    }
}

int GameLogic::getLevel()
{
    return currentLevel;
}


void GameLogic::queryKoratFiring()
{
    if(!isPaused)
    {
        for (int i = 0; i < currentKorat.size(); i ++)
        {
            for (int j = 0; j < currentKorat[i].size(); j++)
            {

                if (currentKorat[i][j] -> getName() == "Jackal" or currentKorat[i][j] -> getName() == "Elite" or currentKorat[i][j] -> getName() == "Brute" or currentKorat[i][j] -> getName() == "Biker" or currentKorat[i][j] -> getName() == "Hunter")
                {
                    if (currentKorat[i][j] -> queryToFire() == true) //if the Korat is ready to Fire
                    {
                        //implement stuff to make Korat fire here
                        Bullet* newBullet;
                        newBullet = new KoratBullet(currentKorat[i][j] -> getLane(), currentKorat[i][j] -> getPositionX(), loadedTextures);

                        int laneToGoIn = decideBulletLaneKorat(currentKorat[i][j] -> getLane());
                        currentKoratBullet[laneToGoIn - 1].emplace_back(newBullet);
                    } else {
                        //pass? basically ask again later
                    }
                }
            }
        }
    }
}

void GameLogic::pauseGame()
{
    isPaused = !isPaused;
}

void GameLogic::queryBikeFiring()
{
cout << "Shots Fired = "<< counter << endl;
	for (int i = 0; i < currentBikeBoss.size(); i ++)
	{
        if (currentBikeBoss[i] -> getPositionX() < 1440)
        {
            if (currentBikeBoss[i] -> queryToFire() == true) //if the Korat is ready to Fire
            {
                if( movingDown == false && movingUp == false)
                {
                    double bikerGun = Random() * 4;
                    int firingLaneInPixels;

                    if (bikerGun < 2)
                    {
                        Bullet* newBullet1;
                        firingLaneInPixels = currentBikeBoss[i] -> getBossPosition() - 86;
                        newBullet1 = new KoratBullet(firingLaneInPixels, currentBikeBoss[i] -> getPositionX() - 50, loadedTextures);

                        int laneToGoIn;
                        switch(firingLaneInPixels)
                        {
                        case 336:
                            laneToGoIn = 0;
                            break;
                        case 422:
                            laneToGoIn = 1;
                            break;
                        case 508:
                            laneToGoIn = 2;
                            break;
                        case 594:
                            laneToGoIn = 3;
                            break;
                        case 680:
                            laneToGoIn = 4;
                            break;
                        default:
                            laneToGoIn = 0;
                            break;
                        }
                        currentKoratBullet[laneToGoIn].emplace_back(newBullet1);
                    }
                    else if(bikerGun >= 2 && bikerGun < 3)
                    {
                        Bullet* newBullet2;
                        firingLaneInPixels = currentBikeBoss[i] -> getBossPosition();
                        newBullet2 = new KoratBullet(firingLaneInPixels, currentBikeBoss[i] -> getPositionX() - 50, loadedTextures);

                        int laneToGoIn;
                        switch(firingLaneInPixels)
                        {
                        case 336:
                            laneToGoIn = 0;
                            break;
                        case 422:
                            laneToGoIn = 1;
                            break;
                        case 508:
                            laneToGoIn = 2;
                            break;
                        case 594:
                            laneToGoIn = 3;
                            break;
                        case 680:
                            laneToGoIn = 4;
                            break;
                        default:
                            laneToGoIn = 0;
                            break;
                        }
                        currentKoratBullet[laneToGoIn].emplace_back(newBullet2);
                    }
                    else
                    {
                        Bullet* newBullet3;
                        firingLaneInPixels = currentBikeBoss[i] -> getBossPosition() + 86;
                        newBullet3 = new KoratBullet(firingLaneInPixels, currentBikeBoss[i] -> getPositionX() - 50, loadedTextures);

                        int laneToGoIn;
                        switch(firingLaneInPixels)
                        {
                        case 336:
                            laneToGoIn = 0;
                            break;
                        case 422:
                            laneToGoIn = 1;
                            break;
                        case 508:
                            laneToGoIn = 2;
                            break;
                        case 594:
                            laneToGoIn = 3;
                            break;
                        case 680:
                            laneToGoIn = 4;
                            break;
                        default:
                            laneToGoIn = 0;
                            break;
                        }
                        currentKoratBullet[laneToGoIn].emplace_back(newBullet3);
                    }
                }
            }
        }
	}
}


void GameLogic::queryTankFiring()
{
	cout << "Shots Fired = "<< counter << endl;
	for (int i = 0; i < currentTankBoss.size(); i ++)
	{
        if (currentTankBoss[i] -> getPositionX() < 1440)
        {
            if (currentTankBoss[i] -> queryToFire() == true) //if the Korat is ready to Fire
            {
                int firingLaneInPixels = currentTankBoss[i] -> decideFiringLane();
                //implement stuff to make Korat fire here
                Bullet* newBullet;
                newBullet = new KoratBullet(firingLaneInPixels, currentTankBoss[i] -> getPositionX(), loadedTextures);

                int laneToGoIn;

                switch(firingLaneInPixels)
                {
                case 335:
                    laneToGoIn = 0;
                    break;
                case 422:
                    laneToGoIn = 1;
                    break;
                case 508:
                    laneToGoIn = 2;
                    break;
                case 594:
                    laneToGoIn = 3;
                    break;
                case 680:
                    laneToGoIn = 4;
                    break;
                default:
                    laneToGoIn = 0;
                    break;
                }
                cout << firingLaneInPixels << endl;


                currentKoratBullet[laneToGoIn].emplace_back(newBullet);

                counter++;

                //405 count
            }

        }
	}
}
