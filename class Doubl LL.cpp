#include <iostream>
using namespace std;
 struct Student
 {
	 int ID;
	 char name[20];
	 Student *next;
	 Student *prev;
	 
 }*start=NULL;
 
 void Add();
 void Display();
 void search_and_display();
 
 
 int main() {
    char exit_flag = 'n';
    do {
        
        int choice = 0;
		cout << "\t0) Exit\n";
        cout << "\t1) Add\n";
        cout << "\t2) Display\n";
        cout << "\t3) search_and_display\n";
        
       
        cin >> choice;

        switch (choice) {
            case 1:
                Add();
                break;
            case 2:
                Display();
                break;
            case 3:
                search_and_display();
                break;
            case 0:
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
void Add(){
	Student *temp=new Student;
	cout<<"pleace insert id";
	cin>> temp->ID;
	cout<<"pleace enter name";
	cin>>temp->name;
	if(start==NULL){
		start=temp;
		temp->next=NULL;
		temp->prev=NULL;	
	}
	else if(start->next==NULL){
		start->next = temp;
		temp->prev=start;
		temp-> next=NULL;
	}
	else{
		int id;
		cout<<"where do u like to add a node";
		cin>>id;
		Student*curr=start;
		while(curr->ID!=id&&curr->next!=NULL){
			   curr=curr->next;	
		}
		if(curr->next==NULL){
			curr->next=temp;
			temp->prev=curr;
			temp->next=NULL;
		}
		else{
			curr->next->prev=temp;
			temp->next=curr->next;
			temp->prev=curr;
			curr->next=temp;
		}
	}
}

void Display(){
	if(start==NULL){
		cout<<"the list is empty\n";
	}
	for(Student*i=start; i!=NULL; i=i->next){
		cout<<"ID: "<<i->ID<<endl;
		cout<<"name: "<<i->name<<endl;
		cout<<endl;
	}
}

void search_and_display(){

	cout<<"enter s id";
	
	if(start==NULL){
		cout<<"NOT found";
	}
	else{
		int id;
		cout<<"enter s id";
		cin>>id;
		Student*curr=start;
		while(curr->ID!=id&&curr->next!=NULL)
		{
		curr=curr->next;	
		}
		cout<<"ID: "<<curr->ID<<endl;
		cout<<"name: "<<curr->name<<endl;
		cout<<endl;	
	}
		
}


