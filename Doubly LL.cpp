#include <iostream>
using namespace std;

struct Node 
{
	   Node *prev;
	   int data;
	   Node*next;	
	
}*first=NULL;

void create(int A[], int n){
	Node *t ,*last;
	
	first=new Node;
	first->prev=NULL;
	first->data = A[0];
	first->next=NULL;
	last=first;
	
	for(int i=1; i<n; i++){
		t=new Node;
		t->data = A[i];
		t->next= NULL;
		t-> prev=last;
		last->next=t;
		last=t;
	}
}

void Display(struct Node *p){
	while(p)
	{
	 cout<< p->data<<" ";
	 p=p->next;	
	}
	cout<< endl;
}
  
int main()
{
	   int A[]={1,2,3,4,5};
	   int n= sizeof(A)/ sizeof(A[0]);
	   create(A,n);
	   cout<<"lists\n";
	   cout<<"==================";
	   cout<<endl;
	   Display(first);
	return 0;
}
