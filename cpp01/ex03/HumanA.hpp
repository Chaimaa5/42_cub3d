#include "Weapon.hpp"

class HumanA{
    private:
        std::string name;
        Weapon      &weapon;
    public:
        void    attack();
        HumanA();
        ~HumanA();
        HumanA(std::string name, Weapon &weapon);
};