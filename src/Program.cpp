#include "Program.hpp"

// Main function of the Program. Calls all other functions.
void Program::startProgram()
{
    // Prints Program's Banner
    Console::printBanner();

    // Asks to choose between loading images or inputting a name.
    // Retrieves a string with the image selection name stored in variable string 'name' that is initialized here.
    std::string name;
    name = Console::promptUserForImageSelection(Console::promptUserForImageInput());

    // Creates ImageBMP object to later load it with User's choice of image data (width, height and *image pointer to
    // the block of data in memory holding the RGB values).
    ImageBMP img;
    img.loadImage(name);

    // Prints Image Data (size and total pixels) in the Console.
    Console::printImageData(img);

    // QueA is created. This Queue will be the original queue used to clone_deprecated others. Boolean true to print time.
    nodeQueue QueA_OG = ImageBMP::loadQueA(img, true);

    // Clones QueA_OG in order to populate DaList_OG.
    nodeQueue QueA_1 = QueA_OG.clone(false);

    // DaList is created. This List will be the original list used to create the modified one.
    nodeList DaList_OG = ImageBMP::loadDaList(QueA_1, true);

    // Clones QueA_OG in order to populate DaPlace_OG.
    nodeQueue QueA_2 = QueA_OG.clone(false);

    // DaPlace_OG is created. This Mesh will be the original grid used to create the modified.
    nodeMesh DaPlace_OG;
    DaPlace_OG.populate(QueA_2, img, true); // DaPlace_OG is populated using QueA_2

    int user_choice_exit{};

    // Program main function.
    bool active = true;
    while (active)
    {
        // Choice variables initialized in order to store User's Menu choice and exit choice.
        int menu_choice{};

        // Prints Program's Menu.
        Console::printMenu();
        menu_choice = Console::printMenuSelection(Console::getUserInput(0, 4, 5,
                                                                        "Select an option using the number: ",
                                                                        "Error, input a correct option."));
        switch (menu_choice)
        {
            case 1:
            {
                // Asks for User input.
                Pixel p = Pixel(Console::createSearchPixel());

                // Creates a clone_deprecated of the original DaList.
                nodeList DaList_1;
                nodeList *clone = &DaList_1;
                nodeList *og = &DaList_OG;

                DaList_OG.clone(og, clone);

                // Creates a list with all pixels following User input.
                nodeList listTargetPixels = DaList_1.searchPixels(p);

                // Creates a stack with pointers to all the pixels to change.
                pointerStack filteredStack = DaList_1.getListOfFiltered(p);

                // Asks the user if they want to change the found pixels to Red, Green or Blue, but only if there
                // are any pixels to change.
                if (!listTargetPixels.isEmpty())
                {
                    // Asks the user for the specific color to change to. Red, Green or Blue.
                    int user_choice_color = Console::userRGBChoice();

                    // Modifies the clone_deprecated of DaList_OG which will be used to save the image.
                    filteredStack.modifyPixels(user_choice_color);

                    // Allocates memory to save the list's Pixel RGB data then it uses a pointer to that
                    // memory block to save it as an image called "OUTPUT.bmp" in 'images'.
                    unsigned char *output = DaList_1.dataToMem(img);

                    // Asks the User for a name for the new image.
                    std::string img_name = Console::askImageName();

                    // Saves the image data as an image.bmp
                    img.saveImage(img_name, output);

                    // Else it prints a message.
                } else std::cout << "\n\e[1mNo pixels found with your parameters!\e[0m\n";

                // Asks the user if they want to exit the Program or continue.
                user_choice_exit = Console::exitUser();
                break;
            }
            case 2:
            {
                // Asks for User input.
                Pixel p = Pixel(Console::createSearchPixel());

                // QueA_3 is created cloning the original QueA, in order to populate a copy of the Mesh to
                // change, so the original Mesh remains the same.
                nodeQueue QueA_3 = QueA_OG.clone(false);
                nodeMesh DaPlace_1;
                DaPlace_1.populate(QueA_3, img, false); // DaPlace_OG is populated using QueA_2

                pointerStack filteredStack = DaPlace_1.searchPixels(p);

                // Asks the user if they want to change the found pixels to Red, Green or Blue, but only if there
                // are any pixels to change.
                if (!filteredStack.isEmpty())
                {
                    // Asks the user for the specific color to change to. Red, Green or Blue.
                    int user_choice_color = Console::userRGBChoice();

                    // Modifies the clone_deprecated of DaPlace_OG which will be used to save the image.
                    filteredStack.modifyPixels(user_choice_color);

                    // Allocates memory to save the Mesh's Pixel RGB data then it uses a pointer to that
                    // memory block to save it as an image.
                    unsigned char *output = DaPlace_1.dataToMem(img);

                    // Asks the User for a name for the new image.
                    std::string img_name = Console::askImageName();

                    // Saves the image data as an image.bmp
                    img.saveImage(img_name, output);

                    // Else it prints a message.
                } else std::cout << "\n\e[1mNo pixels found with your parameters!\e[0m\n";

                // Asks the user if they want to exit the Program or continue.
                user_choice_exit = Console::exitUser();
                break;
            }
            case 3:
            {
                nodeQueue QueA_3 = QueA_OG.clone(false);
                nodeMesh DaPlace_1;
                DaPlace_1.populate(QueA_3, img, false);
                DaPlace_1.mirrorImage();

                unsigned char *output = DaPlace_1.dataToMem(img);

                // Asks the User for a name for the new image.
                std::string img_name = Console::askImageName();

                // Saves the image data as an image.bmp
                img.saveImage(img_name, output);

                // Asks the user if they want to exit the Program or continue.
                user_choice_exit = Console::exitUser();
                break;

            }
            case 4:

                nodeQueue QueA_3 = QueA_OG.clone(false);
                nodeMesh DaPlace_1;

                DaPlace_1.populate(QueA_3, img, false);
                DaPlace_1.averageMirror();

                // Asks the user if they want to exit the Program or continue.
                user_choice_exit = Console::exitUser();
                break;


        }
        // Exits the program if User wants to.
        if (user_choice_exit == 0)
        {
            active = false;

        } else if (user_choice_exit == 2)
        {
            Program::startProgram();
        }
    }
}

