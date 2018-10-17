// Chris Wolinski SFML Pong

#include "MajorTom.h"

using namespace std;

MajorTom::MajorTom()
{
    majorTom.setSize(sf::Vector2f(50,100));
    //majorTom.setTexture()
    majorTom.setOrigin(majorTom.getSize().x / 2, majorTom.getSize().y / 2);
    majorTom.setPosition(156,508);
    currentHealth = 100;
    //currentGun = PlasmaPistol;

}

void MajorTom::drawTom (sf::RenderWindow& window)
{
    window.draw(majorTom);
}

float MajorTom::getTomPosition()
{
    return majorTom.getPosition().y;
}

void MajorTom::setTomPosition(float positionPassed)
{
    majorTom.setPosition(majorTom.getPosition().x, positionPassed);
}

void MajorTom::moveTomUp(float timePassed)
{
    if (majorTom.getPosition().y > 334 && majorTom.getPosition().y < 346)
    {
        // Do not move up - top lane
    }
    else if (majorTom.getPosition().y > 421 && majorTom.getPosition().y < 423)
    {
        while(majorTom.getPosition().y > 335)
        {
            majorTom.move(timePassed * .05, timePassed * -.1);
        }
        setTomPosition(335);
    }
    else if (majorTom.getPosition().y > 507 && majorTom.getPosition().y < 509)
    {
        while(majorTom.getPosition().y > 422)
        {
            majorTom.move(timePassed * .05, timePassed * -.1);
        }
        setTomPosition(422);
    }
    else if (majorTom.getPosition().y > 593 && majorTom.getPosition().y < 595)
    {
        while(majorTom.getPosition().y > 508)
        {
            majorTom.move(timePassed * .05, timePassed * -.1);
        }
        setTomPosition(508);
    }
    else if (majorTom.getPosition().y > 679 && majorTom.getPosition().y < 681)
    {
        while(majorTom.getPosition().y > 594)
        {
            majorTom.move(timePassed * .05, timePassed * -.1);
        }
        setTomPosition(594);
    }
}

void MajorTom::moveTomDown(float timePassed)
{
    if (majorTom.getPosition().y > 334 && majorTom.getPosition().y < 336)
    {
        while(majorTom.getPosition().y < 422)
        {
            majorTom.move(timePassed * -.05, timePassed * .1);
        }
        setTomPosition(422);
    }
    else if (majorTom.getPosition().y > 421 && majorTom.getPosition().y < 423)
    {
        while(majorTom.getPosition().y < 508)
        {
            majorTom.move(timePassed * -.05, timePassed * .1);
        }
        setTomPosition(508);
    }
    else if (majorTom.getPosition().y > 507 && majorTom.getPosition().y < 509)
    {
        while(majorTom.getPosition().y < 594)
        {
            majorTom.move(timePassed * -.05, timePassed * .1);
        }
        setTomPosition(594);
    }
    else if (majorTom.getPosition().y > 593 && majorTom.getPosition().y < 595)
    {
        while(majorTom.getPosition().y < 680)
        {
            majorTom.move(timePassed * -.05, timePassed * .1);
        }
        setTomPosition(680);
    }
    else if (majorTom.getPosition().y > 679 && majorTom.getPosition().y < 681)
    {
        // Do not move down - bottom lane
    }
}


int MajorTom::getHealth()
{
    return currentHealth;
}

void MajorTom::setHealth(int newHealth)
{
    currentHealth = newHealth;
}

Gun MajorTom::getGun()
{
    return currentGun;
}

void MajorTom::setGun(Gun newGun)
{
    currentGun = newGun;
}

bool MajorTom::checkDeath()
{
    if (currentHealth <= 0)
        return true;
    return false;
}
/*
void MajorTom::updateGame(sf::RenderWindow& gameWindow) // Draws all elements of screen
{

    gameWindow.clear(sf::Color::Black);

    gameWindow.draw(sky);
    gameWindow.draw(background);
    majorTom.drawTom(gameWindow);
    gameWindow.draw(survivorCnt);
    gameWindow.draw(weapon1);
    gameWindow.draw(weapon2);
    gameWindow.draw(weapon3);
    gameWindow.draw(weapon4);
    gameWindow.draw(weapon5);
    gameWindow.draw(weapon6);
    gameWindow.draw(weapon7);

    gameWindow.display();
}
*/
