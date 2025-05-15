#include <iostream>
using namespace std;


int LinearSearch(int list[], int n, int key) {
    int index = -1; 
    for (int i = 0; i < n; i++) {
        if (list[i] == key) {
            index = i;
            break;    
        }
    }
    return index;
}

int main() {
    int n;


    cout << "Enter the size of the array: ";
    cin >> n;

  
    int list[n];

    
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> list[i];
    }

    int key;
    
    cout << "Enter the key to search: ";
    cin >> key;


    int result = LinearSearch(list, n, key);

    
    if (result != -1) {
        cout << "Key found at index: " << result << endl;
    } else {
        cout << "Key not found in the array." << endl;
    }

    return 0;
}
