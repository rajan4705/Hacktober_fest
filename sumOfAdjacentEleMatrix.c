#include <stdio.h>

//taking the matrix input from user
void input(int *ptr,int r,int c)
{
    for(int i=0;i<r*c;i++)
    {
        scanf("%d",ptr+i);
    }
}

//function to display the sum of adjucent elements
void display(int *ptr,int r,int c)
{
    //loop to tackle increament of row
    for(int i=0;i<r;i++)
    {   
        //loop to tackle increamnet in a row
        for(int j=0;j<c-1;j++)
        {
            printf("%d ",*(ptr+((i*(c-1))+j)));
        }
        //new line for each new row
        printf("\n");
    }
}

void copy(int *ptrmat,int *ptrresult,int r,int c)
{
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c-1;j++)
        {
            *(ptrresult+((i*(c-1))+j))=*(ptrmat+((i*c)+j)) + *(ptrmat+((i*c)+j+1));
        }
    }
}

int main()
{
    //taking input for no of test cases
    printf("Enter No. of test cases = ");
    int test;
    scanf("%d",&test);
    //running the whole code until all cases are handled
    while(test--)
    {
        //taking input for row and column size
        int r,c;
        printf("Enter the no of row = ");
        scanf("%d",&r);
        printf("Enter the no of column = ");
        scanf("%d",&c);

        //creating the required matrix and taking input
        int mat[r][c];
        int *ptrmat = &mat[0][0];
        input(ptrmat,r,c);
        
        int result[r][c-1];
        int *ptrresult = &result[0][0];
        copy(ptrmat,ptrresult,r,c);

        //printing the result
        display(ptrresult,r,c);
    }
    return 0;
}
