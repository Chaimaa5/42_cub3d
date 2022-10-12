#include "Zombie.hpp"

void Zombie::announce(void)
{
    std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}

int main()
{
    Zombie *zombie;

    zombie = zombieHorde(-1, "zombie");
    if (zombie)
    {
        for (int i = 0; i < 10; i++)
            zombie[i].announce();
        delete [] zombie;
    }
    return (0);
}