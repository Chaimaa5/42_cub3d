#include "Zombie.hpp"

Zombie  *newZombie(std::string name)
{

    Zombie *zombie = new Zombie();

    zombie->setname(name);
    return(zombie);
}