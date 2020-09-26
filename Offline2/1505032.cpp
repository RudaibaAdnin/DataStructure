
#include<stdio.h>

#define MAX_HEAP_SIZE 100000

#define MAXREAL 999999.0

class HeapItem
{
public:
    int data; //actual data that is stored
    float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem *A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
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

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }

    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, int key)
    {
        int i,value,m;
        heapLength++;
        A[heapLength].data=data;
        A[heapLength].key=key;
        m=heapLength;
        //value=heapLength/2;
        // i=value;
        //buHeapify(i);
        buHeapify(m);
    }

    void updateKey(int data, float key)
    {

        /*HeapItem update_item;
        int place=0,m,value;
        // update_item.key=key;
        //update_item.data=data;

            if(heapLength==0)
            {
                printf("Invalid data value\n");
                return;
            }
            int n= map[data];

           // printf("the value of i is:%d\n",n);
            if(n==0)
            {
                printf("Invalid data value\n");
                return;
            }
            A[n].key=key;

            m=heapLength;
            //buHeapify(m);
           while(m>=1)
            {
                heapify(m);
                m--;
            }*/

        HeapItem update_item;
        int place=0,m,value;
        update_item.key=key;
        update_item.data=data;
        for(m=1; m<=heapLength; m++)
        {
            if(A[m].data==update_item.data)
            {
                place=m;
                //break;
            }
        }
        if(place==0)
        {
            printf("The data value is invalid\n");
            return;
        }
        else
        {
            A[place].key=update_item.key;

            int m=heapLength;
            buHeapify(m);
            /* while(m>=1)
             {
                 heapify(m);
                 m--;
             }*/
        }

    }

    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }
       HeapItem removeMin()
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
    }


    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
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
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }

        }
    }

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
    /* void buHeapify(int i)
     {
         int left,right,smallest;
         while(1)
         {
             left=2*i;      //left child index
             right=2*i+1;    //right child index
             smallest=i;

             if(left>heapLength && right>heapLength)
                 break; //nothing to do, we are at bottom
             else if(right>heapLength)
                 smallest = left;
             else if(left>heapLength)
                 smallest = right;
             else if( A[left].key < A[right].key )
                 smallest = left;
             else
                 smallest = right;

             if(A[i].key <= A[smallest].key)
                 break;	//we are done heapifying
             else
             {
                 //swap nodes with smallest child, adjust map array accordingly
                 HeapItem t;
                 t=A[i];
                 A[i]=A[smallest];
                 map[A[i].data]=i;
                 A[smallest]=t;
                 map[A[smallest].data]=smallest;
                 i=smallest;
                 while(i>=1)
                 {
                     buHeapify(i);
                     i=i/2;
                 }
             }
         }


     }*/
    void buHeapify(int i)
    {
        int left,right,smallest,parent;
        int  n=i/2;
        //printf("the value of parent===> %d\n",n);
        while(n>=1)
        {
            parent=n;
            while(1)
            {

                left=2*parent;
                right=2*parent+1;
                smallest=parent;

                if(left>heapLength && right>heapLength)
                {
                    break;
                }
                else if(right>heapLength)
                {
                    smallest=left;
                }
                else if(left>heapLength)
                {
                    smallest=right;
                }
                else if( A[left].key < A[right].key )
                {
                    smallest = left;
                }
                else
                {
                    smallest = right;
                }

                if(A[parent].key <= A[smallest].key)
                {
                    break;
                }
                else
                {
                    HeapItem t;
                    t=A[parent];
                    A[parent]=A[smallest];
                    map[A[parent].data]=parent;
                    A[smallest]=t;
                    map[A[smallest].data]=smallest;
                    parent=smallest;
                }
            }
            n--;
           // printf("the value of parent==> %d\n",n);
        }
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};


int main()
{
    int choice;
    int data;
    float key;
    MinHeap heap;
    bool exit = false;
    while(!exit)
    {
        printf("1. Insert 2. RemoveMin 3.Update 4. Print 5. Exit.\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            scanf("%d%f",&data,&key);
            heap.insertItem(data, key);
            heap.printHeap();
            break;
        case 2:
            HeapItem item;
            item = heap.removeMin();
            printf("Removed: (%d,%.2f)\n", item.data, item.key);
            heap.printHeap();
            break;
        case 3:
            scanf("%d%f",&data,&key);
            heap.updateKey(data,key);
            heap.printHeap();
            break;
        case 4:
            heap.printHeap();
            break;
        case 5:
            exit = true;
            break;

        }
    }
    return 0;
}

