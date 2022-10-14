#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed{
    private:
        int raw;
        static const int fract = 8;
    public:
        Fixed();
        ~Fixed();
        Fixed(Fixed const & F);
        Fixed & operator=(Fixed const & F);
        int getRawBits() const;
        void setRawBits(int const raw);
};
#endif