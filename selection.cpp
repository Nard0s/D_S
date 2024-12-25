#include <iostream>
using namespace std;
int main()
{
int arr[100],n;
cout<<"how many nums \n";
cin>>n;
cout<< "enter "<<n <<" nums\n";
    	for(int i=0; i<n; i++)
         cin >> arr[i];
     
	for(int i=0; i<n-2; i++){
		 int mindex=i;
 	 for(int j=i+1; j<n-1; j++){
		  if( arr[i]< arr[mindex])
		  	mindex=j;
	}
	  if(mindex!=i){
		  int temp =arr[i];
			arr[i] = arr[i+1];
    		arr[i+1]= temp;
	  }
		                                                                                                                                     
	 }
	 
	for (int i = 0; i < n; i++) {
        cout << arr[i] << " "<<endl;
    }
	
	return 0;
}