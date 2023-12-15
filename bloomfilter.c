#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BIT_SIZE 100

bool bit[BIT_SIZE];

int hash1(char *key) {
    int a = 3;
    int b = 5;
    int val = 0;

    while (*key) {
        val += *key;
        key++;
    }

    val = (a * val + b) % BIT_SIZE;
    return val;
}

int hash2(char *key) {
    int a = 4;
    int b = 7;
    int val = 0;

    while (*key) {
        val += *key;
        key++;
    }

    val = (a * val + b) % BIT_SIZE;
    return val;
}

int hash3(char *key) {
    int a = 2;
    int b = 9;
    int val = 0;

    while (*key) {
        val += *key;
        key++;
    }

    val = (a * val + b) % BIT_SIZE;
    return val;
}

void insert(char *key) {
    int h1 = hash1(key);
    int h2 = hash2(key);
    int h3 = hash3(key);

    bit[h1] = true;
    bit[h2] = true;
    bit[h3] = true;
}

bool lookup(char *key) {
    int h1 = hash1(key);
    int h2 = hash2(key);
    int h3 = hash3(key);

    return bit[h1] && bit[h2] && bit[h3];
}

int main() {
    for (int i = 0; i < BIT_SIZE; i++) {
        bit[i] = false;
    }

    char string[] = "Hello";
    insert(string);
    if (lookup(string)) {
        printf("Present\n");
    } else {
        printf("Absent\n");
    }

    insert("batman");
    if (lookup("batman")) {
        printf("Present\n");
    } else {
        printf("Absent\n");
    }

    if (lookup("nightwing")) {
        printf("Present\n");
    } else {
        printf("Absent\n");
    }
    return 0;
}










// #include <stdio.h>
// #include <stdbool.h>
// #include <math.h>

// #define ll long long

// // hash 1
// int h1(char *s, int arrSize)
// {
//     ll int hash = 0;
//     for (int i = 0; s[i] != '\0'; i++)
//     {
//         hash = (hash + ((int)s[i]));
//         // hash = hash % 10;
//         hash = hash % arrSize;
//     }
//     return hash;
// }

// // hash 2
// int h2(char *s, int arrSize)
// {
//     ll int hash = 1;
//     for (int i = 0; s[i] != '\0'; i++)
//     {
//         hash = hash + pow(19, i) * s[i];
//         hash = hash % arrSize;
//     }
//     return hash % arrSize;
// }

// // hash 3
// int h3(char *s, int arrSize)
// {
//     ll int hash = 7;
//     for (int i = 0; s[i] != '\0'; i++)
//     {
//         hash = (hash * 31 + s[i]) % arrSize;
//     }
//     return hash % arrSize;
// }

// // hash 4
// int h4(char *s, int arrSize)
// {
//     ll int hash = 3;
//     int p = 7;
//     for (int i = 0; s[i] != '\0'; i++)
//     {
//         hash += hash * 7 + s[0] * pow(p, i);
//         hash = hash % arrSize;
//     }
//     return hash;
// }



// // lookup operation
// bool lookup(bool *bitarray, int arrSize, char *s)
// {
//     int a = h1(s, arrSize);
//     int b = h2(s, arrSize);
//     int c = h3(s, arrSize);
//     int d = h4(s, arrSize);

//     if (bitarray[a] && bitarray[b] && bitarray[c] && bitarray[d])
//         return true;
//     else
//         return false;
// }

// // insert operation
// void insert(bool *bitarray, int arrSize, char *s)
// {
//     // check if the element is already present or not
//     if (lookup(bitarray, arrSize, s))
//         printf("%s is Probably already present\n", s);
//     else
//     {
//         int a = h1(s, arrSize);
//         int b = h2(s, arrSize);
//         int c = h3(s, arrSize);
//         int d = h4(s, arrSize);
//         bitarray[a] = true;
//         bitarray[b] = true;
//         bitarray[c] = true;
//         bitarray[d] = true;

//         printf("%s inserted\n", s);
//     }
// }

// // Driver Code
// int main()
// {
//     bool bitarray[100] = {false};
//     int arrSize = 100;
//     char sarray[10][50];

//     for (int i = 0; i < 10; i++)
//     {
//         printf("Enter the string: ");
//         scanf("%s", sarray[i]);
//     }

//     for (int i = 0; i < 10; i++)
//     {
//         insert(bitarray, arrSize, sarray[i]);
//     }

//     return 0;
// }
