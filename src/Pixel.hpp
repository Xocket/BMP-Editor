#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <ostream>
#include <iostream>

class Pixel
{
private:
    // RGB values.
    int green{};
    int blue{};
    int red{};

    // Coordinates values.
    int x;
    int y;

public:
    // Constructors and destructors.
    Pixel(int r, int g, int b, int x_coord, int y_coord);

    Pixel(int r, int g, int b);

    ~Pixel();

    // Getters and setters for the three colors.
    int getRed() const;

    void setRed(int r);

    int getGreen() const;

    void setGreen(int g);

    int getBlue() const;

    void setBlue(int b);

    int getX() const;

    [[maybe_unused]] void setX(int x_coor);

    int getY() const;

    [[maybe_unused]] void setY(int y_coor);

    // Functions to change the pixel to one of Red, Green or Blue.
    void changeRed();

    void changeGreen();

    void changeBlue();

    // Function to change the pixel to any color by changing any RGB value.
    [[maybe_unused]] void changeColor(int r, int g, int b);

    // Stream output operator.
    friend std::ostream &operator<<(std::ostream &os, const Pixel &pixel);

    [[maybe_unused]] void printRGB() const;

    // Equality operators.
    bool operator==(const Pixel &rhs) const;

    bool operator!=(const Pixel &rhs) const;
};

#endif //PIXEL_HPP
