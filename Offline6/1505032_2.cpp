#include<iostream>
using namespace std;
void sortmerge(int time[], int l, int m, int r)
{
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;
    int L[n1];
    int R[n2];


    for (i=0; i<n1; i++)
    {
        L[i]=time[l+i];
    }
    for (j=0;j<n2;j++)
    {
        R[j]=time[m+j+1];
    }
    i = 0;
    j = 0;
    k = l;
    while (i<n1&&j<n2)
    {
        if (L[i]<= R[j])
        {
            time[k]=L[i];
            i++;
        }
        else
        {
            time[k]=R[j];
            j++;
        }
        k++;
    }

    while (i<n1)
    {
        time[k]=L[i];
        i++;
        k++;
    }
    while (j<n2)
    {
        time[k]=R[j];
        j++;
        k++;
    }
}

void mergesort(int time[], int l, int r)
{
    int n;
    n=r+1;
    if (l<r)
    {
        int m=l+(r-l)/2;
        mergesort(time,l,m);
        mergesort(time,m+1,r);
        sortmerge(time,l,m,r);
    }
}
void updateIndex(int time[],int index[],int n)
{
    for(int m=0;m<n;m++)
    {
        //mat[m]=time[m];
        index[time[m]]=m+1;
        //index[i]=i+1;

    }
}
void print(int time[],int index[],int n)
{
    for(int m=0;m<n;m++)
    {
      cout<<time[m]<<" ";

    }
    cout<<"\n"<<"The answer is==>\n";

     for(int m=0;m<n;m++)
    {
      cout<<index[time[m]]<<" ";

    }
}

int main()
{
    int n;
    int t;
    int index[2000];
    int mat[100];
    int time[100];
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>time[i];

    }

    updateIndex(time,index,n);
    mergesort(time,0,n-1);
    print(time,index,n);


}
