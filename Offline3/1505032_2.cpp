#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 2
#define GREY 3
#define BLACK 4


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
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ;
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i];
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front]=item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}
int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}
bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

class Graph
{
    int nVertices;
    int nEdges;
    bool directed;
    int **matrix;//adjacency matrix to store the graph
    int *par;
    int *col;
    int *distance;
    int t;
    int *d;
    int *start;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(int source);
    void dfs_visit(int u);

};


Graph::Graph(bool dir)
{
    nVertices =0 ;
    nEdges =0 ;
    matrix =0 ;
    col=0;
    par=0;
    distance=0;
    d=0;
    t=0;
    start=0;
    directed = dir ; //set direction of the graph
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    par=new int[nVertices];
    col=new int[nVertices];
    distance=new int[nVertices];
    d=new int[nVertices];
    start=new int[nVertices];

}

void Graph::addEdge(int u, int v)
{

    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        return;
    }
    nEdges++;
    matrix[u][v] = 1;
    if(!directed)
    {
        matrix[v][u] = 1;
    }

}

void Graph::removeEdge(int u, int v)
{
    if(u<0||v<0||u>=nVertices||v>=nVertices)
    {
        return;
    }
    if(matrix[u][v]==1&&matrix[v][u]==1)
    {
        nEdges--;
        matrix[u][v]=0;
        if(!directed)
        {
            matrix[v][u]=0;
        }
    }
}

bool Graph::isEdge(int u, int v)
{
    if(u<0||v<0||u>=nVertices||v>=nVertices)
    {
        printf("vertex out of range\n");
        return false;
    }
    //returns true if (u,v) is an edge, otherwise should return false
    if(matrix[u][v]==1&&matrix[v][u]==1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    int flag=0;
    for(int k=0; k<nVertices; k++)
    {
        if(matrix[u][k]==1&&matrix[v][k]==1)
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
        printf("vertex out of range");
        return -1;
    }
    int degree=0;
    for(int k=0; k<nVertices; k++)
    {
        if(matrix[u][k]==1)
        {
            degree++;
        }
    }
    return degree;
}


void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
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
            //if(matrix[u][i]==1)
            if(matrix[u][i]==1&&col[i]==WHITE)
            {
                col[i]=GREY;
                distance[i]=distance[u]+1;
                par[i]=u;
                q.enqueue(i);
            }

        }
        col[u]=BLACK;
    }
    /*  printf("The distance from vertex %d ",source);
      for(int i=0; i<nVertices; i++)
      {
          printf("to vertex %d ==> %d\n",i,distance[i]);

      }*/
}





void Graph::dfs(int source)
{
    int j;
    for(j=0; j<nVertices; j++)
    {
        col[j]=WHITE;
        par[j]=-1;
        d[j]=0;
        start[j]=0;
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


void Graph::dfs_visit(int u)
{

    t=t+1;
    start[u]=t;
    distance[u]=t;
    col[u]=GREY;
    int j;
    for(j=0; j<nVertices; j++)
    {
        if(matrix[u][j]==1&&col[j]==WHITE)
        {

            par[j]=u;
            dfs_visit(j);


        }
    }
    col[u]=BLACK;
    t=t+1;
    d[u]=t;

}

int Graph::getDist(int u,int v)
{
    /*for(int i=0; i<nVertices; i++)
     {
         col[i] = WHITE ;
         par[i] = -1 ;
         distance[i] = INFINITY ;
     }
     Queue q ;
     col[u] = GREY;
     distance[u] = 0 ;
     q.enqueue(u) ;
     while(!q.empty())
     {
         int u1,i;
         u1=q.dequeue();
         for(i=0;i<nVertices;i++)
         {
             if(matrix[u1][i]==1&&col[i]==WHITE )
             {
                col[i]=GREY;
                distance[i]=dist[u1]+1;
                par[i]=u1;
                q.enqueue(i);
             }

         }
         col[u1]=BLACK;
     }

    printf("distance from %d vertex to %d vertex is==> %d\n",u,v,distance[v]);*/

    if(u<0||v<0||u>=nVertices||v>=nVertices)
    {
        //printf("vertex out of range\n");
        return -1;
    }
    bfs(u);
    //printf("distance from %d vertex to %d vertex is==> %d\n",u,v,distance[v]);
    return distance[v];
    //return INFINITY ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices,nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
            {
                printf(" %d", j);
            }
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    delete[] matrix;
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
