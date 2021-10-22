#include <bits/stdc++.h>
using namespace std;

void prnt(deque<int> s)
{
    for(auto itr = s.begin();itr!=s.end();++itr)
    cout<<*itr<<" "<<endl;
}

vector<int> solve(vector<int> arr, vector<int> queries) {

    vector<int> v;
    deque<int> dq;

    
    for(int i=0;i<queries.size();i++)
    { 
        int min=INT_MAX,max=INT_MIN; 
        for(int k=0;k<queries[i];k++){
            dq.push_back(arr[k]);
            if(arr[k]>max)
            max=arr[k];
        }
        min=max;
        //prnt(dq);
        for(int j=queries[i];j<arr.size();j++)
        {
            int e=dq.front();
            dq.pop_front();
            if(max==e)
            {
                dq.push_back(arr[j]);
                max=*std::max_element(dq.begin(), dq.end());
            }
            else
            {
                dq.push_back(arr[j]);
                if(arr[j]>max)
                max=arr[j];
            }

            if(min>max)
            min=max;
        }
        v.push_back(min);        
    } 
    return v;
}

int main()
{
    int n,q;
    cin>>n>>q;

    vector<int>arr;
    vector<int>queries;

    for(int i=0;i<n;i++)
    {
        int e;
        cin>>e;
        arr.push_back(e);
    }
    for(int i=0;i<q;i++)
    {
        int e;
        cin>>e;
        queries.push_back(e);
    }

    vector<int> result=solve(arr,queries);

    for(auto itr = result.begin();itr!=result.end();++itr)
    cout<<*itr<<" ";

    return 0;
}
