#include "Console.hpp"

// Prints Banner.
void Console::printBanner()
{
    std::cout << std::endl;
    std::cout << "    _                                _ _ _             " << "\n";
    std::cout << "   | |__  _ __ ___  _ __     ___  __| (_) |_ ___  _ __ " << "\n";
    std::cout << R"(   | '_ \| '_ ` _ \| '_ \   / _ \/ _` | | __/ _ \| '__|)" << "\n";
    std::cout << "  _| |_) | | | | | | |_) | |  __/ (_| | | || (_) | |   " << "\n";
    std::cout << R"( (_)_.__/|_| |_| |_| .__/   \___|\__,_|_|\__\___/|_|   )" << "\n";
    std::cout << "                   |_|                                 " << "\n";
    std::cout << std::endl;

    std::cout << "\t   Made by Daniel Mihai Bostan Tiron";

    printSeparator(2);
}

// Prints main Menu.
void Console::printMenu()
{
    std::cout << std::endl;
    std::cout << "------------------------------------------------------" << "\n";
    std::cout << "|\e[1m                       MENU                         \e[0m|" << "\n";
    std::cout << "|----------------------------------------------------|" << "\n";
    std::cout << "| (1) Search on the list.                            |" << "\n";
    std::cout << "| (2) Search on the mesh.                            |" << "\n";
    std::cout << "| (3) Mirroring using the mesh.                      |" << "\n";
    std::cout << "| (4) Mirror comparison using the mesh.              |" << "\n";
    std::cout << "|                                                    |" << "\n";
    std::cout << "| (0) Exit.                                          |" << "\n";
    std::cout << "------------------------------------------------------" << "\n";
    std::cout << std::endl;
}

// Prints separator with blank lines above as given with parameter n.
void Console::printSeparator(int n)
{
    for (int i = 0; i < n; i++) std::cout << std::endl;
    std::cout << "******************************************************";
    std::cout << std::endl << std::endl;
}

// Prints User's Menu choice.
int Console::printMenuSelection(int n)
{
    Console::printSeparator(1);

    // Switch statement for every possible valid option.
    switch (n)
    {
        // Case 0 exists the program.
        case 0:
            std::cout << "\e[1m Exiting the program...\e[0m" << "\n\n";
            system("pause");
            exit(1);

            // Case 1, 2, 3, 4 print User's selection.
        case 1:
            std::cout << "\e[1m (1) Search on the list.\e[0m" << "\n\n";
            break;

        case 2:
            std::cout << "\e[1m (2) Search on the mesh.\e[0m" << "\n\n";
            break;

        case 3:
            std::cout << "\e[1m (3) Mirroring using the mesh.\e[0m" << "\n\n";
            break;

        case 4:
            std::cout << "\e[1m (4) Mirror comparison using the mesh.\e[0m" << "\n\n";
            break;

            // Default case.
        default:
            break;
    }
    return n;
}

// Prints time formatting it first from milliseconds and a string to indicate what it was measuring.
void Console::printTime(int milliseconds, const std::string &process)
{
    // If there are 60s or more worth of milliseconds, convert them to min, sec and ms.
    if (milliseconds >= 60'000)
    {
        int min = milliseconds / 60'000;
        int sec = (milliseconds % 60'000) / 1'000;
        int ms = milliseconds % 1'000;

        // Prints the result.
        std::cout << "Total time for \e[1m[" << process << "]\e[0m: " << min << " min " << sec << " sec "
                  << ms << " ms.";

        // If there are between 1s and 60s, convert them to sec and ms.
    } else if (milliseconds > 1'000)
    {
        int sec = milliseconds / 1'000;
        int ms = milliseconds % 1'000;

        std::cout << "Total time for \e[1m[" << process << "]\e[0m: " << sec << " sec " << ms << " ms.";

        // Else print the ms.
    } else
    {
        int ms = milliseconds;

        std::cout << "Total time for \e[1m[" << process << "]\e[0m: " << ms << " ms.";
    }
    std::cout << std::endl;
}

// Asks the User between loading a list of images in the console or inputting the name of one.
int Console::promptUserForImageInput()
{
    std::cout << "Select between loading images or input its name: \n\n";
    std::cout << " (1) Load images from 'images' folder.\n";
    std::cout << " (2) Input name.\n\n";

    // Makes the user choose between the two options.
    return Console::getUserInput(1, 2, 5, "Choose (1) or (2): ", "Error, choose a correct option.");
}

// Prints a list of images from the 'images' folder or prompts the user to enter an image name based on his choice.
std::string Console::promptUserForImageSelection(int input)
{
    // If user wants to "load images" it prints the 'images' folder list.
    if (input == 1)
    {
        Console::printSeparator(1);
        // Loads image list and displays it (load_list = true).
        std::string image_name = Console::imageChoice(Console::loadImages(true));
        return image_name;

        // Otherwise it prompts the user to enter a image name.
    } else
    {
        for (int tries = 0; tries < 5; tries++)
        {
            std::string image_name{};
            std::cout << "\nEnter the name of the image (.bmp NOT included): ";
            std::cin >> image_name;
            image_name += ".bmp";

            // Loads images list but does not display it (load_list = false).
            std::vector<std::string> filenames = loadImages(false);

            // If the name inserted exists it validates to true.
            bool exists = false;
            for (const auto &filename: filenames)
            {
                if (image_name == filename)
                {
                    exists = true;
                }
            }

            // If the image exists it prints user selection and returns its name.
            if (exists)
            {
                Console::printSeparator(1);
                std::cout << "Selected: \e[1m" << image_name << "\e[0m\n";
                return image_name;


            } else
            {
                // If the image does not exist, and it was the last attempt, the program exists.
                if (tries == 4)
                {
                    std::cout << "\n\e[1m Exiting the program...\e[0m\n";
                    system("pause");
                    exit(1);

                    // Else it prompts the User again to input a name.
                } else
                {
                    std::cout << "\nIncorrect name. Check and try again.";
                }
            }
        }
    }
}

// Uses "filesystem" to load all images from the target folder. Next it prints the list one by one.
std::vector<std::string> Console::loadImages(bool load_list)
{
    // 'images' folder path relative to the project.
    std::string path = ".";

    // Declare string vector 'filenames' to store images names.
    std::vector<std::string> filenames;

    // Iterate and store each filename inside the array.
    for (const auto &entry: std::filesystem::directory_iterator(path))
    {
        filenames.push_back(entry.path().filename().string());
    }

    // Prints each filename inside the 'filenames' array if the list needs to be loaded.
    if (load_list)
    {
        std::cout << "Choose one of the images on this list: \n\n";
        for (int i = 1; i < static_cast<int>(filenames.size()) + 1; i++)
        {
            std::cout << "(" << i << ") " << filenames[i - 1] << std::endl;
        }
    }
    // Returns the vector so the user can select one of them with imageChoice().
    return filenames;
}

// Asks for User's choice of image and returns the filename name so tinyImage can load it.
std::string Console::imageChoice(const std::vector<std::string> &filenames)
{
    Console::printSeparator(1);

    // Validates User's input.
    int input = getUserInput(1, static_cast<int>(filenames.size()), 5, "Select an image: ",
                             "Error, input a correct option.");

    Console::printSeparator(1);

    // Prints User's selection.
    std::cout << "You selected: \e[1m" << filenames[input - 1] << "\e[0m\n";

    // Returns User's choice as a string.
    return filenames[input - 1];
}

// Validates User's input. Returns a valid integer.
int Console::getUserInput(int lower_limit, int upper_limit, int max_tries, const std::string &request_msg,
                          const std::string &error_msg)
{
    // max_tries parameters determines the number of tries before it closes the program.
    for (int tries = 0; tries < max_tries; tries++)
    {
        // Displays prompt.
        std::cout << request_msg;

        // Initializes input variable and asks for user's input.
        int input{};
        std::cin >> input;

        // Validates user's input.
        if (std::cin.fail() || input < lower_limit || input > upper_limit)
        {
            // Clears console buffer.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Exists the program if try was last one.
            if (tries == max_tries - 1)
            {
                std::cout << "\n\e[1m Exiting the program...\e[0m\n\n";
                system("pause");
                exit(1);

                // Prints error message if input was not valid.
            } else
            {
                std::cout << '\n' << error_msg << '\n';
            }
        } else
        {
            // Returns User input if it was valid.
            return input;
        }
    }
}

// Asks the User for RGB values and creates a pixel object with that will be used to search.
Pixel Console::createSearchPixel()
{
    std::cout << "Input RGB values to search on the list:" << "\n\n";

    // Stores RGB values while validating input.
    int red = getUserInput(0, 255, 5, "   Red: ", "Error, input out of valid range.");
    int green = getUserInput(0, 255, 5, " Green: ", "Error, input out of valid range.");
    int blue = getUserInput(0, 255, 5, "  Blue: ", "Error, input out of valid range.");

    std::cout << std::endl;

    // Creates Pixel object with RGB values.
    Pixel p(red, green, blue);

    // Returns the Pixel object.
    return p;
}

// Asks the User what they want to do after computing.
int Console::exitUser()
{
    Console::printSeparator(1);

    std::cout << "Do you want to exit the program or compute again?";
    std::cout << "\n\n (1) Compute again.\n";
    std::cout << " (2) Change image.\n\n";
    std::cout << " (O) Exit.\n\n";

    // Validates User's choice and returns it.
    int user_choice = getUserInput(0, 2, 5, "Select an option using the number: ", "Error, select again.");
    return user_choice;
}

// Asks the User which color to change the found pixels to (Red, Green or Blue).
int Console::userRGBChoice()
{
    Console::printSeparator(1);

    std::cout << "Which color do you want to change the Pixels to?";
    std::cout << "\n\n (1)   Red [255, 0, 0]";
    std::cout << "\n (2) Green [0, 255, 0]";
    std::cout << "\n (3)  Blue [0, 0, 255]\n\n";

    // Validates User's choice and returns it.
    int user_choice = getUserInput(1, 3, 5, "Select an option using the number: ", "Error, select again.");
    return user_choice;
}

// Prints Image Data (size and total number of pixels).
void Console::printImageData(ImageBMP img)
{
    // Initializes variables to hold size and total pixels.
    int total_pixels = (*img.getPwidth()) * (*img.getPheight());
    int width = *img.getPwidth();
    int height = *img.getPheight();

    // Prints the result.
    std::cout << "Image Size: " << width << " x " << height << "\nNumber of Pixels = " << total_pixels << std::endl
              << std::endl;
}

// Asks the User for a name for the output image, returning a string to the program.
std::string Console::askImageName()
{
    std::cout << "\nInput a name to save the image: ";

    // Initializes variable.
    std::string input;
    std::cin >> input;

    // Returns the name with .bmp extension added.
    return input += ".bmp";
}
