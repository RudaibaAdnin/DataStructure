
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

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning of the linked list
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = list ; //point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
    return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
    struct listNode *temp, *prev ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) break ;
        prev = temp;
        temp = temp->next ; //move to next node
    }
    if (temp == 0) return NULL_VALUE ; //item not found to delete
    if (temp == list) //delete the first node
    {
        list = list->next ;
        free(temp) ;
    }
    else
    {
        prev->next = temp->next ;
        free(temp);
    }
    return SUCCESS_VALUE ;
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

int insertLast(int item)
{

    struct listNode *lastNode,*lastNodePrev;
    lastNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    lastNode->item = item ;
    if(list==0)
    {
        list=lastNode;
        lastNode->next=NULL;
        return SUCCESS_VALUE;
    }
    else
    {
        lastNode->next = NULL ;
        lastNodePrev=list;
        while(lastNodePrev->next!=NULL)
        {
            lastNodePrev=lastNodePrev->next;
        }
        lastNodePrev->next=lastNode;
        return SUCCESS_VALUE;
    }
}

int insertBefore(int oldItem, int newItem)
{
    struct listNode *newNode,*oldNode,*oldNodePrev;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = newItem ;
    //oldNodePrev=list;
    // oldNode=oldNodePrev->next;
    if(list==0)
    {
        printf("LIST EMPTY\n");
        return SUCCESS_VALUE;
    }
    else
    {
        oldNode=list;
        if(oldNode->item==oldItem)
        {
            printf("Item in the head\n");
            newNode->next = list ;
            list = newNode;
            return SUCCESS_VALUE ;
        }
        //oldNodePrev=list;
        //oldNode=oldNodePrev->next;
        while(oldNode!=0)
        {
            if(oldNode->item==oldItem)
            {
                break;
            }
            oldNodePrev=oldNode;
            oldNode=oldNode->next;
        }

        if(oldNode==0)
        {
            printf("Old node item not found\n");
            return SUCCESS_VALUE;
        }
        else
        {
            oldNodePrev->next=newNode;
            newNode->next=oldNode;
            return SUCCESS_VALUE;
        }
    }
}

int deleteAfter(int item)

{
    struct listNode *deleteNode,*oldNode,*deleteNodePrev;
    //deleteNodePrev=list;
    //deleteNode=deleteNodePrev->next;
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
                //printf("DeleteNode Prev Item=== %d\n",deleteNodePrev->item);
                break;
            }
            deleteNodePrev=deleteNodePrev->next;
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
            return SUCCESS_VALUE;
        }
    }


}

int deleteLast()
{
    struct listNode *deleteNode,*deleteNodePrev;

    if(list== NULL)
    {
        printf("No item found in the list to delete\n");
        return NULL_VALUE;
    }
    else
    {
        deleteNode=list;
        if(deleteNode->next==NULL)
        {
            list=0;
            free(deleteNode);
            printf("Deleting head\n");
            return SUCCESS_VALUE;
        }

        while(deleteNode->next!=NULL)
        {
            deleteNodePrev=deleteNode;
            deleteNode=deleteNode->next;
        }

        deleteNodePrev->next=NULL;
        free(deleteNode);
        return SUCCESS_VALUE;
    }
}



int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert Last. 5. Print. 6. exit. 7.Insert Before\n");
        printf("8.Delete After. 9.Delete Last \n");
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
            deleteItem(item);
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
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            int oldItem,newItem;
            scanf("%d %d", &oldItem,&newItem);
            insertBefore(oldItem,newItem);
        }
        else if(ch==8)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==9)
        {
            deleteLast();
        }
    }

}
