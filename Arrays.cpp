#include <iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter the number of elements: ";
    cin >> n;
    int array[n];

    for (int i = 0; i < n; i++)
    {
        cin >> array[i];
    }
    cout<<"The array is: ";
    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }



}