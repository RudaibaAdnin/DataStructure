#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
};

struct listNode * list;

struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

int insertFirst(int item) //insert at the beginning
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;

    if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
    return SUCCESS_VALUE ;
}


int deleteAfter(int item)
{
    //write your codes here
    struct listNode *deleteNodePrev,*deleteNode,*temp;

    if(list==NULL)
    {
        printf("No item found in the list to delete\n");
        return NULL_VALUE;
    }
    else
    {
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
        if(deleteNodePrev->next==tail)
        {
            deleteNode=deleteNodePrev->next;
            deleteNodePrev->next=0;
            tail=deleteNodePrev;
            free(deleteNode);
            return SUCCESS_VALUE;
        }
        else
        {
            deleteNode=deleteNodePrev->next;
            deleteNodePrev->next=deleteNodePrev->next->next;
            deleteNodePrev->next->prev=deleteNodePrev;
            free(deleteNode);
            return SUCCESS_VALUE;
        }
    }

}

int deleteLast()
{
    struct listNode *deleteNode;
    if(list==NULL||tail==NULL)
    {
        printf("No item found in the list to delete\n");
        return NULL_VALUE;
    }
    if(tail==list)
    {
        deleteNode=tail;
        list=0;
        tail=0;
        free(deleteNode);
        return SUCCESS_VALUE;
    }
    else
    {
        printf("the tail is %d\n",tail->item);
        deleteNode=tail;
        tail=deleteNode->prev;
        //tail->prev->next=0;;
        //tail=tail->prev;
        //tail=temp;
        tail->next=NULL;
        free(deleteNode);
        return SUCCESS_VALUE;
    }
}


struct listNode * searchItem(int item)
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

void printListForward()
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

void printListBackward()
{
    struct listNode *printNode;
    printNode = tail;
    while(printNode!=0)
    {
        printf("%d->", printNode->item);
        printNode=printNode->prev;
    }
    printf("\n");

}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward. 6. exit.7.Delete Last\n");
        printf("8.Delete After\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }
        else if(ch==2)
        {
            int item = deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            printListForward();
        }
        else if(ch==5)
        {
            printListBackward();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            deleteLast();
        }
        if(ch==8)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
    }

}
