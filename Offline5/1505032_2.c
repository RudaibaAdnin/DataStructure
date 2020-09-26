#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;
struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

struct listNode *searchItem(int item)
{
    struct listNode * temp ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }
    return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}
int insertItem(int item) //insert at the beginning of the linked list
{
    struct listNode * newNode,*pointNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = list ;
    list=newNode;
    printf("The head is: %d\n",list->item);
    pointNode=list;
    while(pointNode->next!=NULL)
    {
        pointNode=pointNode->next;
    }
    pointNode->next=NULL;
    tail=pointNode;
    printf("The tail is: %d\n",tail->item);
    return SUCCESS_VALUE ;
}
/*int insertItem(int oldItem, int newItem)
{
    struct listNode *newNode,*oldNode,*oldNodePrev,*pointNode;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = newItem ;
    oldNodePrev=list;
    oldNode=oldNodePrev->next;
    while(oldNode->item!=oldItem)
    {
        oldNodePrev=oldNode;
        oldNode=oldNode->next;
    }
    oldNodePrev->next=newNode;
    newNode->next=oldNode;
    pointNode=list;

    while(pointNode->next!=NULL)
    {
        pointNode=pointNode->next;
    }
    tail=pointNode;
    return SUCCESS_VALUE;
}*/

int deleteAfter(int item)
{
    struct listNode *deleteNode,*oldNode,*deleteNodePrev,*pointNode;
    if(list==NULL)
    {
        printf("No item found in the list to delete\n");
        return NULL_VALUE;
    }
    else
    {
        //deleteNode=deleteNodePrev->next;
        deleteNodePrev=list;
        while(deleteNodePrev!=0)
        {
            if(deleteNodePrev->item==item )
            {
                printf("DeleteNode Prev Item=== %d\n",deleteNodePrev->item);
                break;
            }
            deleteNodePrev=deleteNodePrev->next;
            //deleteNode=deleteNode->next;
        }
        //deleteNode=deleteNodePrev->next;
        if (deleteNodePrev ==NULL)
        {
            printf("DeleteAfter item not found\n");
            return NULL_VALUE ;
        }
        if(deleteNodePrev->next==NULL)
        {
            printf("No item after DeleteAfter item\n");
            return NULL_VALUE;
        }
        else
        {
            deleteNode=deleteNodePrev->next;
            deleteNodePrev->next=deleteNodePrev->next->next;
            free(deleteNode);
            pointNode=list;
            while(pointNode->next!=NULL)
            {
                pointNode=pointNode->next;
            }
            tail=pointNode;
            printf("The tail is:%d\n",tail->item);
            return SUCCESS_VALUE;

        }
    }


}

int insertLast(int item)
{

    struct listNode *newNode;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    //printf("The tail is:%d\n",tail->item);
    newNode->item = item ;
    //printf("The tail is:%d\n",newNode->item);
    if(list==0)
    {
        //newNode->item = item ;
        newNode->next = list ;
        list=newNode;
        tail=newNode;
        return SUCCESS_VALUE;
    }
    else
    {
        //newNode->item = item ;
        newNode->next = NULL ;
        tail->next=newNode;
        //newNode->next = NULL ;
        tail=newNode;
        return SUCCESS_VALUE;
    }


}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert item before . 2. Delete After. 3. Search item. \n");
        printf("4. Insert Last. 5. Print. 6. exit.\n");
        // printf("7.Insert Last.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
    }

}
