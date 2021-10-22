#include<stdio.h>
void ComputeTerm(int );         //function declaration

int main()          //main function
{
    int n;
    printf("Enter the value of n: ");  
    scanf("%d",&n);
    ComputeTerm(n);         //function calling
    
}

void ComputeTerm(int n)         //function definition
{
    int n1=1,n2=2,n3=3,n4=0;
    if(n<0)
    {
        printf("Negative input! Error\n");
    }
    else if(n==1)
        printf("%d",n1);
    else if(n==2)
        printf("%d",n2);
    else if(n==3)
        printf("%d",n3);
    else
    {   for(int i=3;i<n;i++)
        {
            n4=n2+2*n1;    
            n1=n2;    
            n2=n3;
            n3=n4;
        }
        printf("%d",n4);
    }
}
