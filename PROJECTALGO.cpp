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
    for (char ch : name) {
        if (isdigit(ch)) {
            return false;  // Name contains a digit, invalid
        }
    }
    return true;  // Name is valid (contains no digits)
}

// Function to validate if a string contains only letters and spaces (no numbers)
bool isValidRole(const string& role) {
    for (char ch : role) {
        if (isdigit(ch)) {
            return false;  // Role contains a digit, invalid
        }
    }
    return true;  // Role is valid (contains no digits)
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

    cin.ignore();  // Clear newline from input buffer

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
    getline(cin, emp->name);
    if (!isValidName(emp->name)) {
        cout << "Error: Employee name cannot contain numbers!" << endl;
        delete emp;  // Free allocated memory if invalid input
        return;
    }

    // Validate employee role (no numbers allowed)
    cout << "Enter Role: ";
    getline(cin, emp->role);
    if (!isValidRole(emp->role)) {
        cout << "Error: Employee role cannot contain numbers!" << endl;
        delete emp;  // Free allocated memory if invalid input
        return;
    }

    cout << "Enter Salary: ";
    cin >> emp->salary;
    cout << "Enter Tax Rate (as decimal): ";
    cin >> emp->taxRate;

    // Validate salary and tax rate
    if (emp->salary < 0 || emp->taxRate < 0 || emp->taxRate > 1) {
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

            if (newSalary < 0) {
                cout << "Error: Invalid Salary!" << endl;
                return;
            }

            current->salary = newSalary;
            cout << "Salary updated successfully!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Employee with ID " << id << " not found!" << endl;
}

// Function to update the employee's name and tax rate
void updateEmployeeNameAndTax() {
    int id;
    string newName;
    double newTaxRate;

    cout << "Enter Employee ID to update name and tax rate: ";
    cin >> id;
    cin.ignore();  // Clear newline from input buffer

    // Validate employee ID
    if (!isValidID(id)) {
        cout << "Error: Invalid Employee ID!" << endl;
        return;
    }

    Employee* current = head;
    while (current != NULL) {
        if (current->employeeID == id) {
            cout << "Current Name: " << current->name << endl;
            cout << "Enter new Name: ";
            getline(cin, newName);

            // Validate name (no numbers allowed)
            if (!isValidName(newName)) {
                cout << "Error: Employee name cannot contain numbers!" << endl;
                return;
            }

            cout << "Current Tax Rate: " << current->taxRate << endl;
            cout << "Enter new Tax Rate (as decimal): ";
            cin >> newTaxRate;

            // Validate tax rate
            if (newTaxRate < 0 || newTaxRate > 1) {
                cout << "Error: Invalid tax rate!" << endl;
                return;
            }

            current->name = newName;
            current->taxRate = newTaxRate;
            cout << "Name and Tax Rate updated successfully!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Employee with ID " << id << " not found!" << endl;
}

int main() {
    int choice;

    while (true) {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Generate Payslips\n";
        cout << "3. Update Employee Salary\n";
        cout << "4. Update Employee Name and Tax Rate\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                generatePayslips();
                break;
            case 3:
                updateEmployeeSalary();
                break;
            case 4:
                updateEmployeeNameAndTax();
                break;
            case 5:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
