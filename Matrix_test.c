// for a 512 x 512 matrix (example, will be updated to an actually realistic size later).

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAP_SIZE 512
#define EMPTY_VALUE 0
#define HASH_TABLE_SIZE 1024

typedef struct HashNode {
    int x, y;
    int value;
    struct HashNode* next;
} HashNode;

int map[MAP_SIZE][MAP_SIZE] = {EMPTY_VALUE};
HashNode* hashTable[HASH_TABLE_SIZE] = {0};

unsigned int hashFunction(int x, int y) {
    return (x * 31 + y) % HASH_TABLE_SIZE;
}

void insertOrUpdateHashTable(int x, int y, int value) {
    unsigned int hashIndex = hashFunction(x, y);
    HashNode* current = hashTable[hashIndex];
    HashNode* prev = NULL;

    while (current != NULL && !(current->x == x && current->y == y)) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        current->value = value;
    } else {
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->x = x;
        newNode->y = y;
        newNode->value = value;
        newNode->next = hashTable[hashIndex];
        hashTable[hashIndex] = newNode;
    }
}

void updateMap(int x, int y, int value) {
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
        map[x][y] = value;
        if (value != EMPTY_VALUE) {
            insertOrUpdateHashTable(x, y, value);
        }
    }
}

int getValue(int x, int y) {
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
        if (map[x][y] != EMPTY_VALUE) {
            return map[x][y];
        }

        unsigned int hashIndex = hashFunction(x, y);
        HashNode* current = hashTable[hashIndex];
        while (current != NULL) {
            if (current->x == x && current->y == y) {
                return current->value;
            }
            current = current->next;
        }
    }
    return EMPTY_VALUE;
}

void freeHashTable() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

// VALUE CHART
// EMPTY (INITIALIZED AS SO) - 0
// BORDER - 1
// SBLOCK - 2
// BBLOCK - 3
// CLIFF - 4
// MOUNTAIN - 5

int main() {
    // Example usage at coords 
    updateMap(10, 10, 5);
    printf("Value at (10, 10): %d\n", getValue(10, 10));

    updateMap(20, 20, 8);
    printf("Value at (20, 20): %d\n", getValue(20, 20));

    // Free allocated memory
    freeHashTable();

    return 0;
}
