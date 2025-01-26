#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int MAX_EMPLOYEES = 100;
const string DATABASE_FILE = "employees.txt";

struct Employee {
    int employeeID;
    string name;
    string role;
    double salary;
    double taxRate;
};

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

void loadDatabase() {
    ifstream infile(DATABASE_FILE);
    if (!infile) {
        cout << "Database file not found. Starting fresh." << endl;
        return;
    }

    while (infile >> employees[employeeCount].employeeID) {
        infile.ignore(); // Ignore newline
        getline(infile, employees[employeeCount].name);
        getline(infile, employees[employeeCount].role);
        infile >> employees[employeeCount].salary >> employees[employeeCount].taxRate;
        employeeCount++;
    }
    infile.close();
}

void saveDatabase() {
    ofstream outfile(DATABASE_FILE);
    for (int i = 0; i < employeeCount; ++i) {
        outfile << employees[i].employeeID << endl;
        outfile << employees[i].name << endl;
        outfile << employees[i].role << endl;
        outfile << employees[i].salary << endl;
        outfile << employees[i].taxRate << endl;
    }
    outfile.close();
}

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee limit reached!" << endl;
        return;
    }

    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.employeeID;
    cin.ignore(); // Clear newline from input buffer
    cout << "Enter Name: ";
    getline(cin, emp.name);
    cout << "Enter Role: ";
    getline(cin, emp.role);
    cout << "Enter Salary: ";
    cin >> emp.salary;
    cout << "Enter Tax Rate (as decimal): ";
    cin >> emp.taxRate;

    employees[employeeCount++] = emp;
    saveDatabase(); // Save to database after adding
    cout << "Employee added successfully!" << endl;
}

void generatePayslips() {
    cout << fixed << setprecision(2);
    
    for (int i = 0; i < employeeCount; ++i) {
        double netSalary = employees[i].salary - (employees[i].salary * employees[i].taxRate);
        cout << "Payslip for " << employees[i].name 
             << " (ID: " << employees[i].employeeID << ")" << endl;
        cout << "Role: " << employees[i].role << endl;
        cout << "Gross Salary: $" << employees[i].salary << endl;
        cout << "Net Salary after Tax: $" << netSalary << "\n" << endl;
    }
}

void updateEmployeeSalary() {
    int id;
    double newSalary;

    cout << "Enter Employee ID to update salary: ";
    cin >> id;

    for (int i = 0; i < employeeCount; ++i) {
        if (employees[i].employeeID == id) {
            cout << "Current Salary: $" << employees[i].salary << "\n";
            cout << "Enter new Salary: ";
            cin >> newSalary;
            employees[i].salary = newSalary;
            saveDatabase(); // Save to database after updating
            cout << "Salary updated successfully!" << endl;
            return;
        }
    }
    
    cout << "Employee not found!" << endl;
}

bool authenticateUser() {
    string password;

    cout << "Enter the password to access the Payroll System: ";
    cin >> password;

    // Simple password check
    return password == "admin123"; // Change this password as needed
}

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
                break; // Exit
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);
}
int main() {
    if (!authenticateUser()) {
        cout << "Authentication failed! Exiting." << endl;
        return 1; // Exit if authentication fails
    }

    loadDatabase(); // Load existing employee data from file
    displayMenu();
    
    return 0;
}