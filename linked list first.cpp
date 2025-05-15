#include <iostream>
#include <cstdlib> // For system("cls")
using namespace std;

// Define the Student structure
struct Student {
    int ID;
    char name[30];
    Student* next;
} *start = NULL;
	Student*last=NULL;

// Function prototypes
void insert_big();
void insert_end();
void del_big();
void del_end();
void display();
void search_by_id();

int main() {
    char exit_flag = 'n';
    do {
        system("cls"); // Clear the screen
        int choice = 0;

        cout << "\t1) Insert at the beginning\n";
        cout << "\t2) Insert at the end\n";
        cout << "\t3) Delete at the beginning\n";
        cout << "\t4) Delete at the end\n";
        cout << "\t5) Display\n";
        cout << "\t6) Search by ID\n";
        cout << "\t7) Exit\n";
        cout << "\n\tPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insert_big();
                break;
            case 2:
                insert_end();
                break;
            case 3:
                del_big();
                break;
            case 4:
                del_end();
                break;
            case 5:
                display();
                break;
            case 6:
                search_by_id();
                break;
            case 7:
                exit_flag = 'y';
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
                cin.ignore();
                cin.get();
        }
    } while (exit_flag != 'y');

    return 0;
}

// Insert at the beginning
void insert_big() {
    Student* temp = new Student;
    cout << "Please enter student ID: ";
    cin >> temp->ID;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(temp->name, 30);
    temp->next = start;
    start = temp;
}

// Insert at the end
void insert_end() {

    Student* temp = new Student;
    cout << "Please enter student ID: ";
    cin >> temp->ID;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(temp->name, 30);
    temp->next = NULL;

    if (start == NULL) {
        last=start = temp;
    } else {
    	last->next=temp;
    	last=temp;
        
    }
}

// Delete at the beginning
void del_big() {
    if (start == NULL) {
        cout << "The list is empty.\n";
    } else {
        Student* temp = start;
        start = start->next;
        cout << "Deleted student with ID: " << temp->ID << "\n";
        delete temp;
    }
    cin.ignore();
    cin.get();
}

// Delete at the end
void del_end() {
    if (start == NULL) {
        cout << "The list is empty.\n";
    } else if (start->next == NULL) {
        cout << "Deleted student with ID: " << start->ID << "\n";
        delete start;
        start =last= NULL;
    } else {
        Student* ptr = start;
        while (ptr->next->next != NULL) {
            ptr = ptr->next;
        }
        cout << "Deleted student with ID: " << ptr->next->ID << "\n";
        delete ptr->next;
        ptr->next = NULL;
        last = ptr;
    }
    cin.ignore();
    cin.get();
}

// Display the list
void display() {
    if (start == NULL) {
        cout << "The list is empty.\n";
    } else {
        cout << "ID\tName\n";
        cout << "====================\n";
        Student* ptr = start;
        while (ptr != NULL) {
            cout << ptr->ID << "\t" << ptr->name << "\n";
            ptr = ptr->next;
        }
    }
    cin.ignore();
    cin.get();
}

// Search by ID
void search_by_id() {
    if (start == NULL) {
        cout << "The list is empty.\n";
    } else {
        int search_id;
        cout << "Enter the ID to search: ";
        cin >> search_id;

        Student* ptr = start;
        while (ptr != NULL) {
            if (ptr->ID == search_id) {
                cout << "Student found:\n";
                cout << "ID: " << ptr->ID << "\n";
                cout << "Name: " << ptr->name << "\n";
                cin.ignore();
                cin.get();
                return;
            }
            ptr = ptr->next;
        }
        cout << "Student with ID " << search_id << " not found.\n";
    }
    cin.ignore();
    cin.get();
}
