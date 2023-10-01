#ifndef POINTERSTACK_HPP
#define POINTERSTACK_HPP

#include "Pixel.hpp"

class pointerStack
{
private:
    // Node struct that holds 2 pointers, one of them points at the Node of another Data Structure that needs to have
    // its data (Pixel) modified. The other points at the Node below it of the same type.
    struct Node
    {
        Node(Pixel *p) : p(p), next(nullptr)
        {}

        // 'p' points at the Node that must have its data (Pixel) modified while 'next' points at the next Node
        // of its type.
        Pixel *p;
        Node *next;
    };

    // Points at the last Node of the Stack and first to be removed (LIFO).
    Node *top;

public:
    // pointerStack constructor.
    pointerStack();

    // Adds a Node to the Stack, increasing the top pointer.
    void push(Pixel *p);

    // Returns the top Node's data from the stack, decreasing the top pointer
    // and eliminating the Node from the Stack.
    Pixel *pop();

    // Returns true if Stack is empty. False otherwise.
    bool isEmpty();

    // Modifies all the pixels its Nodes point at
    // (Pixels in the cloned Structure, either List or Mesh).
    void modifyPixels(int color);

    // Prints last 100 inserted.
    void print100();

    void print();

    // Deletes the structure.
    void makeNull();
};

#endif //POINTERSTACK_HPP
