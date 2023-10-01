#ifndef NODELIST_HPP
#define NODELIST_HPP

#include <iostream>

#include "pointerStack.hpp"

class ImageBMP;

class nodeList
{

private:
    // Node struct that holds one piece of data (Pixel object) and two pointers to the next and previous Nodes in the
    // List.
    struct Node
    {
        Node(Pixel p) : p(p), next(nullptr), prev(nullptr) {}

        // Pixel object.
        Pixel p;

        // Next pointer points to the next node in the List (the one in front of it).
        // Prev pointer points to the previous node in the List (the one behind it).
        Node *next;
        Node *prev;
    };

    // Head and Tail pointers indicate the extremes of the List. We can insert at both ends and remove from both ends
    // as both operations are O(1).
    Node *head;
    Node *tail;

public:
    // nodeList constructor.
    nodeList();

    // Prints the list from the Tail to Head (We add to the Head, so it's printed in FIFO order).
    void print();

    // Returns the length of the List (number of Nodes in it).
    int length();

    // Returns true if the List is empty, false otherwise.
    bool isEmpty();

    // Inserts a Pixel object in the position it takes as argument.
    // void insert(Pixel p, int position);

    // Also known as append, it inserts a Pixel object at the start of the list.
    void append(Pixel p); // Works just like insert with parameter position = 0

    // Returns the Pixel object located at the end of the list.
    Pixel remove();

    // Returns a list of all pixels that comply with user's parameter by using a Pixel object.
    nodeList searchPixels(Pixel p);

    // returns a stack of Nodes of pointers to the nodes we need to modify.
    // It basically holds pointers to nodes that we
    // need to change, so we don’t have to compute them again
    // after prompting the user to select which change to apply.
    pointerStack getListOfFiltered(Pixel p);

    // Returns a pointer to the start of a block of memory holding
    // all pixels RGB values to later process it and save the image
    // in /images. It takes an ImageBMP object as parameter because
    // it stores the size (width and height) of the image the user
    // initially asked the program to load.
    unsigned char *dataToMem(ImageBMP img);

    // nodeList clone_deprecated();

    // clones a list using the internal pointers of the list,
    // traversing it node by node and copying Pixel objects
    // by value and inserting them inside the clone_deprecated list.
    void clone(nodeList *original, nodeList *clone);

    // Deletes the structure.
    void makeNull();

};

#endif //NODELIST_HPP
