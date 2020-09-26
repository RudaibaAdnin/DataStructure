#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i,j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  *adjList ;
    int t;
    int *d;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int *col;
    int *distance;
    int *par;
    int *finish;
    int *disco;
    int *start;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    bool adja_is(int u,int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(int source); //will run dfs in the graph
    void dfs_visit(int u);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    col=0;
    par=0;
    distance=0;
    t=0;
    disco=0;
    finish=0;
    start=0;
    d=0;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices];
    par=new int[nVertices];
    col=new int[nVertices];
    distance=new int[nVertices];
    finish=new int[nVertices];
    disco=new int[nVertices];
    d=new int[nVertices];
    start=new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        return; //vertex out of range
    }
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed)
    {
        adjList[v].insertItem(u);
    }
}

void Graph::removeEdge(int u, int v)
{

    if(u<0||v<0||u>=nVertices||v>=nVertices)
    {
        printf("Vertex out of range\n");
        return;
    }

    /*this->nEdges--;
    adjList[u].removeItem(v) ;
    if(!directed)
    {
        adjList[v].removeItem(u);
    }*/
    int position;
    position=adjList[u].searchItem(v);
    //printf("The position is==> %d",position);
    if(position!=NULL_VALUE)
    {
        this->nEdges--;
        adjList[u].removeItem(v) ;
        if(!directed)
        {
            adjList[v].removeItem(u);
        }
    }
    else
    {
        return;
    }
}

bool Graph::isEdge(int u,int v)
{
    if(u<0||v<0||u>=nVertices||v>=nVertices)
    {
        printf("Vertex out of range\n");
        return false;
    }
    int position;
    position=adjList[u].searchItem(v);
    //printf("The position is==> %d",position);
    if(position!=NULL_VALUE)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Graph::adja_is(int u,int v)
{
    int length_u,flag=0;
    length_u=adjList[u].getLength();
    for(int i=0; i<nVertices; i++)
    {
        if(v==adjList[u].getItem(i))
        {
            flag=1;
        }
    }
    if(flag==1)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int Graph::getDegree(int u)
{
    if(u<0||u>=nVertices)
    {
        printf("Value out of range\n");
        return -1;
    }
    return (adjList[u].getLength());
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0||v<0||u>=nVertices||v>=nVertices)
    {
        printf("Vertex out of range\n");
        return false;
    }
    int length_u,length_v,flag=0;
    length_u=adjList[u].getLength();
    length_v=adjList[v].getLength();
    for(int m=0; m<length_u; m++)
    {
        for(int n=0; n<length_v; n++)
        {
            if(adjList[u].getItem(m)==adjList[v].getItem(n))
            {
                flag=1;
            }
        }
    }

    if(flag==1)
    {
        return true;
    }
    else
    {
        return false;
    }

}


void Graph::bfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        col[i] = WHITE ;
        par[i] = -1 ;
        distance[i] = INFINITY ;
    }
    Queue q ;
    col[source]=GREY;
    distance[source] = 0 ;
    q.enqueue(source) ;
    while(!q.empty())
    {

        int u,i;
        u=q.dequeue();
        for(i=0; i<nVertices; i++)
        {
            if(adja_is(u,i)&&col[i]==WHITE)
            {
                col[i]=GREY;
                distance[i]=distance[u]+1;
                par[i]=u;
                q.enqueue(i);
            }

        }
        col[u]=BLACK;
    }
    /*printf("The distance from vertex %d ",source);
    for(int i=0; i<nVertices; i++)
    {
      printf("to vertex %d ==> %d\n",i,distance[i]);

    }*/

}
void Graph::dfs_visit(int u)
{

    t=t+1;
    start[u]=t;
    distance[u]=t;
    col[u]=GREY;
    int j;
    for(j=0; j<nVertices; j++)
    {
        if(adja_is(u,j))
        {
            if(col[j]==WHITE)
            {
                par[j]=u;
                dfs_visit(j);

            }
        }
    }
    col[u]=BLACK;
    t=t+1;
    d[u]=t;

}

void Graph::dfs(int source)
{
    int j;
    for(j=0; j<nVertices; j++)
    {
        col[j]=WHITE;
        par[j]=-1;
        start[j]=0;
        d[j]=0;
    }
    t=0;
    for(j=source; j<nVertices; j++)
    {
        if(col[j]==WHITE)
        {
            dfs_visit(j);
        }
    }
    for(int i=0; i<nVertices; i++)
    {
        printf("For vertex %d :",i);
        printf("the first time is==>%d and finish time is==>%d\n",start[i],d[i]);
    }

}

int Graph::getDist(int u, int v)
{
    if(u<0||v<0||u>=nVertices||v>=nVertices)
    {
        //printf("vertex out of range\n");
        return -1;
    }
    bfs(u);
    //printf("distance from %d vertex to %d vertex is==> %d\n",u,v,distance[v]);
    return distance[v];
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf("%d ",adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    delete[] adjList;
    delete[] col;
    delete[] par;
    delete[] distance;
    delete[] start;
    delete[] d;
}

int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1.Add edge.2.is edge 3.remove edge 4.get degree\n");
        printf("5. Print Graph  6. Exit.7.has common adjacent\n");
        printf("8.get distance\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u,v);
            g.printGraph();
        }
        else if(ch==2)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            if(g.isEdge(u,v))
            {
                printf("YESS they have edge\n\n");
            }
            else
            {
                printf("NO they don't have edge\n\n");
            }
            g.printGraph();
        }
        else if(ch==3)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            g.removeEdge(u,v);
            g.printGraph();

        }
        else if(ch==4)
        {
            int u,value;
            scanf("%d",&u);
            value=g.getDegree(u);
            if(value>=0)
            {
                printf("The degree of vertex %d is==> %d\n",u,value);
            }
            g.printGraph();


        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            int u,v,dist;
            scanf("%d%d",&u,&v);
            if(g.hasCommonAdjacent(u,v))
            {
                printf("Yes they have common adjacent\n\n");
            }
            else
            {
                printf("No they don't have common adjacent\n\n");
            }
            g.printGraph();

        }
        else if(ch==8)
        {
            int u,v,dist;
            scanf("%d%d",&u,&v);
            dist=g.getDist(u,v);
            if(dist==INFINITY)
            {
                printf("distance infinity\n");
            }
            else if(dist==-1)
            {
                printf("vertex out of range\n");
            }
            else
            {
                printf("distance from %d vertex to %d vertex is==> %d\n\n",u,v,dist);
            }
            g.printGraph();
        }
        else if(ch==9)
        {
            int u;
            scanf("%d",&u);
            g.dfs(u);
        }
    }

}
