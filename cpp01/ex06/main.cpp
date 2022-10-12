#include "Harl.hpp"

int main(int ar, char **av)
{
    Harl harl;
    std::string level;

    if (ar == 2)
    {
        level = av[1];
        harl.complain(level);
    }
    else
        std::cout << "Too much arguments\n";
    return (0);
}