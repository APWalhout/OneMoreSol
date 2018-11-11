/*
 * KoratBullet.cpp
 *
 *  Created on: Nov 10, 2018
 *      Author: Bowden
 */


#include "KoratBullet.h"
#include <iostream>

using namespace std;

KoratBullet::KoratBullet(int givenLane, int givenHeight, TextureLoader* loadedTextures) {
    plasma.setTexture(loadedTextures->textureArray[0]);
    cout << "stage 1" << endl;
    plasma.setTextureRect(sf::IntRect(256,64,32,32));
    cout << "stage 2" << endl;
	plasma.setOrigin(sf::Vector2f(16.f,16.f));
	cout << "stage 3" << endl;
	setLane(givenLane, givenHeight);
	cout << "lane = " << lane << endl;
	cout << "stage 4" << endl;
	plasma.setPosition(height, lane);
	cout << "stage 5" << endl;
	speed = 500;
	damage = 35;

	if (!plasmaPistolSound.loadFromFile("assets/Plasma_Pistol_Sound.ogg")) // Loads and initializes all sounds based on impact
    std::cout << "Could not load Plasma Pistol Sound." << std::endl;

    firePlasmaPistol.setBuffer(plasmaPistolSound);
    firePlasmaPistol.setVolume(50);
    firePlasmaPistol.play();
}

KoratBullet::~KoratBullet() {
	// TODO Auto-generated destructor stub
}

int KoratBullet::getDamage()
{
    return damage;
}

int KoratBullet::getLane()
{
    return lane;
}

int KoratBullet::getHeight()
{
    return height;
}

float KoratBullet::getPositionX()
{
    return plasma.getPosition().x;
}

void KoratBullet::setLane(int givenLane, int givenHeight)
{
     switch(givenLane)
	{
		case 1:
			lane = lane1;
			if (givenHeight == -1)
			{
				height = height1;
			} else {
				height = givenHeight;
			}
			break;
		case 2:
			lane = lane2;
			height = height2;
			if (givenHeight == -1)
			{
				height = height2;
			} else {
				height = givenHeight;
			}
			break;
		case 3:
			lane = lane3;
			height = height3;
			if (givenHeight == -1)
			{
				height = height3;
			} else {
				height = givenHeight;
			}
			break;
		case 4:
			lane = lane4;
			height = height4;
			if (givenHeight == -1)
			{
				height = height4;
			} else {
				height = givenHeight;
			}
			break;
		case 5:
			lane = lane5;
			height = height5;
			if (givenHeight == -1)
			{
				height = height5;
			} else {
				height = givenHeight;
			}
			break;
		default:
			lane = lane1;
			height = height1;
			break;
	}
}

void KoratBullet::moveCurrentBullet(float timePassed)
{
        if(plasma.getPosition().x > -100)
        {
        	std::cout << "ABOUT TO MOVE BULLET" << std::endl;
            plasma.move(-speed * timePassed, 0);
            outOfBounds = false;
        }
        else
        {
            outOfBounds = true;
        }
}

void KoratBullet::drawCurrentBullet(sf::RenderWindow& window)
{
    window.draw(plasma);
}

bool KoratBullet::getOutOfBounds()
{
    return outOfBounds;
}

sf::Sprite KoratBullet::getBullet()
{
    return plasma;
}

