#include <iostream>
using namespace std;

struct Node
{
	   int data;
	   Node*next;	
}*start=NULL;

void push();
void pop();
void display();

int main() {
    char exit_flag = 'n';
    do {
        int choice = 0;

        cout << "\t1) Push";
        cout << "\t2) pop";
        cout << "\t3) display";
        cout << "\n\tPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                display();
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (exit_flag != 'y');

    return 0;
}


void push(){
	Node* temp = new Node;
	cout << "Please enter the data";
    cin >> temp->data;
   
    if(start==NULL){
		start=temp;
		temp->next=NULL;
	}else{
		temp->next=start;
		start=temp;
	}		
}

void pop(){
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