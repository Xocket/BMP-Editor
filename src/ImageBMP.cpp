#include "ImageBMP.hpp"

// ImageBMP class constructor.
ImageBMP::ImageBMP()
{
    this->image = nullptr;
    this->width = 0;
    this->height = 0;

}

// Loads the .bmp data in a block of memory using tinyimage's library functions using the name of the image as
// parameter.
void ImageBMP::loadImage(const std::string &name)
{
    // Creates pointer to the name of the image.
    const char *filename = name.c_str();

    // Loads image.
    TinyImgColorType type = TINYIMG_RGB;
    this->image = tinyimg_load(filename, pwidth, pheight, type);

    // Displays error or success message depending on whether image was loaded or not.
    if (!image)
    {
        std::cout << "Failed to load image!" << std::endl;
    } else
    {
        std::cout << "BMP loaded successfully!\n" << std::endl;
    }
}

// Saves a block of memory as a .bmp img.
void ImageBMP::saveImage(const std::string &name, unsigned char *img)
{
    // Removes any img that might exist with the same name.
    std::remove(name.c_str());
    // Saves the img in the 'images' folder.
    tinyimg_save(name.c_str(), this->width, this->height, TINYIMG_RGB, img);

    // Image is freed in memory.
    tinyimg_free(img);
}

nodeQueue ImageBMP::loadQueA(ImageBMP img, bool t)
{
    // Initializes timer.
    Timer timer;
    timer.start();

    // Initializes total pixel count.
    int total_pixels = (*img.getPwidth()) * (*img.getPheight());

    // Creates a queue data structure called 'QueA'.
    nodeQueue QueA;

    for (int pixel = 0; pixel < total_pixels; pixel++)
    {
        //Calculates row and column based on Image ratio and pixel count.
        int row = pixel / *img.getPwidth();
        int column = pixel % *img.getPwidth();

        // Calculates RGB values using pointer arithmetic. In memory, they are inverted -> Blue, Green, Red.
        int blue = static_cast<int>(*((img.getImage() + (3 * pixel))));
        int green = static_cast<int>(*((img.getImage() + (3 * pixel)) + 1));
        int red = static_cast<int>(*((img.getImage() + (3 * pixel)) + 2));

        // Creates Pixel object with computed RGB values and coordinates. After, it enqueues the pixel in the
        // queue data structure.
        Pixel pixelRGB(red, green, blue, column + 1, row + 1);
        QueA.enqueue(pixelRGB);
    }
    // Prints total time of execution if t boolean is set to true.
    if (t) Console::printTime(timer.stop(), "Creating    QueA");

    // Frees image in disk.
    tinyimg_free(img.getImage());

    // Returns the Queue.
    return QueA;
}

// TODO might need to be changed from this file to another.
// Creates a list data structure using the original queue and returns it populated.
nodeList ImageBMP::loadDaList(nodeQueue QueA, bool t)
{
    // Initializes timer.
    Timer timer;
    timer.start();

    // Initializes a list called 'DaList'.
    nodeList DaList;

    // Iterates through the list dequeuing from the queue and enqueuing in the list.
    while (!QueA.isEmpty())
    {
        DaList.append(QueA.dequeue());
    }
    // Prints total execution time.
    if (t) Console::printTime(timer.stop(), "Creating  DaList");

    return DaList;
}

// Getters and Setters **********************************************************************************************+*
unsigned char *ImageBMP::getImage() const
{
    return image;
}

[[maybe_unused]] void ImageBMP::setImage(unsigned char *img)
{
    ImageBMP::image = img;
}

int ImageBMP::getWidth() const
{
    return width;
}

[[maybe_unused]] [[maybe_unused]] void ImageBMP::setWidth(int wid)
{
    ImageBMP::width = wid;
}

int *ImageBMP::getPwidth() const
{
    return pwidth;
}

[[maybe_unused]] [[maybe_unused]] void ImageBMP::setPwidth(int *pwid)
{
    ImageBMP::pwidth = pwid;
}

int ImageBMP::getHeight() const
{
    return height;
}

[[maybe_unused]] [[maybe_unused]] void ImageBMP::setHeight(int heig)
{
    ImageBMP::height = heig;
}

int *ImageBMP::getPheight() const
{
    return pheight;
}

[[maybe_unused]] [[maybe_unused]] void ImageBMP::setPheight(int *pheig)
{
    ImageBMP::pheight = pheig;
}
