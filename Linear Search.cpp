#include <iostream>
using namespace std;

// Function to perform linear search
int LinearSearch(int list[], int n, int key) {
    int index = -1; // Initialize the index to -1
    for (int i = 0; i < n; i++) {
        if (list[i] == key) {
            index = i; // Update index if key is found
            break;     // Exit the loop after finding the key
        }
    }
    return index;
}

int main() {
    int n;

    // Accept array size from the user
    cout << "Enter the size of the array: ";
    cin >> n;

    // Declare the array
    int list[n];

    // Accept array elements from the user
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> list[i];
    }

    int key;
    // Accept the key to search for
    cout << "Enter the key to search: ";
    cin >> key;

    // Call the LinearSearch function
    int result = LinearSearch(list, n, key);

    // Print the result
    if (result != -1) {
        cout << "Key found at index: " << result << endl;
    } else {
        cout << "Key not found in the array." << endl;
    }

    return 0;
}
