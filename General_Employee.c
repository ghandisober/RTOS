/*                	   German Jordanian University                      *
 * 			Department of Computer Engineering                  *
 *                       CE 705: Real Time Embedded Systems                 *
 *                 Program demonstrating general C programming              * 
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure definition and declaration of head and tail for the linked list
struct employee {
    struct employee *prev;
    char name[20];
    char ssn[10];
    double salary;
    char address[30];
    int workhours;
    struct employee *next;
}*head, *tempHead;

void add(struct employee **list, char name[], char ssn[], double salary, char address[], int workhours)
{
    struct employee *tmp, *traverse;
    traverse = *list;
    tmp=malloc(sizeof(struct employee));
    strcpy(tmp->name, name);
    strcpy(tmp->ssn, ssn);
    strcpy(tmp->address, address);
    tmp->salary = salary;
    tmp->workhours = workhours;

    if(*list == NULL)
    {
        tmp->prev = NULL;
        tmp->next = NULL;
        *list = tmp;

    }
    else
    {
        while(traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = tmp;
        tmp->prev = traverse;
        tmp->next = NULL;
    }
}

int deleteEmployee(char name[])
{
    struct employee *traverse = head;

        for(traverse=head;traverse!=NULL;traverse=traverse->next)
        {
            if(strcmp(traverse->name, name)==0)
            {
                if(traverse->prev == NULL)
                {
                    head = traverse->next;

                }
                else
                {
                    traverse->prev->next = traverse->next;
                    if(traverse->next!=NULL)
                        traverse->next->prev = traverse->prev;
                }
                free(traverse);
                return 1;
            }
        }
        return -1;


}

int removeEmployeeFromList(struct employee **list, char name[])
{
    struct employee *traverse = *list;

        for(traverse=*list;traverse!=NULL;traverse=traverse->next)
        {
            if(strcmp(traverse->name, name)==0)
            {
                if(traverse->prev == NULL)
                {
                    *list = traverse->next;

                }
                else
                {
                    traverse->prev->next = traverse->next;
                    if(traverse->next!=NULL)
                        traverse->next->prev = traverse->prev;
                }
                free(traverse);
                return 1;
            }
        }
        return -1;


}




void print()
{
    if(head==NULL)
    {
        printf("The list is empty\n");
    }
    else
    {
        struct employee *traverse = head;

        for(traverse=head;traverse!=NULL;traverse=traverse->next)
        {
            printf("%s\n%s\n%e\n%s\n%d\n\n", traverse->name, traverse->ssn, traverse->salary, traverse->address, traverse->workhours);
        }
    }

}

int printFile(char filePath[])
{
    if(head==NULL)
    {
        printf("The list is empty\n");
        return 0;
    }
    else
    {
        struct employee *traverse = head;

        FILE *fp = fopen(filePath, "w");
        if(fp == NULL)
        {
            return -1;
        }

        for(traverse=head;traverse!=NULL;traverse=traverse->next)
        {
            fprintf(fp,"%s\n%s\n%e\n%s\n%d\n\n", traverse->name, traverse->ssn, traverse->salary, traverse->address, traverse->workhours);
        }
        fclose(fp);
        return 1;
    }

}

struct employee *minimum(struct employee *list)
{
    struct employee *traverse = list;
    struct employee *min= list;

    for(traverse=list;traverse!=NULL;traverse=traverse->next)
        {
            if((strcmp(min->name, traverse->name)) < 0)
            {
                min = traverse;
            }
        }
        return min;
}

void sort()
{

    struct employee *min = NULL;


    min  = minimum(head);
    while(min != NULL)
    {
        add(&tempHead, min->name,min->ssn,min->salary, min->address, min->workhours);
        deleteEmployee(min->name);
        min  = minimum(head);


    }
    head = tempHead;

}



void deleteList()
{
    struct employee *traverse = head;

    for(traverse=head;traverse!=NULL;)
        {
            traverse=traverse->next;
            free(traverse->prev);

        }


}

int main()
{
    head = NULL;

    printf("\nAdding Records:\n\n");
    add(&head, “Abass”, "2007502000", 10000.0, "abcd", 40);
    add(&head, “Sami”, "2007555001", 10600.0, "aggbcd", 30);
    add(&head, “Farah”, "2007555002", 10600.0, "aggbcd", 30);
    add(&head, “Hana”, "2007555003", 10600.0, "aggbcd", 30);
    add(&head, “John”, "2007555004", 10600.0, "aggbcd", 30);
    add(&head, “Ama”, "2007555005", 10600.0, "aggbcd", 30);
    sort();
    print();
    printFile("file.txt");
    printf("\n\nDeleting x, a, and c\n\n");
    deleteEmployee("x");
    deleteEmployee("a");
    removeEmployeeFromList(&head, "t");
    deleteEmployee("c");
    print();
    return 0;
}


