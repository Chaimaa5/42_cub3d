#include "Fixed.hpp"

Fixed::Fixed()
{
    raw = 0;
    std::cout << "Default Constructor called" << std::endl;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(Fixed const & F)
{
    this->raw = F.raw;
    std::cout << "Copy Constructor called" << std::endl;
}


Fixed & Fixed::operator=(Fixed const & F)
{
    this->raw = F.raw;
    std::cout << "Copy Assignment Operator called" << std::endl;
    return (*this);
}

int Fixed::getRawBits() const
{
    std::cout << "getRawBits member function called\n";
    return (raw);
}

void Fixed::setRawBits(int const raw)
{
    this->raw = raw;
}