#include "Zombie.hpp"

void    randomChump(std::string name)
{
    Zombie zombie;

    zombie.setname(name);
    zombie.announce();
}