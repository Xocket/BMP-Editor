#ifndef NODEMESH_HPP
#define NODEMESH_HPP

#include "ImageBMP.hpp"

class nodeMesh
{
private:
    struct Node
    {
        Node(Pixel p) : p(p), up(nullptr), down(nullptr), right(nullptr), left(nullptr)
        {}

        Pixel p;

        Node *up;
        Node *down;
        Node *right;
        Node *left;

        // Bool variable to check if a Node was visited during searching.
        bool isVisited = false;
    };

    Node *origin;
    Node *tail;

public:

    nodeMesh();

    // This algorithm extracts each node in order from a nodeQueue and populates it row by row from left to right.
    // Once a row is populated and all nodes are linked left to right, the head_row pointer indicates where to link the
    // second row's first node to. Making the head_row the pointer to the first node in each row and always below the new row.
    // A second node called linker will be used to point at the node below each new node in the new row, using it to link
    // every vertical pair of nodes together. A third pointer called tail will point at the last object inserted into
    // the mesh. Finally, the origin pointer will point at the first node of the mesh.
    // Repeat process until you have the entire mesh.

    // Populates the empty instance of DaPlace at creation. It uses a clone_deprecated of the starting QueA,
    // the Image's data and a boolean to measure or not the time.
    void populate(nodeQueue queue, ImageBMP img, bool t);

    // Travels the entire Mesh in a counterclockwise spiral right->up->left->down
    // checking if Pixels are the same as the User's Pixel and returns a pointerStack
    // with pointers to the Pixels to later change them.
    pointerStack searchPixels(Pixel p);

    // Returns true if there are any pixels not visited around the current Pixel,
    // else false (search ends). It is used in searchPixels(Pixel p)
    bool continueTraversing(nodeMesh::Node *current);

    // Writes the Mesh's data to a memory block to later save as an image.
    unsigned char *dataToMem(ImageBMP img);

    // Mirrors the image using the bottom-left to top-right diagonal.
    void mirrorImage();

    // Computes the average of pixel-pairs using the bottom-left top-right diagonal
    // just like mirrorImage() returning its value.
    double averageMirror();

};


#endif //NODELIST_HPP
