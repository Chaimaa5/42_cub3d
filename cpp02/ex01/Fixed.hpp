#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>
class Fixed{
    private:
        float  fixed_point_number;
        static const int  fractional_bits = 8;
    public:
        Fixed();
        Fixed(const int fixed_point_number);
        Fixed(const float fixed_point_number);
        ~Fixed();
        Fixed(Fixed const & F);
        Fixed & operator=(Fixed const & F);
        int getRawBits() const;
        void setRawBits(int const fixed_point_number);
        float toFloat(void) const;
        int toInt(void) const;
};

std::ostream& operator<<(std::ostream & os, const Fixed & F);

#endif