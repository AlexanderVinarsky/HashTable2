#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_CITY_LENGTH = 30;

struct Element
{
    char data [MAX_CITY_LENGTH];
    Element* next;
};
struct Queue
{
    Element* head = nullptr, *tail = nullptr;
};
void push(Queue& q, char*s)
{
    Element* e = (Element*)malloc(sizeof(Element));
    strcpy(e->data,s);
    e->next = nullptr;

    if (q.head == nullptr)
    {
        q.tail = e;
        q.head = e;
    }
    else {
        q.tail->next = e;
        q.tail = e;
    }
}
int find(Queue &q, char* n)
{
    int counter = 0;
    Element* cur = nullptr;
    for (cur = q.head; cur != nullptr; cur = cur->next)
    {
        counter++;
        if (strcmp(cur->data, n) == 0)
        {
            printf("City was found!\n");
            return counter;
        }
    }
    printf("City wasn't found!\n");
    return counter;
}
int hashCode(char* cityName, int hashSize) {
    int hash = 0;
    for (char* cur = cityName; *cur!='\0'; *cur++) {
        hash+=int(*cur);
    }
    hash = hash%hashSize;
    return hash;
}
double hashTableCoef(Queue* hashTable, int hashSize) {
    double full = 0;
    for (int i = 0; i<hashSize; i++) {
        if (hashTable[i].head != nullptr) {
            full+=1.0;
        }
    }
    return full/hashSize;
}
void kill(Queue& q, Element* dead)
{
    if (q.tail == q.head)
    {
        strcpy(q.tail->data, "");
    }

    else if (q.head == dead)
    {
        Element* e = q.head;
        q.head = q.head->next;
        free(e);
    }

    for (Element* cur = q.head; cur != nullptr; cur = cur->next)
    {
        if ((cur->next) == dead)
        {
            strcpy(dead->data, "");
            cur->next = dead->next;
            free(dead);
        }
    }
}
bool isThere(Queue& q, char *n) {
    Element *cur = nullptr;
    for (cur = q.head; cur != nullptr; cur = cur->next) {
        if (strcmp(cur->data, n) == 0) {
            printf("\n %s is there!\n", n);
            return true;
        }
    }
    printf("\n %s isn't there!\n", n);
    return false;
}
void freeHashTable(Queue* hashTable, int hashSize) {
    for (int i = 0; i<hashSize; i++) {
        Element* cur = nullptr;
        if (hashTable[i].head != nullptr) {
            for (cur = hashTable[i].head; cur != nullptr; cur = cur->next)
            {
                kill(hashTable[i], cur);
            }
        }
    }
    //    for (int i = 0; i<hashSize; i++) {
    //        free(hashTable[i]);
    //    }
    //free(hashTable);
}
Element* findElement(Queue& q, char *n) {
    Element* cur = nullptr;
    for (cur = q.head; cur != nullptr; cur = cur->next)
    {
        if (strcmp(cur->data, n) == 0)
        {
            return cur;
        }
    }
    return nullptr;
}
void printQueue(Queue& q) {
    Element* cur = nullptr;
    for (cur = q.head; cur != nullptr; cur = cur->next) {
        printf("%s ", cur->data);
    }
}
void printHashTable(Queue* hashTable, int hashSize) {
    for (int i = 0; i < hashSize; i++) {
        printf("%d\n", i);
        printQueue(hashTable[i]);
        printf("\n");
    }
}

int main() {
    int hashSize = 17;
    char cityName[MAX_CITY_LENGTH];
    struct Queue hashTable[hashSize];

//    Queue* hashTable = (Queue*)сalloc(hashSize * sizeof(Queue));
//    for (int i = 0; i < hashSize; i++) {
//        *(hashTable+i) = malloc(sizeof(struct Queue));
//    }
//    Queue test;
//    Queue test1;
//    Queue test2;
//    ...
//    hashTable[0] = test;
//    hashTable[1] = test1;
//    hashTable[2] = test2;
//    ...

    FILE * f = fopen(R"(C:\Users\vinar\CLionProjects\HashTable\cities.txt)","r");
    if(!f)
        printf("Error!\n");
    else {
        while (fscanf(f, " %30s", cityName) == 1) {
            push(hashTable[hashCode(cityName, hashSize)], cityName);
        }
    }
    fclose(f);

    printHashTable(hashTable, hashSize);

    for (int i = 0; i<2; i++) {
        printf("Input your city to add:\n");
        scanf("%s", cityName);
        printQueue(hashTable[hashCode(cityName, hashSize)]);
        if (isThere(hashTable[hashCode(cityName, hashSize)], cityName)) {
            kill(hashTable[hashCode(cityName, hashSize)],
                 findElement(hashTable[hashCode(cityName, hashSize)], cityName));
        }
        else {
            push(hashTable[hashCode(cityName, hashSize)], cityName);
        }
        printQueue(hashTable[hashCode(cityName, hashSize)]);
        printf("\n");
    }
    int d = find(hashTable[hashCode(cityName, hashSize)], cityName);
    printf("Number of elements: %d\n", d);
    printf("HashTable Coefficient: %.2f\n", hashTableCoef(hashTable, hashSize));

    printHashTable(hashTable, hashSize);

    freeHashTable(hashTable, 17);

    printHashTable(hashTable, hashSize);
    return 0;
}

