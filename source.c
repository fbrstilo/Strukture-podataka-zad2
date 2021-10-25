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
void insertAfter(person* prev, person* to_insert);
void prependList(person* headptr, person to_insert);
void appendList(person* headptr, person to_insert);
void printList();
void findByLname();
void deleteElement();

int main(){
    person head = {.fname = "", .lname = "", .next = NULL };



    return 0;
}

void prependList(person* headptr, person to_insert){

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