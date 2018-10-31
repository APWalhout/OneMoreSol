
#include "Hunter.h"
#include <iostream>

Hunter::Hunter(int startLane, TextureLoader* loadedTextures){
    lane = 0;

	hunter.setTexture(loadedTextures->mtSpriteSheet);
	hunter.setTextureRect(sf::IntRect(0,640,64,64));
	hunter.setOrigin(sf::Vector2f(32.f,32.f));
	setLane(startLane);
	hunter.setPosition(1500, lane);
}

Hunter::~Hunter() {
	// TODO Auto-generated destructor stub

}

void Hunter::wasShot(int damage)
{
    health = health - damage;
}

int Hunter::getLane()
{
    return lane;
}

std::string Hunter::getName()
{
    return "Hunter";
}

void Hunter::setLane(int givenLane)
{
     switch(givenLane)
	{
		case 1:
			lane = lane1;
			break;
		case 2:
			lane = lane2;
			break;
		case 3:
			lane = lane3;
			break;
		case 4:
			lane = lane4;
			break;
		case 5:
			lane = lane5;
			break;
		default:
			lane = lane1;
			break;
	}
}

void Hunter::moveCurrentKorat(float timePassed)
{
        if(hunter.getPosition().x > -100)
        {
            hunter.move(-speed * timePassed, 0);
        }
        else
        {
            survive = true;
        }
}

void Hunter::drawCurrentKorat(sf::RenderWindow& window)
{
    window.draw(hunter);
}

sf::Sprite Hunter::getKorat()
{
    return hunter;
}

float Hunter::getPositionX()
{
    return hunter.getPosition().x;
}

bool Hunter::checkDeath()
{
    if (health <= 0)
    {
		postDeathTime = postDeathClock.getElapsedTime().asSeconds();
		if (postDeathTime >= .5)
		{
			postDeathClock.restart();
			return true;
		}
		else
        {
			speed = 0;
			if (koratDeathSoundPlayed == false)
			{
				postDeathClock.restart();
				koratDied.setBuffer(koratDeathSound);
				koratDied.setVolume(100);
				koratDied.play();
				koratDeathSoundPlayed = true;
			}
		}
    }
    else
    {
        postDeathClock.restart();
        return false;

    }
}

bool Hunter::checkSurvive()
{
    return survive;
}