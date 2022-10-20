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

        int     getRawBits() const;
        void    setRawBits(int const fixed_point_number);

        float   toFloat(void) const;
        int     toInt(void) const;

        bool operator < (Fixed const & F1);
        bool operator > (Fixed const & F1);
        bool operator >= (Fixed const & F1);
        bool operator <= (Fixed const & F1);
        bool operator == (Fixed const & F1);
        bool operator != (Fixed const & F1);

        Fixed operator * (Fixed const & F1);
        Fixed operator + (Fixed const & F1);
        Fixed operator - (Fixed const & F1);
        Fixed operator / (Fixed const & F1);

        Fixed & operator ++ ();
        Fixed operator ++ (int);
        Fixed & operator -- ();
        Fixed operator -- (int);
        
        static const Fixed & min(Fixed const & F1, Fixed const & F2);
        static Fixed & min(Fixed & F1, Fixed & F2);
        static const Fixed & max(Fixed const & F1, Fixed const & F2);
        static Fixed & max(Fixed & F1, Fixed & F2);


};

std::ostream& operator<<(std::ostream & os, const Fixed & F);

#endif