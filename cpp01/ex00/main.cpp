#include "Zombie.hpp"

void Zombie::announce(void)
{
    std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}

int main()
{
    Zombie *zombie;

    randomChump("chump");
    zombie = newZombie("chuuuump");
    zombie->announce();
    delete(zombie);
}