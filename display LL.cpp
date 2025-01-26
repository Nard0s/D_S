
#include <iostream>
using namespace std;

// Define a Node structure
struct Node {
    int data;       // Data part
    Node* next;     // Pointer to the next node
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node(); // Allocate memory for a new node
    newNode->data = data;       // Set the data
    newNode->next = NULL;       // Initialize the next pointer to NULL
    return newNode;
}

// Function to display the linked list
void displayList(Node* head) {
    Node* current = head; // Start from the head node
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->next; // Move to the next node
    }
    cout << "NULL" << endl; // End of the list
}

int main() {
    // Create nodes
    Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);

    // Display the linked list
    cout << "Linked List: ";
    displayList(head);

    // Free the allocated memory
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
