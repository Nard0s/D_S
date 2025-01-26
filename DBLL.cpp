#include <iostream>
using namespace std;

struct Node {
    Node* prev; // Pointer to the previous node
    int data;   // Data part
    Node* next; // Pointer to the next node
} *first = NULL;

void create(int A[], int n) {
    Node* t, *last;

    // Create the first node
    first = new Node;
    first->prev = NULL;
    first->data = A[0];
    first->next = NULL;
    last = first;

    // Create the remaining nodes
    for (int i = 1; i < n; i++) {
        t = new Node; // Allocate memory for a new node
        t->data = A[i];
        t->next = NULL;
        t->prev = last;    // Link the new node to the last node
        last->next = t;    // Link the last node to the new node
        last = t;          // Move the last pointer to the new node
    }
}

void Display(Node* p) {
    while (p) {
        cout << p->data << " "; // Print the data of the current node
        p = p->next;           // Move to the next node
    }
    cout << endl;
}

int main() {
    int A[] = {1, 2, 3, 4, 5}; // Input array
    int n = sizeof(A) / sizeof(A[0]); // Calculate the number of elements in the array

    create(A, n); // Create the doubly linked list
    cout << "==================" << endl;
    cout << "List: ";
    Display(first); // Display the doubly linked list
    return 0;
}
