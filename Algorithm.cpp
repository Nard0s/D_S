#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>

#include "sqlite3.h"

using namespace std;

struct Employee {
    string id;
    string name;
    string role;
    double grossSalary;
    double taxRate;
    double netSalary;
    Employee* next;
};

Employee* head = NULL;

bool isAlphabetic(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return false;
        }
    }
    return true;
}

bool isNumeric(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i]) && str[i] != '.') {
            return false;
        }
    }
    return true;
}

bool isUniqueID(const string& id) {
    Employee* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

bool isAlphanumeric(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isalnum(str[i])) {
            return false;
        }
    }
    return true;
}

double stringToDouble(const string& str) {
    stringstream ss(str);
    double result;
    ss >> result;
    return result;
}

void calculateNetSalary(Employee* emp) {
    emp->netSalary = emp->grossSalary - (emp->grossSalary * emp->taxRate / 100);
}

// Function to save data to SQLite database
void saveData() {
    sqlite3* db;
    int rc = sqlite3_open("payroll.db", &db); // Corrected to use the same database file
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return;
    }
    // Create table if it doesn't exist
    string sql = "CREATE TABLE IF NOT EXISTS Employees ("
                 "ID TEXT PRIMARY KEY,"
                 "Name TEXT,"
                 "Role TEXT,"
                 "GrossSalary REAL,"
                 "TaxRate REAL,"
                 "NetSalary REAL);";
    char* errMsg;
    rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }

    // Insert employee data into table
    Employee* temp = head;
    while (temp != NULL) {
        sql = "INSERT OR REPLACE INTO Employees (ID, Name, Role, GrossSalary, TaxRate, NetSalary) VALUES ('" +
              temp->id + "', '" + temp->name + "', '" + temp->role + "', " + to_string(temp->grossSalary) + ", " +
              to_string(temp->taxRate) + ", " + to_string(temp->netSalary) + ");";
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << errMsg << endl;
            sqlite3_free(errMsg);
        }
        temp = temp->next;
    }

    sqlite3_close(db);
    cout << "Data saved successfully!\n";
}

// Function to load data from SQLite database
void loadData() {
    sqlite3* db;
    int rc = sqlite3_open("payroll.db", &db); // Corrected to use the same database file
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string sql = "SELECT * FROM Employees;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Employee* newEmployee = new Employee();
        newEmployee->id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        newEmployee->name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        newEmployee->role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        newEmployee->grossSalary = sqlite3_column_double(stmt, 3);
        newEmployee->taxRate = sqlite3_column_double(stmt, 4);
        newEmployee->netSalary = sqlite3_column_double(stmt, 5);
        newEmployee->next = head;
        head = newEmployee;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    cout << "Data loaded successfully!\n";
}

void addEmployee() {
    Employee* newEmployee = new Employee();
    do {
        cout << "Enter Employee ID (alphanumeric): ";
        cin >> newEmployee->id;
        if (!isAlphanumeric(newEmployee->id)) {
            cout << "Invalid input! Employee ID must contain only alphanumeric characters.\n";
        } else if (!isUniqueID(newEmployee->id)) {
            cout << "ID already exists! Please enter another Employee ID.\n";
        }
    } while (!isAlphanumeric(newEmployee->id) || !isUniqueID(newEmployee->id));

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clearing the input buffer

    do {
        cout << "Enter Employee Name: ";
        getline(cin, newEmployee->name);
        if (!isAlphabetic(newEmployee->name)) {
            cout << "Invalid input! Name must contain only alphabetic characters.\n";
        }
    } while (!isAlphabetic(newEmployee->name));

    do {
        cout << "Enter Employee Role: ";
        getline(cin, newEmployee->role);
        if (!isAlphabetic(newEmployee->role)) {
            cout << "Invalid input! Role must contain only alphabetic characters.\n";
        }
    } while (!isAlphabetic(newEmployee->role));

    string grossSalaryStr;
    do {
        cout << "Enter Employee Gross Salary: ";
        cin >> grossSalaryStr;
        if (!isNumeric(grossSalaryStr)) {
            cout << "Invalid input! Gross Salary must be a numeric value.\n";
        }
    } while (!isNumeric(grossSalaryStr));
    newEmployee->grossSalary = stringToDouble(grossSalaryStr);

    string taxRateStr;
    do {
        cout << "Enter Employee Tax Rate (%): ";
        cin >> taxRateStr;
        if (!isNumeric(taxRateStr)) {
            cout << "Invalid input! Tax Rate must be a numeric value.\n";
        }
    } while (!isNumeric(taxRateStr));
    newEmployee->taxRate = stringToDouble(taxRateStr);

    calculateNetSalary(newEmployee);
    newEmployee->next = head;
    head = newEmployee;
    cout << "Employee added successfully!\n";
}

void displayEmployees() {
    Employee* temp = head;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "Role" << setw(15) << "Gross Salary" << setw(10) << "Tax Rate" << setw(10) << "Net Salary" << endl;
    while (temp != NULL) {
        cout << left << setw(10) << temp->id << setw(20) << temp->name << setw(20) << temp->role << setw(15) << temp->grossSalary << setw(10) << temp->taxRate << setw(10) << temp->netSalary << endl;
        temp = temp->next;
    }
}

void modifyEmployee() {
    string id;
    cout << "Enter Employee ID to modify: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clearing the input buffer
    Employee* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            do {
                cout << "Enter new name: ";
                getline(cin, temp->name);
                if (!isAlphabetic(temp->name)) {
                    cout << "Invalid input! Name must contain only alphabetic characters.\n";
                }
            } while (!isAlphabetic(temp->name));

            do {
                cout << "Enter new role: ";
                getline(cin, temp->role);
                if (!isAlphabetic(temp->role)) {
                    cout << "Invalid input! Role must contain only alphabetic characters.\n";
                }
            } while (!isAlphabetic(temp->role));

            string grossSalaryStr;
            do {
                cout << "Enter new gross salary: ";
                cin >> grossSalaryStr;
                if (!isNumeric(grossSalaryStr)) {
                    cout << "Invalid input! Gross Salary must be a numeric value.\n";
                }
            } while (!isNumeric(grossSalaryStr));
            temp->grossSalary = stringToDouble(grossSalaryStr);

            string taxRateStr;
            do {
                cout << "Enter new tax rate (%): ";
                cin >> taxRateStr;
                if (!isNumeric(taxRateStr)) {
                    cout << "Invalid input! Tax Rate must be a numeric value.\n";
                }
            } while (!isNumeric(taxRateStr));
            temp->taxRate = stringToDouble(taxRateStr);

            calculateNetSalary(temp);
            cout << "Employee record modified successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with ID " << id << " not found.\n";
}

void searchEmployee() {
    string id;
    cout << "Enter Employee ID to search: ";
    cin >> id;
    Employee* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            cout << "Employee found:\n";
            cout << "ID: " << temp->id << "\nName: " << temp->name << "\nRole: " << temp->role << "\nGross Salary: " << temp->grossSalary << "\nTax Rate: " << temp->taxRate << "\nNet Salary: " << temp->netSalary << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with ID " << id << " not found.\n";
}

void printPayslip() {
    string id;
    cout << "Enter Employee ID to print payslip: ";
    cin >> id;
    Employee* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            cout << "\nEmployee Payslip:\n";
            cout << "ID: " << temp->id << "\nName: " << temp->name << "\nRole: " << temp->role << "\nGross Salary: " << temp->grossSalary << "\nTax Rate: " << temp->taxRate << "\nNet Salary: " << temp->netSalary << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with ID " << id << " not found.\n";
}

void deleteList() {
    Employee* current = head;
    Employee* next = NULL;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
}

int main() {
    loadData();  // Load data from database at the start
    char option;
    do {
        cout << "\n****** Payroll Management System 1.0 ******\n";
        cout << "Press a -----> Add New Record.\n";
        cout << "Press d -----> Display all Records.\n";
        cout << "Press u -----> Update a Record.\n";
        cout << "Press s -----> Search a Record.\n";
        cout << "Press p -----> Print Employee Payslip.\n";
        cout << "Press q -----> Quit Program.\n";
        cout << "\nSelect Your Option ====> ";
        cin >> option;

        switch (option) {
            case 'a': addEmployee(); break;
            case 'd': displayEmployees(); break;
            case 'u': modifyEmployee(); break;
            case 's': searchEmployee(); break;
            case 'p': printPayslip(); break;
            case 'q': cout << "Exiting program and cleaning up...\n"; saveData(); deleteList(); break;
            default: cout << "Invalid option! Please try again.\n";
        }
    } while (option != 'q');

    return 0;
}
