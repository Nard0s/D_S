
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
int A[100],n;
cout<<"how many nums \n";
cin>>n;
cout<< "enter "<<n <<" nums\n";
    	for(int i=0; i<n; i++)
         cin >> A[i];
     
     
  for (int i = 0; i < n - 1; i++)
  {
        for (int j = 0; j <=n-i-1; j++){
            if (A[j] > A[j + 1])
			{
                int temp = A[j];
    			A[j] = A[j + 1];
    			A[j + 1]=temp;
            }
        }
    }
    cout<<"=============================="<<endl;
  for (int i = 0; i < n; i++) {
        cout << A[i] << " "<<endl;
    }
     
	return 0;
}

