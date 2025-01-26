#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const string DATABASE_FILE = "employees.txt";

struct Employee {
    int employeeID;
    string name;
    string role;
    double salary;
    double taxRate;
};

// Function to add a new employee and save to file
void addEmployee() {
    ifstream infile(DATABASE_FILE.c_str()); // For reading from the file
ofstream outfile(DATABASE_FILE.c_str(), ios::app); // For writing in append mode

    if (!outfile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.employeeID;
    cin.ignore(); // Ignore remaining newline
    cout << "Enter Name: ";
    getline(cin, emp.name);
    cout << "Enter Role: ";
    getline(cin, emp.role);
    cout << "Enter Salary: ";
    cin >> emp.salary;
    cout << "Enter Tax Rate (as decimal): ";
    cin >> emp.taxRate;

    // Write employee details to the file
    outfile << emp.employeeID << "\n"
            << emp.name << "\n"
            << emp.role << "\n"
            << emp.salary << "\n"
            << emp.taxRate << "\n";

    outfile.close();
    cout << "Employee added successfully!" << endl;
}

// Function to generate payslips for all employees
void generatePayslips() {
    ifstream infile(DATABASE_FILE.c_str()); // For reading from the file
ofstream outfile(DATABASE_FILE.c_str(), ios::app); // For writing in append mode

    if (!infile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    Employee emp;
    cout << fixed << setprecision(2);

    while (infile >> emp.employeeID) {
        infile.ignore(); // Ignore newline
        getline(infile, emp.name);
        getline(infile, emp.role);
        infile >> emp.salary >> emp.taxRate;

        double netSalary = emp.salary - (emp.salary * emp.taxRate);
        cout << "Payslip for " << emp.name 
             << " (ID: " << emp.employeeID << ")" << endl;
        cout << "Role: " << emp.role << endl;
        cout << "Gross Salary: $" << emp.salary << endl;
        cout << "Net Salary after Tax: $" << netSalary << "\n" << endl;
    }

    infile.close();
}

// Function to update an employee's salary in the file
void updateEmployeeSalary() {
   ifstream infile(DATABASE_FILE.c_str()); // For reading from the file
ofstream outfile(DATABASE_FILE.c_str(), ios::app); // For writing in append mode

    if (!infile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    ofstream tempFile("temp.txt"); // Temporary file for updated records
    if (!tempFile) {
        cerr << "Error opening temporary file for writing!" << endl;
        return;
    }

    int id;
    double newSalary;
    cout << "Enter Employee ID to update salary: ";
    cin >> id;
    cout << "Enter new Salary: ";
    cin >> newSalary;

    Employee emp;
    bool found = false;

    while (infile >> emp.employeeID) {
        infile.ignore(); // Ignore newline
        getline(infile, emp.name);
        getline(infile, emp.role);
        infile >> emp.salary >> emp.taxRate;

        if (emp.employeeID == id) {
            emp.salary = newSalary; // Update salary
            found = true;
        }

        // Write employee details to the temporary file
        tempFile << emp.employeeID << "\n"
                 << emp.name << "\n"
                 << emp.role << "\n"
                 << emp.salary << "\n"
                 << emp.taxRate << "\n";
    }

    infile.close();
    tempFile.close();

    if (found) {
        remove(DATABASE_FILE.c_str());            // Delete the original file
        rename("temp.txt", DATABASE_FILE.c_str()); // Rename temporary file
        cout << "Salary updated successfully!" << endl;
    } else {
        remove("temp.txt"); // Remove temp file if no changes
        cout << "Employee not found!" << endl;
    }
}

// Authenticate the user
bool authenticateUser() {
    string password;
    cout << "Enter the password to access the Payroll System: ";
    cin >> password;

    return password == "admin123"; // Simple password authentication
}

// Display the menu
void displayMenu() {
    int choice;

    do {
        cout << "\nPayroll System Menu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Generate Payslips\n";
        cout << "3. Update Employee Salary\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
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
                cout << "Exiting Payroll System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);
}

int main() {
    if (!authenticateUser()) {
        cout << "Authentication failed! Exiting." << endl;
        return 1;
    }

    displayMenu();
    return 0;
}
