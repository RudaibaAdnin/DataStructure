#include<iostream>
#include<stdio.h>
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
using namespace std;
class HeapItem
{
public:
    int data;
    float key;
    HeapItem *right;
    HeapItem *left;
};

class MinHeap
{
public:
    HeapItem **A;
    int heapLength;
    int *map;

    MinHeap() //constructor
    {
        A = new HeapItem*[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }

    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1]->data = v[i];
            A[i+1]->key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }
    void insertItem(HeapItem *t)
    {
        heapLength++;
        A[heapLength]=t;
        int m=heapLength;
        while(m>=1)
        {
            heapify(m);
            m--;
        }
    }

    HeapItem *removeMin()
    {
        HeapItem *removeItem;
        removeItem=A[1];
        A[1]=A[heapLength];
        heapLength--;
        /*int m=heapLength;
         while(m>=1)
         {
             heapify(m);
             m--;
         }*/
        heapify(1);
        return removeItem;

    }

    /* void insert_Item(int data, int key)
     {
         int i,value,m;
         heapLength++;
         A[heapLength].data=data;
         A[heapLength].key=key;
         m=heapLength;

        m=heapLength;
         while(m>=1)
         {
             heapify(m);
             m--;
         }

     }*/
    /*  float getKey(int data)
      {
          int i = map[data];
          return A[i]->key;
      }*/
    /*  HeapItem *remove_Min()
      {
          HeapItem remove_Min;
          HeapItem remove_Min1;
          remove_Min1.key=0;
          remove_Min1.data=0;
          int value,m;
          remove_Min=A[1];
          A[1]=A[heapLength];
          heapLength--;

          if(heapLength<=0)
          {
              heapLength=0;
              printf("No item found\n");
              return remove_Min1;
          }
          m=heapLength;
          while(m>=1)
          {
              heapify(m);
              m--;
          }
          return remove_Min;//returning minimum item
      }*/


    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;
            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l]->key < A[r]->key )
                smallest = l;
            else
                smallest = r;

            if(A[i]->key<=A[smallest]->key)
                break;
            else
            {
                HeapItem *t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i]->data]=i;
                A[smallest]=t;
                map[A[smallest]->data]=smallest;
                i=smallest;
            }

        }
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};
void print(string v,HeapItem *root)
{
    if(root==NULL)
    {
        return;
    }
    if(root->left==NULL&&root->right==NULL)
    {
        printf("%c ",root->data);
        //cout<<min_node->data;
        cout <<v<< endl;
    }
    print(v+"0",root->left);
    print(v+"1",root->right);
}

void Huffman_tree(HeapItem *main,MinHeap *minHeap,int n)
{
    while(minHeap->heapLength!=1)
    {
        HeapItem *l;
        HeapItem *r;
        HeapItem *temp;
        temp = new HeapItem[1];
        l=minHeap->removeMin();
        r=minHeap->removeMin();
        temp->key =l->key+r->key;
        temp->left=l;
        temp->right=r;
        temp->data='!';
        minHeap->insertItem(temp);
    }
    main=minHeap->A[1];
    print("",main);
}

void huffmancode(char matrix[],int key[],int n)
{
    MinHeap *minHeap;
    minHeap=new MinHeap[1];
    HeapItem *main;
    int i;

    for(i=0; i<n; i++)
    {
        HeapItem *temp =new HeapItem[1];
        temp->left=0;
        temp->right=0;
        temp->data=matrix[i];
        temp->key =key[i];

        minHeap->insertItem(temp);
    }
    Huffman_tree(main,minHeap,n) ;


}
int main()
{
    int n;
    cin>>n;
    char matrix[100]; //{'a','b','c','d','e','f'};
    int freq[100]; //{45,13,12,16,9,5};
    for(int i=0; i<n; i++)
    {
        cin>>matrix[i];
        cin>>freq[i];
    }
    huffmancode(matrix,freq,n);
    return 0;
}


