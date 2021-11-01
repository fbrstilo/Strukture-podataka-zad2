#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 64
#define MAX_LINE 1024

typedef struct _person{
    char fname[MAX_STRING], lname[MAX_STRING];
    int byear;
    struct _person* next;
}person;

person* createPerson(char* fname, char* lname, int byear);
person* findEnd(person* headptr);
void insertAfter(person* prev, person* to_insert);
void prependList(person* headptr, char* fname, char* lname, int byear);
void appendList(person* headptr, char* fname, char* lname, int byear);
void printList(person* headptr);
void printNode(person* node);
person* findByLname(person* headptr, char* lname);
void deleteElement(person* headptr);
person* findBefore(person* headptr, char* lname);

//zadatak 3
void addBehind(person* headptr, char* fname, char* lname, int byear);
void addBefore(person* headptr, char* fname, char* lname, int byear);
void sortByLname(person* headptr);
person* importList(char* filename);
int exportList(person* headptr, char* filename);

int ascending(char* str1, char* str2){return strcmp(str1, str2);} //vraca pozitivan broj ako su stringovi slozeni silazno
int descending(char* str1, char* str2){return strcmp(str2, str1);} //vraca pozitivan broj ako su stringovi slozeni uzlazno
void swapPerson(person* current);

//menu functions
int menu();
void printByLname(person* headptr);
void dataInput(person* headptr, void (*insert_function)(person* headptr, char* fname, char* lname, int byear));
void askLname(char* lname);


int main(){
    person head = {.fname = "", .lname = "", .byear = 0, .next = NULL };
    int choice;
    while(1){
        choice = menu();
        
        switch(choice){
            /*
            0 - izlaz
            1 - unos na pocetak liste
            2 - unos na kraj liste
            3 - unos ispred odredenog elementa
            4 - unos iza odredenog elementa
            5 - pronadi po prezimenu
            6 - brisanje iz liste
            7 - ispis liste
            8 - sortiranje liste
            9 - rad sa datotekama
            */
            case 0:
                return 0;
            case 1:
                dataInput(&head, prependList);
                break;
            case 2:
                dataInput(&head, appendList);
                break;
            case 3:
                dataInput(&head, addBefore);
                break;
            case 4:
                dataInput(&head, addBehind);
                break;
            case 5:
                printByLname(&head);
                break;
            case 6:
                deleteElement(&head);
                break;
            case 7:
                printList(&head);
                break;
            case 8:
                sortByLname(&head);
                break;
            case 9:
                break;
        }
    }
    return 0;
}

void prependList(person* headptr, char* fname, char* lname, int byear){
    person* to_insert = NULL;
    to_insert = createPerson(fname, lname, byear);
    if(!to_insert){
        printf("Failed to prepend list. Try again.\n");
        return;
    }
    insertAfter(headptr, to_insert);
}

void appendList(person* headptr, char* fname, char* lname, int byear){
    person* temp = headptr;
    person* to_insert = NULL;
    to_insert = createPerson(fname, lname, byear);
    if(!to_insert){
        printf("Failed to appepend list. Try again.\n");
        return;
    }
    temp = findEnd(temp);
    insertAfter(temp, to_insert);
}

void insertAfter(person* prev, person* to_insert){
    to_insert->next = prev->next;
    prev->next = to_insert;
}

person* createPerson(char* fname, char* lname, int byear){
    person* temp = NULL;

    temp = (person*)malloc(sizeof(person));
    if(!temp){
        perror("Failed to allocate memory for person in function createPerson\n");
        free(temp);
        return NULL;
    }

    strcpy(temp->fname, fname);
    strcpy(temp->lname, lname);
    temp->byear = byear;
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
    if(headptr->next == NULL){
        printf("Lista je prazna.\n");
    }
    for(person* node = headptr->next; node; node = node->next){
        printNode(node);
    }
}

void printNode(person* node){
    printf("%s %s %d\n", node->fname, node->lname, node->byear);
}

person* findByLname(person* headptr, char* lname){
    for(person* node = headptr->next; node; node = node->next){
        if(!strcmp(node->lname, lname)){
            return node;
        }
    }
    return NULL;
}

void deleteElement(person* headptr){
    char lname[MAX_STRING] = {0};
    askLname(lname);
    person* before = findBefore(headptr, lname);
    if(before == NULL){
        printf("Osoba se ne nalazi na listi.\n");
        return;
    }
    person* temp = before->next;
    before->next = temp->next;
    free(temp);
}

person* findBefore(person* headptr, char* lname){
    if(headptr->next == NULL) return NULL;
    for(person* node = headptr; node->next; node = node->next){
        if(strcmp(node->next->lname, lname) == 0){
            return node;
        }
    }
    return NULL;
}

int menu(){
    int choice = 0;
    
    while(1){
        printf(
        "Izbornik:\n"
        "0 - izlaz\n"
        "1 - unos na pocetak liste\n"
        "2 - unos na kraj liste\n"
        "3 - unos ispred odredenog elementa\n"
        "4 - unos iza odredenog elementa\n"
        "5 - pronadi po prezimenu\n"
        "6 - brisanje iz liste\n"
        "7 - ispis liste\n"
        "8 - sortiranje liste\n"
        "9 - rad sa datotekama\n"
        );

        scanf(" %d", &choice);
        puts("");
        if(choice>=0 && choice<=9) return choice;
        
        printf("Pogresan unos. Pokusajte ponovno\n");
    }
}

void printByLname(person* headptr){
    char lname[MAX_STRING];
    person* temp = NULL;
    askLname(lname);

    temp = findByLname(headptr, lname);
    if(temp == NULL){
        printf("Osoba se ne nalazi na listi.\n");
    }
    else{
        printNode(temp);
    }
}

void dataInput(person* headptr, void (*insert_function)(person* headptr, char* fname, char* lname, int byear)){
    char fname[MAX_STRING], lname[MAX_STRING];
    int byear;
    printf("Unesite ime i prezime osobe koju zelite unijeti:\n");
    scanf(" %s %s", fname, lname);
    printf("Godina rodenja: ");
    scanf(" %d", &byear);
    insert_function(headptr, fname, lname, byear);
}

void askLname(char* lname){
    printf("Unesite prezime trazene osobe:\n");
    scanf(" %s", lname);
}

void addBehind(person* headptr, char* fname, char* lname, int byear){
    person* temp = headptr;
    person* to_insert = NULL;
    char before[MAX_STRING];
    to_insert = createPerson(fname, lname, byear);
    if(!to_insert){
        printf("Failed to add behind. Try again.\n");
        return;
    }
    askLname(before);
    temp = findByLname(temp, before);
    insertAfter(temp, to_insert);
}

void addBefore(person* headptr, char* fname, char* lname, int byear){
    person* temp = headptr;
    person* to_insert = NULL;
    char before[MAX_STRING];
    to_insert = createPerson(fname, lname, byear);
    if(!to_insert){
        printf("Failed to add before. Try again.\n");
        return;
    }
    askLname(before);
    temp = findBefore(temp, before);
    insertAfter(temp, to_insert);
}

void sortByLname(person* headptr){
    person* current = headptr;
    int (*sort_check)(char* str1, char* str2);
    int choice = 0;
    int swapped = 1;

    //provjera postoje li prva 2 elementa
    if(!current->next) return;
    if(!current->next->next) return;

    while(1){
        printf(
        "Kakvo sortiranje zelite?\n"
        "1 - uzlazno\n"
        "2 - silazno\n");
        scanf(" %d", &choice);
        if(choice == 1){
            sort_check = ascending;
            break;
        }
        else if(choice == 2){
            sort_check = descending;
            break;
        }
        else{
            printf("Pogresan unos. Pokusajte ponovno:\n");
        }
    }
    
    while(swapped){
        swapped = 0;
        current = headptr;
        while(current->next->next){
            if(sort_check(current->next->lname, current->next->next->lname) > 0){
                swapPerson(current);
                swapped = 1;
            }
            current = current->next;
        }
    }
}

void swapPerson(person* current){
   person* first = current->next;
   if(!first){
       printf("Error in function swapPerson: person1 does not exist\n");
   }
   person* second = first->next;
   if(!second){
       printf("Error in function swapPerson: person2 does not exist\n");
   }
   first->next = second->next;
   second->next = first;
   current->next = second;
}