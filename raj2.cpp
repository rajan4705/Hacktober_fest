#include<bits/stdc++.h>
using namespace std;
#define int long long
int32_t main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;

        vector<int> v(n);
        for(int i=0;i<n;i++){
            cin>>v[i];
        }
        if(1){
            bool flag = true;
            for(int k = 0; k < 1; k++){
            for (int i = 0; i < n-2; i++)
            {
                /* code */
                if(__gcd(v[i],v[i+2])>__gcd(v[i],v[i+1]))
                flag = false;
            }}
            if(flag) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
            
        }
        // else cout<<"YES"<<endl;
    }
    return 0;
}
