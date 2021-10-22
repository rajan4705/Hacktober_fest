int searchInSorted(int arr[], int N, int K) { 
    int h=N-1,l=0,x=0,r=0;
    while(1){
        x=(h+l)/2;
        if (K==arr[x]){
            r=1;
            break;
        } 
        //Checking the constraint
        if(l>=h || l<0 || h>N-1){
            r=-1;
            break;
        }        
        if(K>arr[x])
            l=x+1;
        else
            h=x-1;
    }
    return r;
}
