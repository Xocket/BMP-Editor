#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <filesystem>
#include <vector>

#include "ImageBMP.hpp"

class Console
{
public:
    // Function to print Banner.
    static void printBanner();

    // Function to print Menu.
    static void printMenu();

    // Function to print separator.
    static void printSeparator(int n);

    // Function to print Menu selection.
    static int printMenuSelection(int n);

    // Function to print duration of any process.
    static void printTime(int milliseconds, const std::string &process);

    // Function to prompt User to choose to either load a list of images or input a name.
    static int promptUserForImageInput();

    // Function to prompt user to select an image.
    static std::string promptUserForImageSelection(int input);

    // Function to load all images in 'images' folder.
    static std::vector<std::string> loadImages(bool load_list);

    // Function that returns User's chosen image.
    static std::string imageChoice(const std::vector<std::string> &filenames);

    // Function to validate User input.
    static int getUserInput(int lower_limit, int upper_limit, int max_tries, const std::string &request_msg,
                            const std::string &error_msg);

    // Function that returns a Pixel object with equal RGB values to User's input.
    static Pixel createSearchPixel();

    // Function to prompt User to decide between exiting the Program or continuing computing.
    static int exitUser();

    // Function to prompt User to decide which color to turn all found pixels to.
    static int userRGBChoice();

    // Function to print the Image data (size and total number of pixels).
    static void printImageData(ImageBMP img);

    // Function to return a name for the output image after asking the User for one.
    static std::string askImageName();
};

#endif //CONSOLE_HPP
