#include "Fixed.hpp"

Fixed::Fixed(const int fixed_point_number)
{
    this->fixed_point_number = roundf(fixed_point_number * (1 << fractional_bits));
    std::cout << "Int Constructor called\n";
}

Fixed::Fixed(const float fixed_point_number)
{
    this->fixed_point_number = roundf(fixed_point_number * (pow(2, fractional_bits) ));
    std::cout << "Float Constructor called\n";
}

Fixed::Fixed()
{
    std::cout << "Default Constructor called" << std::endl;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(Fixed const & F)
{
    std::cout << "Copy Constructor called" << std::endl;
    (*this) = F;
}

Fixed & Fixed::operator=(Fixed const & F)
{

    std::cout << "Copy Assignment Operator called" << std::endl;
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
