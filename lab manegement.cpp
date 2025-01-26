#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>  // For checking characters

using namespace std;

// Employee struct to represent an employee
struct Employee {
    int employeeID;
    string name;
    string role;
    double salary;
    double taxRate;
    Employee* next;  // Pointer to the next employee in the linked list
};

// Head pointer to the linked list
Employee* head = NULL;  // Initialize head as NULL

// Function to validate if a string contains only letters (no numbers)
bool isValidName(const string& name) {
    for (char chname) {
        if (isdigit(ch)) {
            return false;  // Name contains a digit, invalid
        }
    }
    return true;  // Name is valid (contains no digits)
}

// Function to validate if the ID is a valid number
bool isValidID(int id) {
    return id >= 0;  // ID should be non-negative
}

// Function to add an employee to the linked list
void addEmployee() {
    Employee* emp = new Employee();  // Dynamically allocate memory for a new employee

    // Validate employee ID
    cout << "Enter Employee ID: ";
    cin >> emp->employeeID;

    // Check for valid ID
    if (!isValidID(emp->employeeID)) {
        cout << "Error: Invalid Employee ID!" << endl;
        delete emp;  // Free allocated memory if invalid input
        return;
    }

    cin.ignore();  // Clear newline from input buffer after employee ID input

    // Check for duplicate IDs
    Employee* current = head;
    while (current != NULL) {
        if (current->employeeID == emp->employeeID) {
            cout << "Error: Employee ID already exists!" << endl;
            delete emp;  // Free allocated memory for the duplicate employee
            return;
        }
        current = current->next;
    }

    // Validate employee name (no numbers allowed)
    cout << "Enter Name: ";
    getline(cin, emp->name);  // Get the name input from the user
    if (!isValidName(emp->name)) {
        cout << "Error: Employee name cannot contain numbers!" << endl;
        delete emp;  // Free allocated memory if invalid input
        return;
    }

    cout << "Enter Role: ";
    getline(cin, emp->role);  // Get the role input from the user
    cout << "Enter Salary: ";
    cin >> emp->salary;
    cout << "Enter Tax Rate (as decimal): ";
    cin >> emp->taxRate;

    // Validate salary and tax rate
    if (emp->salary < 0  emp->taxRate < 0   emp->taxRate > 1) {
        cout << "Error: Invalid salary or tax rate." << endl;
        delete emp;  // Free allocated memory if invalid input
        return;
    }

    // Insert the employee at the beginning of the list (could be done at the end as well)
    emp->next = head;
    head = emp;  // Now head points to the new employee

    cout << "Employee added successfully!" << endl;
}

// Function to display payslips of all employees
void generatePayslips() {
    cout << fixed << setprecision(2);
    Employee* current = head;
    while (current != NULL) {
        double netSalary = current->salary - (current->salary * current->taxRate);
        cout << "\nPayslip for " << current->name
             << " (ID: " << current->employeeID << ")" << endl;
        cout << "Role: " << current->role << endl;
        cout << "Gross Salary: $" << current->salary << endl;
        cout << "Net Salary after Tax: $" << netSalary << endl;
        current = current->next;  // Move to the next employee
    }
}

// Function to update the salary of an employee
void updateEmployeeSalary() {
    int id;
    double newSalary;

    cout << "Enter Employee ID to update salary: ";
    cin >> id;

    // Validate employee ID
    if (!isValidID(id)) {
        cout << "Error: Invalid Employee ID!" << endl;
        return;
    }

    Employee* current = head;
    while (current != NULL) {
        if (current->employeeID == id) {
            cout << "Current Salary: $" << current->salary << endl;
            cout << "Enter new Salary: ";
            cin >> newSalary;