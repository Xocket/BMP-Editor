#include "pointerStack.hpp"

// Constructor pointerStack class.
pointerStack::pointerStack()
{
    top = nullptr;
}

// Inserts a Node on top of the Stack, then it updates the top pointer.
void pointerStack::push(Pixel *p)
{
    // Creates new Node structure with the Pixel pointer and a pointer to it.
    Node *newNode = new Node(p);

    // If pointerStack is empty (top = nullptr), then top is set to the newNode.
    if (top == nullptr)
    {
        top = newNode;

        // Else the newNode is set to point to the current top and after that the top pointer is updated to point at
        // the last Node added (this one).
    } else
    {
        newNode->next = top;
        top = newNode;
    }
}

// Returns the data pointed at by top. After that it updates top and deletes the Node.
Pixel *pointerStack::pop()
{
    // If nodeStack is empty (top = nullptr) it prints a message and returns nullptr.
    if (top == nullptr)
    {
        return nullptr;

        // Else a temp pointer to the Node pointed at by top is created, so top can be moved to point to the next Node
        // and ALSO be able to delete the Node we return the data from, to free memory. If a temp pointer is not used
        // we either have to delete the Node top points at, but then we can't update top, or we must update top but
        // can't delete the Node top abandons because nothing points at it.
    } else
    {
        // New temp pointer set to top's Node.
        Node *temp = top;

        // The Pixel pointer is retrieved from temp/top (both pointers point at the same Node at time of execution).
        Pixel *pPixel = temp->p;

        // top is updated to point at the next node (or the Node below it, if we imagine a vertical Stack).
        top = temp->next;

        // The Node temp points at is deleted.
        delete temp;

        // The Pixel pointer is returned.
        return pPixel;
    }
}

// Returns true if pointerStack is empty, false if not.
bool pointerStack::isEmpty()
{
    return top == nullptr;
}

// Modifies all the pixels its Nodes point at (Pixels in the cloned Structure, either List or Mesh).
void pointerStack::modifyPixels(int color)
{
    while (!this->isEmpty())
    {
        Pixel *pPixel = this->pop();

        switch (color)
        {
            case 1:
                pPixel->changeRed();
                break;
            case 2:
                pPixel->changeGreen();
                break;
            case 3:
                pPixel->changeBlue();
                break;
        }
    }
}

void pointerStack::print100()
{
    if (!isEmpty())
    {
        Node *current = top;
        for (int i = 0; i < 100; i++)
        {
            std::cout << *current->p;
            current = current->next;
        }
    }
}

void pointerStack::print()
{
    if (!isEmpty())
    {
        Node *current = top;
        while (current->next != nullptr)
        {
            std::cout << *current->p;
            current = current->next;
        }
    }

}

void pointerStack::makeNull()
{
    while (!isEmpty())
    {
        pop();
    }
}
