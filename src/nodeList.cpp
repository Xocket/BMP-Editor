#include "nodeList.hpp"
#include "ImageBMP.hpp"
#include "Console.hpp"

// nodeList constructor. It initializes head and tail to nullptr.
nodeList::nodeList()
{
    head = nullptr;
    tail = nullptr;
}

/*
// TODO fix, scales horribly with pixels.
void nodeList::insert(Pixel p, int position)
{
    int len = this->length();

    if (position < 0 || position > len)
    {

        std::cout << "Error, position out of list bounds.";

    } else if (head == nullptr && position == 0)
    {

        Node *newNode = new Node(p);

        head = newNode;
        tail = newNode;

    } else if (head != nullptr && position == 0)
    {

        Node *newNode = new Node(p);

        newNode->next = head;
        newNode->next->prev = newNode;
        newNode->prev = nullptr;
        head = newNode;


    } else
    {

        Node *newNode = new Node(p);
        Node *temp = head;

        for (int i = 0; i < position && temp->next != nullptr; i++)
        {

            temp = temp->next;

        }
        if (temp == tail)
        {
            tail = newNode;
        }

        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next = newNode;
        if (newNode->next != nullptr) newNode->next->prev = newNode;

    }

}
*/

// Inserts object Pixel at the beginning of the list.
void nodeList::append(Pixel p)
{

    if (head == nullptr)
    {

        Node *newNode = new Node(p);
        head = newNode;
        tail = newNode;

    } else
    {

        Node *newNode = new Node(p);

        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }

}

// Removes pixels in FIFO order.
Pixel nodeList::remove()
{
    if (head == nullptr || tail == nullptr)
    {
        std::cout << "The list is empty!";
    } else
    {
        Node *temp = tail;
        Pixel p = temp->p;
        if (tail->prev != nullptr)
        {
            tail->prev->next = nullptr;
            tail = tail->prev;
        } else
        {
            tail = nullptr;
            head = nullptr;
        }
        delete temp;
        return p;
    }

}

// Returns a list of pixels equivalent to User's input.
nodeList nodeList::searchPixels(Pixel p)
{
    // Initializes timer.
    Timer timer;
    timer.start();

    if (head == nullptr)
    {
        std::cout << "The list is empty!";
    } else
    {
        nodeList pixelsFound;
        Node *current = tail;

        int count{};

        while (current != nullptr)
        {
            if (current->p == p)
            {
                pixelsFound.append(current->p);
                count++;
            }
            current = current->prev;
        }
        if (count > 100)
        {
            Node *current = pixelsFound.tail;
            for (int i = 1; i < 101; i++)
            {
                std::cout << i << ". " << current->p;
                current = current->prev;
            }
            std::cout << "\nFound " << count << " pixels with the given parameters.\nPrinted first 100 of them.\n\n";
        } else
        {
            pixelsFound.print();
            std::cout << "Found " << count << " pixels with the given parameters.\n\n";
        }
        // Prints timer.
        Console::printTime(timer.stop(), "Searching/Creating filtered List");
        return pixelsFound;
    }
}

// Returns True if the List is empty, else it returns False.
bool nodeList::isEmpty()
{
    return head == nullptr;
}

// Returns size of the List (amount of Nodes in it).
int nodeList::length()
{
    int count{};
    Node *current = head;

    // While the current hasn't jumped over the last element it counts (at the Tail), it iterates throught the list
    // updating a counter.
    while (current != nullptr)
    {
        current = current->next;
        count++;
    }
    // Counter is returned.
    return count;
}

// Prints the List from Tail to Head, so it's displayed in FIFO order (because we add to the Head in this Program).
void nodeList::print()
{
    // If List is empty it prints a message.
    if (head == nullptr)
    {
        std::cout << "List is empty!";

        // Else a pointer is initialized and set to Tail. A counter is also initialized.
    } else
    {
        Node *current = tail;
        int count{};

        // While current hasn't jumped over the last element in the other end of the list, it updates the counter and
        // prints its current Pixel value.
        while (current != nullptr)
        {
            count++;
            std::cout << count << ". " << current->p;
            current = current->prev;
        }
        std::cout << std::endl;
    }
}

// Returns a pointerStack of only the Pixels that need to be changed.
pointerStack nodeList::getListOfFiltered(Pixel p)
{
    pointerStack filteredStack;
    Node *current = tail;

    while (current != nullptr)
    {
        if (p == current->p)
        {
            Pixel *pPixel = &current->p;
            filteredStack.push(pPixel);
        }

        current = current->prev;
    }
    return filteredStack;
}

// Writes image data to memory.
unsigned char *nodeList::dataToMem(ImageBMP img)
{
    // Creates object to point at memory block direction.
    unsigned char *image = (unsigned char *) malloc(sizeof(unsigned char) * (img.getWidth() * img.getHeight()) * 3);

    // Initializes counter.
    int pixel_number{};

    // While the list is not empty.
    while (!this->isEmpty())
    {
        // Removes from list and writes to memory.
        Pixel p = this->remove();

        *(image + pixel_number * 3 + 0) = p.getBlue();
        *(image + pixel_number * 3 + 1) = p.getGreen();
        *(image + pixel_number * 3 + 2) = p.getRed();

        pixel_number++;
    }
    return image;
}

// Clones a list using the internal pointers of the list.
void nodeList::clone(nodeList *original, nodeList *clone)
{
    // We initialize a pointer to the head/front of the list.
    Node *current = original->tail;
    // We initialize a counter since we're going to clone_deprecated the list using the insert(Pixel *p, int n) method.

    // While current does not point at nullptr, which it will only if it reaches the end of the list.
    while (current != nullptr)
    {
        // We pass by value, since insert() calls the constructor of the object.
        Pixel p = current->p;
        clone->append(p);
        // Update current pointer to point to the next node.
        current = current->prev;
    }
}

void nodeList::makeNull()
{
    while (!isEmpty())
    {
        remove();
    }
}

/*
nodeList nodeList::clone_deprecated()
{
    Node *current = tail;
    nodeList newList;
    while (current != nullptr)
    {
        Pixel p = current->p;
        newList.append(p);

        current = current->prev;

    }

    return newList;
}
*/

