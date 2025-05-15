#include <iostream>
using namespace std;

struct Node
{
	
	int data;
	Node*next;
}*first=  NULL;
Node*last=NULL;

void display();
void add_data();


int main (){
	char flag='c';
	
	do{
		int choice;
		
		cout<<"\t===============================\n";
		cout<<"\t enter your choice\n";
		cout<<"\t===============================\n";
		
		cout<<"\t1) Add data\n";
		cout<<"\t2) display data\n";
		cout<<"\t3) exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
				add_data();
				break;
			case 2:
				display();
				break;
			case 3:
				flag='L';
				break;
			default:
				cout<<"invalid input";
				break;
		}
	}while(flag!='L');	
}


void add_data(){
	int age;
	cout<<"Enter your age";
	cin>>age;
	   Node*t=new Node;	
	   t->data=age;
	   t->next=NULL;
	   
	   if(first==NULL){
		   first=last=t;
	   }else{
		   last->next=t;
		   last=t;
	   }
	
}
void display(){
	Node*p;
	p=first;

	while(p!=NULL)
		{	
		   	cout<<"age "<<p->data <<endl;
			p=p->next;
	    }		
		
}