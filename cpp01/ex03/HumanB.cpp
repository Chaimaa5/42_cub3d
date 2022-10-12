#include "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name)
{
    std::cout << "HumanB Parametrize Constructor called\n";
}

HumanB::HumanB()
{
    std::cout << "HumanB Constructor called\n";
}

HumanB::~HumanB()
{
    std::cout << "HumanB Destructor called\n";
}

void    HumanB::attack()
{
    if (weapon)
        std::cout << name << " attacks with their" << weapon->getType() << std::endl;
    else
        std::cout << name << " Do not have a Weapon to attack" << std::endl;
}


void    HumanB::setWeapon(Weapon &weapon)
{
        this->weapon = &weapon;
}