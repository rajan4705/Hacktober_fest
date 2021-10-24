// cyclically rotate an array by one by swapping every element by the last element

#include<bits/stdc++.h>
using namespace std;

void solve()
{
	int n;
	cin>>n;
	int arr[n];
	for(int i=0 ; i<n ; i++)
		cin>>arr[i];

	int i=0, j=n-1;
	while(i!=j)
	{
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		i++;
	}

	for(int i=0 ; i<n ; i++)
		cout<<arr[i]<<" ";
	cout<<endl;

	return;
}

int main()
{
	solve();
	return 0;
}