#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : name(name), weapon(weapon)
{
    std::cout << "HumanA Parametrized Constructor called\n";
}

HumanA::~HumanA()
{
    std::cout << "HumanB Destructor called\n";
}

void    HumanA::attack(){
    std::cout << name << " attacks with their" << this->weapon.getType() << std::endl;
}


