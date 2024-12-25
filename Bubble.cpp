#include <iostream>
using namespace std;

// Function to swap two integers
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to perform Bubble Sort on an array
void Bubble(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
}

int main() {
    int A[] = {1, 2, 6, 71, 8, 9, 5, 4, 33, 10};
    int n = 10;

    // Call Bubble Sort
    Bubble(A, n);

    // Print the sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}