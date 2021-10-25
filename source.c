#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 64
#define MAX_LINE 4096

typedef struct _person{
    char fname[MAX_STRING], lname[MAX_STRING];
    struct _person* next;
}person;

person* createPerson(char* fname, char* lname);
person* findEnd(person* headptr);
void insertAfter(person* prev, person* to_insert);
void prependList(person* headptr, person* to_insert);
void appendList(person* headptr, person* to_insert);
void printList(person* headptr);
person* findByLname(person* headptr, char* lname);
void deleteElement(person* headptr, char* fname, char* lname);
person* findBefore(person* headptr, char* fname, char* lname);

int main(){
    person head = {.fname = "", .lname = "", .next = NULL };



    return 0;
}

void prependList(person* headptr, person* to_insert){
    insertAfter(headptr, to_insert);
}

void appendList(person* headptr, person* to_insert){
    person* temp = headptr;
    temp = findEnd(temp);
    insertAfter(temp, to_insert);
}


void insertAfter(person* prev, person* to_insert){
    to_insert->next = prev->next;
    prev->next = to_insert;
}

person* createPerson(char* fname, char* lname){
    person* temp = NULL;

    temp = (person*)malloc(sizeof(person));
    if(!temp){
        perror("Failed to allocate memory for person in function createPerson\n");
        return NULL;
    }

    strcpy(temp->fname, fname);
    strcpy(temp->lname, lname);
    temp->next = NULL;

    return temp;
}

person* findEnd(person* headptr){
    person* temp = headptr;

    while(temp->next){
        temp = temp->next;
    }

    return temp;
}

void printList(person* headptr){
    for(person* node = headptr->next; node; node = node->next){
        printf("%s %s\n", node->fname, node->lname);
    }
}

person* findByLname(person* headptr, char* lname){
    for(person* node = headptr->next; node; node = node->next){
        if(!strcmp(node->lname, lname)){
            return node;
        }
    }
    return NULL;
}

void deleteElement(person* headptr, char* fname, char* lname){
    person* before = findBefore(headptr, fname, lname);
    person* temp = before->next;

    before->next = temp->next;
    free(temp);
}

person* findBefore(person* headptr, char* fname, char* lname){
    for(person* node = headptr->next; node; node = node->next){
        if(!strcmp(node->next->fname, fname) && !strcmp(node->next->lname, lname)){
            return node;
        }
    }
}