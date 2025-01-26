#include <iostream>
#include <cstdlib> // For system("cls")
using namespace std;

// Define the Student structure
struct Student {
    int ID;
    char name[30];
    Student* next;
} *start = NULL;

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

void insert_big(){
	Student*temp=new Student;
	cout<<"ID??";
	cin>>temp->ID;
	cout<<"name";
	cin>>temp->name;
	temp->next=start;
	start=temp;
}

void insert_end(){
Student*temp=new Student;
	cout<<"ID??";
	cin>>temp->ID;
	cout<<"name";
	cin>>temp->name;
	temp->next=NULL;
	if(start==NULL){
		start=temp;
	}
	else{
		Student*ptr=start;
		while(ptr->next!=NULL)
		{
			   ptr=ptr->next;	
		}
		ptr->next=temp;
	}	
}
