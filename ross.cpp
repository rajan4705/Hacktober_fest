#include <iostream>
#include <string.h>
using namespace std;
int comp(string s1,string s2){
    
    int n1=s1.length(),n2=s2.length(),p=0;
    cout<<s2[3];
    if(n2<n1){
        
            
                int k = 0;
                for(int i = 0;i<=n2;i++){
                    cout<<"p="<<p<<" k= "<<k;
                cout<<" i="<<i;
                   if(s2[i]==s1[k]){
                    k++;
                    
                }else{
                    if(i==n2-1){
                       p=1;
                       cout<<"end loop";
                       
                    }
                    k++;cout<<" 4t"<<p<<k;
                    
                } 
                }
                
            
        
    
    return p;cout<<" 5t"<<p;
    
}
}
int main() {
string str1,str2;
cin>>str1;cin>>str2;

int n1=str1.length(),n2=str2.length(),p=0,arr[n1];
string arr1[n1],arr2[n2];

for(int i = 0;i<n1;i++){
    arr1[i]=str1[i];
}
for(int i = 0;i<n2;i++){
    arr2[i]=str2[i];
}

    int a = comp(str1,str2);
    cout<<"a";
    cout<<a;
}
