#include <iostream>
using namespace std;

struct Node
{
	   int data;
	   Node*next;	
}*start=NULL;

void enqueue();
void dequeue();
void display();

int main() {
    char exit_flag = 'n';
    do {
        int choice = 0;

        cout << "\t1) add";
        cout << "\t2) delete";
        cout << "\t3) display";
        cout <<"\t4) exit";
        cout << "\n\tPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
            	exit_flag='y';
            	
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (exit_flag != 'y');

    return 0;
}

void enqueue(){
	Node*temp=new Node;
	cout<<"enter data";
	cin>>temp->data;
	temp->next=NULL;
	if(IsEmpty()){
		
	}
	
	start->next=temp;
	start=temp;
}

void dequeue(){
	if(start==NULL){
	cout<<"NO data";
	}
	else{
		Node*current=start;
		start=start->next;
		delete current;
	}
}
void display(){
		if(start==NULL){
		cout<<"null";
	}
	else{
		for(Node*i=start;i!=NULL; i=i->next){
			cout<<i->data;
		}
	}
}