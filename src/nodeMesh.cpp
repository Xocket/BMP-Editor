#include "nodeMesh.hpp"
#include "Console.hpp"

nodeMesh::nodeMesh()
{
    origin = nullptr;
    tail = nullptr;
}

// Returns a mesh populated after giving a queue to extract from and the img data (width and height) as parameters.
void nodeMesh::populate(nodeQueue queue, ImageBMP img, bool t)
{
    // Initializes timer.
    Timer timer;
    timer.start();

    // Initializes two pointers to correctly run the algorithm, 'head_row' to point at the first Node of each row and
    // 'linker' to point at the Node below the last one.
    Node *head_row = nullptr;
    Node *linker = nullptr;

    // Gets image's width in order to draw the lines.
    int width = img.getWidth();

    // Pixel counter to check if a pixel is the first in each line.
    int pixel{1};

    // While loop until queue is empty.
    while (!queue.isEmpty())
    {
        // nodeMesh Node created with 4 pointers (up, down, right, left) using the queue's remove function returning
        // a Pixel object.
        Node *newNode = new Node(queue.dequeue());

        // Calculate row of image.
        int row = (pixel - 1) / width;

        // If origin == nullptr, then mesh is empty so first Node must be pointed at by head_row, linker, tail and
        // origin.
        if (origin == nullptr)
        {
            // Set head_row, linker, tail and origin to newNode.
            origin = newNode;
            head_row = newNode;
            linker = newNode;
            tail = newNode;

            // If we're in the first row and the newNode does still belong in it. We place the newNode and point its
            // left pointer to tail  (last node placed before newNode). Then we update tail's node right pointer to
            // newNode. Finally, we update tail to point to newNode.
        } else if ((pixel - 1) % width == 0)
        {
            // Pointer below the newNode (which head_row points at) has its up pointer set to newNode and newNode's down
            // pointer set to head_row (Node below it).
            head_row->up = newNode;
            newNode->down = head_row;

            // Linker is set to head_row so it jumps from the uttermost right position of the row below head_row, or the row
            // 2 lines below newNode.
            linker = head_row;

            // head_row and tail are updated, head_row points to the first node of the new row, which is newNode, while tail
            // points to the last node placed, which is newNode also hehe siuuu.
            head_row = newNode;
            tail = newNode;

            // If the mesh is not empty (head_row != nullptr) AND we're not in the first row (row != 0) AND the pixel is
            // not a pixel of the first column ((pixel - 1) % width != 0). We place the newNode to the right of the
            // last node placed which tail points at.
        } else if (row == 0)
        {
            newNode->left = tail;
            newNode->left->right = newNode;
            tail = newNode;

            // If mesh is not empty (head_row != nullptr) if statement checking if newNode corresponds to a pixel of the
            // uttermost left column. If it's a pixel of that column, it's no longer placed at the right of the tail,
            // but at top of the head_row.
        } else
        {
            // newNode's left pointer set to point to the last pixel placed (which tail points at).
            newNode->left = tail;
            // The node tail points at has its right pointer set to newNode.
            newNode->left->right = newNode;

            // The linker is moved to point to the pixel below newNode.
            linker = linker->right;

            // The pixel below newNode points at it.
            // newNode->left->down->right->up = newNode;
            linker->up = newNode;
            // newNode's down pointer points at the pixel below it.
            newNode->down = linker;

            // Tail is set to point at newNode, the last pixel placed.
            tail = newNode;
        }
        // Pixel counter is updated.
        pixel++;
    }

    // Prints total execution time.
    if (t) Console::printTime(timer.stop(), "Creating DaPlace");
}

// Travels the entire Mesh in a counterclockwise spiral right->up->left->down checking if Pixels are the same as the
// User's Pixel and returns a pointerStack with pointers to the Pixels to later change them.
pointerStack nodeMesh::searchPixels(Pixel pTarget)
{
    // Initializes timer.
    Timer timer;
    timer.start();

    int count{};

    // Initializes a pointerStack.
    pointerStack pStack;

    // Sets a temporal pointer 'current' to origin to start the search.
    Node *current = origin;

    // Checks first if origin's Pixel = User Pixel.
    current->isVisited = true;
    if (current->p == pTarget)
    {
        Pixel *pPixel = &current->p;
        pStack.push(pPixel);
        count++;
    }
    // Checks bottom border left to right.
    while (current->right != nullptr)
    {
        current = current->right;
        current->isVisited = true;
        if (current->p == pTarget)
        {
            Pixel *pPixel = &current->p;
            pStack.push(pPixel);
            count++;
        }
    }
    // Checks right border bottom to up.
    while (current->up != nullptr)
    {
        current = current->up;
        current->isVisited = true;
        if (current->p == pTarget)
        {
            Pixel *pPixel = &current->p;
            pStack.push(pPixel);
            count++;
        }
    }
    // Checks top border right to left.
    while (current->left != nullptr)
    {
        current = current->left;
        current->isVisited = true;
        if (current->p == pTarget)
        {
            Pixel *pPixel = &current->p;
            pStack.push(pPixel);
            count++;
        }
    }

    // Now checking for nullptr can no longer be used as we've checked the borders. Therefore, we're checking if the
    // node in front was visited.
    while (continueTraversing(current))
    {
        // Checks up to bottom.
        while (!current->down->isVisited)
        {
            current = current->down;
            current->isVisited = true;
            if (current->p == pTarget)
            {
                Pixel *pPixel = &current->p;
                pStack.push(pPixel);
                count++;
            }
        }
        // Checks left to right.
        while (!current->right->isVisited)
        {
            current = current->right;
            current->isVisited = true;
            if (current->p == pTarget)
            {
                Pixel *pPixel = &current->p;
                pStack.push(pPixel);
                count++;
            }
        }
        // Checks bottom to up.
        while (!current->up->isVisited)
        {
            current = current->up;
            current->isVisited = true;
            if (current->p == pTarget)
            {
                Pixel *pPixel = &current->p;
                pStack.push(pPixel);
                count++;
            }
        }
        // Checks right to left.
        while (!current->left->isVisited)
        {
            current = current->left;
            current->isVisited = true;
            if (current->p == pTarget)
            {
                Pixel *pPixel = &current->p;
                pStack.push(pPixel);
                count++;
            }
        }
    }
    // Prints time to filter the Mesh.
    Console::printTime(timer.stop(), "Creating filtered list of Mesh");

    if (count >= 100)
    {
        pStack.print100();
        std::cout << "\n\n" << count << " found. Printed last 100.";
    } else
    {
        pStack.print();
        std::cout << "\n\n" << count << " found.";
    }

    // Returns pointerStack structure.
    return pStack;
}

// Returns true if there are any pixels not visited around the current Pixel, else false (search ends).
bool nodeMesh::continueTraversing(nodeMesh::Node *current)
{
    return (!current->right->isVisited || !current->down->isVisited || !current->left->isVisited ||
            !current->up->isVisited);
}

// Writes the Mesh's data to a memory block to later save as an image.
unsigned char *nodeMesh::dataToMem(ImageBMP img)
{
    unsigned char *image = (unsigned char *) malloc(sizeof(unsigned char) * (img.getWidth() * img.getHeight()) * 3);

    int pixel_number{};
    Node *head_row = origin->up;

    while (origin != nullptr)
    {
        Node *temp = origin;
        Pixel p = temp->p;

        *(image + pixel_number * 3 + 0) = p.getBlue();
        *(image + pixel_number * 3 + 1) = p.getGreen();
        *(image + pixel_number * 3 + 2) = p.getRed();

        pixel_number++;

        if (origin->right != nullptr) origin = origin->right;
        else if (head_row != nullptr)
        {
            origin = head_row;
            head_row = origin->up;
        } else
        {
            origin = nullptr;
        }

        delete temp;
    }
    return image;
}

// Mirrors the image.
void nodeMesh::mirrorImage()
{
    Timer timer;
    timer.start();

    Node *diagonal = tail;
    Node *horizontal;
    Node *vertical;

    if (this->tail->p.getX() > this->tail->p.getY())
    {
        while (diagonal->p.getX() != diagonal->p.getY())
        {
            diagonal = diagonal->left;
        }
    }

    // Move towards bottom-left corner while changing every pixel-pair.
    while (diagonal->left != nullptr)
    {
        horizontal = diagonal->left;
        vertical = diagonal->down;

        vertical->p = horizontal->p;

        while (horizontal->left != nullptr)
        {
            horizontal = horizontal->left;
            vertical = vertical->down;

            vertical->p = horizontal->p;
        }

        diagonal = diagonal->left->down;
    }

    Console::printTime(timer.stop(), "Mirroring the Mesh");
}

// Computes the average of pixel-pairs using the bottom-left top-right diagonal just like mirrorImage();
double nodeMesh::averageMirror()
{

    double total{};
    int total_pixel_pairs{};

    Node *diagonal = tail;
    Node *horizontal;
    Node *vertical;

    if (this->tail->p.getX() > this->tail->p.getY())
    {
        while (diagonal->p.getX() != diagonal->p.getY())
        {
            diagonal = diagonal->left;
        }
    }

    while (diagonal->left != nullptr)
    {
        horizontal = diagonal->left;
        vertical = diagonal->down;

        total += (abs(vertical->p.getRed() - horizontal->p.getRed()) + abs(vertical->p.getGreen() - horizontal->p
                .getGreen()) + abs(vertical->p.getBlue() - horizontal->p.getBlue())) / 3.0;

        total_pixel_pairs += 1;

        while (horizontal->left != nullptr)
        {
            horizontal = horizontal->left;
            vertical = vertical->down;

            total +=
                    (abs(vertical->p.getRed() - horizontal->p.getRed()) + abs(vertical->p.getGreen() - horizontal->p
                            .getGreen()) + abs(vertical->p.getBlue() - horizontal->p.getBlue())) / 3.0;

            total_pixel_pairs += 1;
        }

        diagonal = diagonal->left->down;
    }

    std::cout << "Total Number of Pixels: " << total_pixel_pairs * 2 << std::endl;
    std::cout << "Total pair of Pixels: " << total_pixel_pairs << std::endl;
    std::cout << "Average of all Pixel pairs: " << total / total_pixel_pairs << std::endl;

    double average_total = total / total_pixel_pairs;
    return average_total;
}
