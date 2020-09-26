#include<iostream>
using namespace std;
struct Point
{
public:
    int x;
    int y;
    int flag;
};
void initialize(struct Point *point,int n)
{
    for(int i=0; i<n; i++)
    {
        point[i].flag=1;
    }

}
void print(struct Point *point,int n)
{
    //cout<<"The answer is:\n";
    for(int i=0; i<n; i++)
    {
        if(point[i].flag==1)
        {
            cout<<point[i].x<<" "<<point[i].y<<"\n";
        }
    }
}
void sortmerge(struct Point *point,int l,int m,int h)
{
    int i,j,k;
    int n1=m-l+1;
    int n2=h-m;
    struct Point *Left;
    struct Point *Right;
    Left=new Point[n1];
    Right=new Point[n2];

    for (i=0; i<n1; i++)
    {
        Left[i]=point[l+i];
    }
    for (j=0; j<n2; j++)
    {
        Right[j]=point[m+j+1];
    }
    i = 0;
    j = 0;
    k = l;
    while(i<n1&&j<n2)
    {
        if (Left[i].x<=Right[j].x)
        {
            point[k]=Left[i];
            i++;
        }
        else
        {
            point[k]=Right[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        point[k]=Left[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        point[k]=Right[j];
        j++;
        k++;
    }
}

void mergesort(struct Point *point,int l,int h)
{
    if(l==h)
    {
        return;
    }

    int n;
    n=h+1;
    int m;
    if(l<h)
    {
        m=l+(h-l)/2;
        mergesort(point,l,m);
        mergesort(point,m+1,h);
        sortmerge(point,l,m,h);
    }
}
/*void sortt(struct Point *point,int n)
{
    struct Point t;
     for(int i=0; i<n; i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(point[j].x<point[i].x)
            {
              t=point[i];
              point[i]=point[j];
              point[j]=t;


            }
        }
    }
cout<<"After sorting:\n";
     for(int i=0; i<n; i++)
    {
        {
            cout<<point[i].x<<" "<<point[i].y<<"\n";
        }
    }

     for(int i=0; i<n; i++)
    {
        point[i].flag=1;
    }


}*/
/*void compare(struct Point *point,int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(point[j].x>=point[i].x&&point[j].y>=point[i].y)
            {
                point[j].flag=0;
            }
        }
    }
}*/

void divide(struct Point *point,int l,int h)
{
    if(l==h)
    {
        return;
    }
    int n;
    n=h+1;
    int q=INT_MAX;
    if (l<h)
    {
        int m=l+(h-l)/2;
        divide(point,l,m);
        divide(point,m+1,h);
        //cout<<"dividing\n";
        int p=l;

        //cout<<q<<"\n";
        while(p<m)
        {
            if(point[p].y<q)
            {
                q=point[p].y;
            }
            p++;
        }
        p=m;
        while(p<=h)
        {
            //if(point[p].x>=point[m-1].x&&point[p].y>=point[m-1].y)
            //if(point[p].flag==1&&point[p].y>=q)
            if(point[p].y>=q)
            {
                //cout<<"Got one\n";
                point[p].flag=0;
            }
            p++;
        }
    }
}


int main()
{

    int n;
    cin>>n;
    struct Point *point;
    point=new Point[n];
    for(int i=0; i<n; i++)
    {
        cin>>point[i].x;
        cin>>point[i].y;
    }

    initialize(point,n);
    cout<<"The points are:\n";
    print(point,n);
    mergesort(point,0,n-1);
    cout<<"After sorting:\n";
    /*for(int i=0; i<n; i++)
    {
        {
            cout<<point[i].x<<" "<<point[i].y<<"\n";
        }
    }*/
    print(point,n);
    divide(point,0,n-1);
    cout<<"The answer is:\n";
    print(point,n);




}







