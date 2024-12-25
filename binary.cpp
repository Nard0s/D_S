#include<iostream>
#include <conio.h>
using namespace std;
int main()
{
    int arr[100];
    int n,key,index=0;
  
    cout<<"how many names\n";
    cin>>n;
    cout<< "enter "<<n<<"names\n";
    for(int i=0; i<n; i++)
       cin >> arr[i];
       cout<<"enter search data\n";
       cin>> key;
   int left=0, right=n-1, mid=0;
   while (left<=right){
       mid=(left+right)/2;
       if(arr[mid]==key){
           index=1;
           cout<<key<<"is found at position"<<mid;
 getch();
       }
       else if(arr[mid]<key)
           left=mid+1;
       else
           right=mid-1;    
   }
   if(index==0){
       cout<<key<<"is not found";
   }
    
    return 0;
}