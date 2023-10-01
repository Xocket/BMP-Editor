#include "Pixel.hpp"

// Pixel constructor.
Pixel::Pixel(int r, int g, int b, int x_coord, int y_coord)
{
    // Sets RGB values.
    setRed(r);
    setGreen(g);
    setBlue(b);

    // Sets coordinates values.
    this->x = x_coord;
    this->y = y_coord;
}

// Pixel constructor mainly used to create User's RGB input Pixel object to look for other similars.
Pixel::Pixel(int r, int g, int b)
{
    setRed(r);
    setGreen(g);
    setBlue(b);
    this->x = -1;
    this->y = -1;
}

// Destructor Pixel class.
Pixel::~Pixel()
= default;

// Getters and Setters ************************************************************************************************
int Pixel::getRed() const
{
    return red;
}

void Pixel::setRed(int r)
{
    this->red = r;
}

int Pixel::getGreen() const
{
    return green;
}

void Pixel::setGreen(int g)
{
    this->green = g;
}

int Pixel::getBlue() const
{
    return blue;
}

void Pixel::setBlue(int b)
{
    this->blue = b;
}

int Pixel::getX() const
{
    return x;
}

[[maybe_unused]] void Pixel::setX(int x_coor)
{
    Pixel::x = x_coor;
}

int Pixel::getY() const
{
    return y;
}

[[maybe_unused]] void Pixel::setY(int y_coor)
{
    Pixel::y = y_coor;
}

// Changes Pixel to Red.
void Pixel::changeRed()
{
    setRed(255);
    setGreen(0);
    setBlue(0);
}

// Changes Pixel to Green.
void Pixel::changeGreen()
{
    setRed(0);
    setGreen(255);
    setBlue(0);
}

// Changes Pixel to Blue.
void Pixel::changeBlue()
{
    setRed(0);
    setGreen(0);
    setBlue(255);
}

// Changes Pixel to a specific color.
[[maybe_unused]] void Pixel::changeColor(int r, int g, int b)
{
    setRed(r);
    setGreen(g);
    setBlue(b);
}

// Prints Pixel RGB values.
[[maybe_unused]] void Pixel::printRGB() const
{
    std::cout << "R: " << this->getRed() << " G: " << this->getGreen() << " B: " << this->getBlue() << std::endl
              << std::endl;
}

// Output stream operator to print Pixel RGB values.
std::ostream &operator<<(std::ostream &os, const Pixel &pixel)
{
    os << "R: " << pixel.red << " G: " << pixel.green << " B: " << pixel.blue << " | Row: " << pixel.getY() <<
       " Column: " << pixel.getX() << std::endl;
    return os;
}

// Equality operator. Compares pixel only by RGB values.
bool Pixel::operator==(const Pixel &rhs) const
{
    return green == rhs.green &&
           blue == rhs.blue &&
           red == rhs.red;
}

bool Pixel::operator!=(const Pixel &rhs) const
{
    return !(rhs == *this);
}
