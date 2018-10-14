#ifndef GUN_H
#define GUN_H
#include<SFML/Graphics.hpp>

class Gun
{
public:
    Gun();
    virtual ~Gun();

    unsigned int damage;
    unsigned int clip;
    float reloadSpeed;
    std::string dmgMultiplier;
    float fireRate;
    sf::Image image;

};

#endif // GUN_H