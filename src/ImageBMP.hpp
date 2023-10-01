#ifndef IMAGEBMP_HPP
#define IMAGEBMP_HPP

#include <iostream>

#include "nodeQueue.hpp"
#include "tinyimage.hpp"
#include "nodeList.hpp"
#include "Timer.hpp"
#include "Console.hpp"

class ImageBMP
{
private:
    unsigned char *image;

    int width;
    int *pwidth = &width;

    int height;
    int *pheight = &height;

public:
    // Constructor.
    ImageBMP();

    // Function to load image in memory.
    void loadImage(const std::string &name);

    // Function to create original queue.
    static nodeQueue loadQueA(ImageBMP img, bool t);

    // Function to create DaList.
    static nodeList loadDaList(nodeQueue QueA, bool t);

    // Function to save the image from a block of memory in the 'images' folder.
    void saveImage(const std::string &name, unsigned char *img);

    // Getters and Setters.
    [[nodiscard]] unsigned char *getImage() const;

    [[maybe_unused]] void setImage(unsigned char *img);

    [[nodiscard]] int getWidth() const;

    [[maybe_unused]] void setWidth(int wid);

    [[nodiscard]] int *getPwidth() const;

    [[maybe_unused]] void setPwidth(int *pwid);

    [[nodiscard]] int getHeight() const;

    [[maybe_unused]] void setHeight(int heig);

    [[nodiscard]] int *getPheight() const;

    [[maybe_unused]] void setPheight(int *pheig);
};

#endif //IMAGEBMP_HPP
