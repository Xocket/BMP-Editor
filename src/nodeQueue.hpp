#ifndef NODEQUEUE_HPP
#define NODEQUEUE_HPP

#include <iostream>
#include "Pixel.hpp"


// TODO Maybe choose better nomenclature, Head and Tail can be confusing.
class nodeQueue {
private:
    // Node struct that holds one piece of data (Pixel object) and a pointer to the next Node in the Queue.
    struct Node {
        Node(Pixel p) : p(p), next(nullptr) {}

        // Pixel object.
        Pixel p;
        // Next pointer which points to the next Node in the Queue.
        Node *next;
    };

    // Head and tail pointers used to indicate both extremes of the Queue. Nodes will be inserted at the Head and
    // will exit from the Tail.

    // HEAD <-- NODE <-- NODE <-- NODE <-- NODE <-- NODE <-- TAIL
    Node *head;
    Node *tail;

public:
    // nodeQueue constructor.
    nodeQueue();

    // Adds a new Node to the back of the Queue using the Tail pointer.
    void enqueue(Pixel p);

    // Removes the first Node at the front of the Queue using the Head pointer.
    Pixel dequeue();

    // Returns true if empty, else false.
    bool isEmpty();

    // Prints the Queue's contents in FIFO order, from the Head to the Tail.
    void print();

    // Copies and returns an identical Queue.
    nodeQueue clone(bool t);

    // Clones a queue using a third temporal queue.
    void clone(nodeQueue *original, nodeQueue *clone);

    // Deletes the structure.
    void makeNull();
};

#endif //NODEQUEUE_HPP
