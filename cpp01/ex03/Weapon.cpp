#include "HumanB.hpp"

Weapon::Weapon()
{
    std::cout << "Weapon Constructor called\n";
}

Weapon::~Weapon()
{
    std::cout << "Weapon Destructor called\n";
}

Weapon::Weapon(std::string type) : type(type)
{
    std::cout << "Weapon Parametrize Constructor called\n";
}

void    Weapon::setType(std::string type)
{
    this->type = type;
}

std::string Weapon::getType()
{
    return (type);
}