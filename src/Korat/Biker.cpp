
#include "Biker.h"
#include <iostream>

Biker::Biker(int startLane){
    if(!gruntPlasma.loadFromFile("assets/plasmaGrunt.png"))
        std::cout << "Failed to load plasmaGrunt." << std::endl;
    lane = 0;
	biker.setSize(sf::Vector2f(64,64));
	biker.setTexture(&gruntPlasma);
	biker.setOrigin(biker.getSize().x / 2, biker.getSize().y /2);
	setLane(startLane);
	biker.setPosition(1500, lane);
	std::cout << "I'm a biker" << std::endl;
}

Biker::~Biker() {
	// TODO Auto-generated destructor stub

}

void Biker::wasShot(int damage)
{
    health = health - damage;
}

int Biker::getLane()
{
    return lane;
}

void Biker::setLane(int givenLane)
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

void Biker::moveCurrentKorat(float timePassed)
{
        if(biker.getPosition().x > -100)
        {
            biker.move(-speed * timePassed, 0);
        }
        else
        {
            health = 0;
        }
}

void Biker::drawCurrentKorat(sf::RenderWindow& window)
{
    window.draw(biker);
}

sf::RectangleShape Biker::getKorat()
{
    return biker;
}

float Biker::getPositionX()
{
    return biker.getPosition().x;
}

bool Biker::checkDeath()
{
    if (health <= 0)
        return true;
    return false;
}
