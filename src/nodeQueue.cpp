#include "nodeQueue.hpp"
#include "Timer.hpp"
#include "Console.hpp"

// nodeQueue constructor. Initializes head and tail as nullptr.
nodeQueue::nodeQueue()
{
    head = nullptr;
    tail = nullptr;
};

// Adds an element to the back of the Queue using the HEAD pointer.
void nodeQueue::enqueue(Pixel p)
{
    // New Node is created with Pixel object and a pointer to it.
    Node *newNode = new Node(p);

    // If the nodeQueue is empty (head = nullptr) then it sets the head and the tail to the newNode, which happens to
    // be the first Node of the Queue.
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;

        // Else if the nodeQueue is not emtpy, that means head must be pointing at a Node which has a next pointer
        // that points to nullptr, because it is the last one at the back of the queue. Therefore, the Node head
        // points at must set its next pointer to newNode.
    } else
    {
        head->next = newNode;
        head = newNode;
    }
}

// Returns the Pixel object from the Node at the front of the Queue whilst removing it.
Pixel nodeQueue::dequeue()
{
    // If nodeQueue is empty (head = nullptr) it prints a message.
    if (head == nullptr)
    {
        std::cout << "Queue is empty!";

        // Else it creates a temp pointer to point at the Node Tail points at. We must use it for the same reason we
        // use it in the nodeStack implementation. It is necessary otherwise we have to either choose to first move
        // the Tail pointer and then delete its previous Node which is impossible as we don't have anything to point
        // to it, or we must delete the Node, but then we wouldn't have a next pointer to use to update Tail.
    } else
    {
        // New temp pointer set to Tail's Node.
        Node *temp = tail;

        // The Pixel is retrieved from temp/tail (both pointers point at the same Node at time of execution).
        Pixel p = temp->p;

        // Tail is updated to point to the second Node from the front.
        tail = tail->next;

        // If tail = nullptr after updating it, that means the last Node of the nodeQueue (and also first Node from
        // the back) was just dequeued, which also means that Head is pointing to a Node that does not exist anymore,
        // therefore we must update it.
        if (tail == nullptr) head = nullptr;

        // Finally the Node temp points at is deleted.
        delete temp;

        // The Pixel object is returned.
        return p;
    }
}

// Returns true if nodeQueue is empty (head = nullptr), else it returns false.
bool nodeQueue::isEmpty()
{
    return head == nullptr;
}

// Prints the entire Queue, one by one.
void nodeQueue::print()
{
    // If nodeQueue is empty (head = nullptr) it prints a message.
    if (head == nullptr)
    {
        std::cout << "Queue is empty!";

        // Else it creates a temporary pointer to traverse the Queue.
    } else
    {
        // Temporary pointer set to tail.
        Node *current = tail;

        // While current hasn't reached the back of the Queue and jumped over the last element (current = nullptr),
        // it prints current's Node's Pixel. After, it updates to point to the next Node.
        while (current != nullptr)
        {
            std::cout << current->p;
            current = current->next;
        }
    }
}

// Creates an exact copy of the target queue.
nodeQueue nodeQueue::clone(bool t)
{
    // Initializes timer.
    Timer timer;
    timer.start();

    // A nodeQueue object is initialized.
    nodeQueue copiedQueue;

    // A pointer which points at the Node Tail points at is created (The Node at the very front of the Queue and
    // first one ready to remove).
    Node *copyNode = this->tail;

    // While the pointer hasn't reached the back of the queue and jumped over the last Node (copyNode = nullptr), the
    // data portion, the Pixel, of every Node copyNode points at is extracted and enqueued in the clone_deprecated nodeQueue, so
    // a new Node is constructed holding equivalent data. After that the pointer is updated.
    while (copyNode != nullptr)
    {
        // Pixel from each Node in original queue is enqueued in cloned queue.
        copiedQueue.enqueue(copyNode->p);

        // The pointer is updated.
        copyNode = copyNode->next;
    }
    // Prints total execution time.
    if (t) Console::printTime(timer.stop(), "Creating  DaList");

    // The copied queue is returned.
    return copiedQueue;
}

// Clones a queue.
void nodeQueue::clone(nodeQueue *original, nodeQueue *clone)
{
    // A temp queue in the heap is created for which we need a pointer to.
    nodeQueue *temp = new nodeQueue;

    // While the original queue is not empty, we remove each element and append them in the temp queue.
    while (!original->isEmpty())
    {
        temp->enqueue(original->dequeue());
    }

    // After that, we remove each element in the temp queue extracting the data, Pixel object in this case in a temporary variable,
    // which we will append to restore back the original and to create the cloned queue.
    while (!temp->isEmpty())
    {
        Pixel current = temp->dequeue();
        original->enqueue(current);
        clone->enqueue(current);
    }
    // Delete the temporary queue in the heap.
    delete temp;
}

void nodeQueue::makeNull()
{
    while (!isEmpty())
    {
        dequeue();
    }
}
