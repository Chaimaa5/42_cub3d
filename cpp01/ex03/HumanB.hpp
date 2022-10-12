#include "HumanA.hpp"

class HumanB{
    private:
        std::string name;
        Weapon      *weapon;
    public:
        void    attack();
        HumanB();
        ~HumanB();
        HumanB(std::string name);
        void    setWeapon(Weapon &weapon);

};