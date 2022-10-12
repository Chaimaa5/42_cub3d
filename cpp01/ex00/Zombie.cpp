#include "Zombie.hpp"
 Zombie::Zombie(){std::cout << "zombie constructed\n";}

Zombie::~Zombie()
{
    std::cout << "zombie destructed\n";
}

void    Zombie::setname(std::string nam)
{
    name = nam;
}

std::string    Zombie::getname()
{
    return (name);
}