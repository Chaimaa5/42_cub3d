#include "Fixed.hpp"

Fixed::Fixed(const int fixed_point_number)
{
    this->fixed_point_number = roundf(fixed_point_number * (1 << fractional_bits));
}

Fixed::Fixed(const float fixed_point_number)
{
    this->fixed_point_number = roundf(fixed_point_number * (pow(2, fractional_bits) ));
}

Fixed::Fixed()
{
    fixed_point_number = 0;
}

Fixed::~Fixed()
{
}

Fixed::Fixed(Fixed const & F)
{
    (*this) = F;
}

Fixed & Fixed::operator=(Fixed const & F)
{

    this->fixed_point_number = F.getRawBits();
    return (*this);
}

int Fixed::getRawBits() const
{
    return (fixed_point_number);
}

void Fixed::setRawBits(int const raw)
{
    this->fixed_point_number = raw;
}

int Fixed::toInt() const
{
    return (roundf(fixed_point_number / (1 << fractional_bits)));
}

float Fixed::toFloat() const
{
    return (fixed_point_number / (pow(2, fractional_bits)));
}

std::ostream & operator<<(std::ostream & os, const Fixed & F)
{
    os << F.toFloat();
    return (os);
}

bool Fixed::operator < (Fixed const & F1)
{
    if (F1.fixed_point_number < this->fixed_point_number)
        return (1);
    else
        return (0);
}

bool Fixed::operator > (Fixed const & F1)
{
    if (F1.fixed_point_number > this->fixed_point_number)
        return (1);
    else
        return (0);
}

bool Fixed::operator >= (Fixed const & F1)
{
    if  (F1.fixed_point_number >= this->fixed_point_number)
        return (1);
    else
        return (0);
}

bool Fixed::operator <= (Fixed const & F1)
{
    if  (F1.fixed_point_number <= this->fixed_point_number)
        return (1);
    else
        return (0);
}

bool Fixed::operator == (Fixed const & F1)
{
    if (F1.fixed_point_number == this->fixed_point_number)
        return (1);
    else
        return (0);
}

bool Fixed::operator != (Fixed const & F1)
{
    if (F1.fixed_point_number != this->fixed_point_number)
        return (1);
    else
        return (0);
}

Fixed Fixed::operator * (Fixed const & F1)
{
    return (F1.fixed_point_number * this->fixed_point_number);
}

Fixed Fixed::operator + (Fixed const & F1)
{
    return (F1.fixed_point_number + this->fixed_point_number);
}

Fixed Fixed::operator - (Fixed const & F1)
{
    return (F1.fixed_point_number - this->fixed_point_number);
}

Fixed Fixed::operator / (Fixed const & F1)
{
    return (F1.fixed_point_number / this->fixed_point_number);
}

Fixed & Fixed::operator ++ ()
{
    ++(*this).fixed_point_number;
    return ((*this));
}

Fixed Fixed::operator ++ (int)
{
    Fixed F(*this);
    operator++();
    return (F);
}

Fixed & Fixed::operator -- ()
{
    --(*this).fixed_point_number;
    return ((*this));
}

Fixed Fixed::operator -- (int)
{
    Fixed F(*this);
    operator--();
    return (F);
}

Fixed & Fixed::min(Fixed & F1, Fixed & F2)
{
    if (F1.fixed_point_number < F2.fixed_point_number)
        return (F1);
    return (F2);
}

Fixed & Fixed::max(Fixed & F1, Fixed & F2)
{
    if (F1.fixed_point_number > F2.fixed_point_number)
        return (F1);
    return (F2);
}

const Fixed & Fixed::min(Fixed const & F1, Fixed const & F2)
{
    if (F1.fixed_point_number < F2.fixed_point_number)
        return (F1);
    return (F2);
}

const Fixed & Fixed::max(Fixed const & F1, Fixed const & F2)
{
    if (F1.fixed_point_number > F2.fixed_point_number)
        return (F1);
    return (F2);
}