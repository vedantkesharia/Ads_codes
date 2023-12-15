#include <stdio.h>
#include <stdlib.h>

#define MAX_HASH_TABLES 2
#define MAX_SLOTS 11

int hashTables[MAX_HASH_TABLES][MAX_SLOTS]; // The hash tables for storing keys

// Initialize the hash tables with -1 indicating empty slots
void initializeTables() {
    for (int i = 0; i < MAX_HASH_TABLES; i++) {
        for (int j = 0; j < MAX_SLOTS; j++) {
            hashTables[i][j] = -1;
        }
    }
}

// Hashing functions
int hashFunction(int function, int key) {
    if (function == 1) {
        return key % MAX_SLOTS; // Modulo hashing
    } else if (function == 2) {
        return (key / MAX_SLOTS) % MAX_SLOTS; // Division hashing
    }
    return -1;
}

// Place a key in the hash tables using cuckoo hashing
void placeKey(int key, int tableId, int count, int n) {
    if (count == n) {
        printf("%d unpositioned\n", key);
        printf("Cycle present. REHASH.\n");
        return;
    }

    int positions[MAX_HASH_TABLES];
    for (int i = 0; i < MAX_HASH_TABLES; i++) {
        positions[i] = hashFunction(i + 1, key);
        if (hashTables[i][positions[i]] == key) {
            return; // Key already present, no need to insert
        }
    }

    for (int i = 0; i < MAX_HASH_TABLES; i++) {
        if (hashTables[tableId][positions[tableId]] != -1) {
            int displacedKey = hashTables[tableId][positions[tableId]];
            hashTables[tableId][positions[tableId]] = key;
            placeKey(displacedKey, (tableId + 1) % MAX_HASH_TABLES, count + 1, n);
        } else {
            hashTables[tableId][positions[tableId]] = key;
            return;
        }
    }
}

// Print the final hash tables
void printTables() {
    printf("Final hash tables:\n");
    for (int i = 0; i < MAX_HASH_TABLES; i++) {
        printf("\n");
        for (int j = 0; j < MAX_SLOTS; j++) {
            if (hashTables[i][j] == -1) {
                printf("- ");
            } else {
                printf("%d ", hashTables[i][j]);
            }
        }
        printf("\n");
    }
}

// Cuckoo hashing algorithm
void cuckooHashing(int keys[], int n) {
    initializeTables();
    for (int i = 0; i < n; i++) {
        int count = 0;
        placeKey(keys[i], 0, count, n);
        printTables();
    }
    printTables();
}

int main() {
    int keys[] = {20, 50, 53, 75, 100, 67, 105, 3, 36, 39, 6};
    
    cuckooHashing(keys, sizeof(keys) / sizeof(keys[0]));

    return 0;
}