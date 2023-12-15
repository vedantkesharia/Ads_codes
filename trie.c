#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Structure for Trie Node
struct TrieNode
{
    char character;
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

// Creates a new Trie Node
struct TrieNode *createTrieNode(char character)
{
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (newNode)
    {
        newNode->isEndOfWord = false;
        newNode->character = character;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Inserts a word into the Trie
void insertWord(struct TrieNode *root, char *word)
{
    struct TrieNode *currentNode = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (!currentNode->children[index]) // if no children present or if character is not child, then it creates a node  
        {
            currentNode->children[index] = createTrieNode(word[i]);
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = true;
}

// Searches for a word in the Trie
bool searchWord(struct TrieNode *root, const char *word)
{
    struct TrieNode *currentNode = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (!currentNode->children[index])
        {
            return false; // Word not found
        }
        currentNode = currentNode->children[index];
    }
    return (currentNode != NULL && currentNode->isEndOfWord);
}

// Checks if a node has no children
bool isLeaf(struct TrieNode *node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            return false;
        }
    }
    return true;
}


// if{}
// if{if{}}
// if{}
// if{}

// Recursively deletes a word from the Trie
bool deleteWord(struct TrieNode *root, const char *word, int depth)
{
    if (!root) //to check if root is null, if null return false 
    {
        return false;
    }
    if (word[depth] == '\0') //: Checks if the current character of the word is the null character ('\0'), indicating the end of the word.
    {
        if (root->isEndOfWord)
        {
            //If root->isEndOfWord is true (indicating that the current node represents the end of a word), it sets root->isEndOfWord to false (indicating the removal of the word) and returns the result of isLeaf(root)
            root->isEndOfWord = false;
            return isLeaf(root);
        }
        return false; //returns false if word not found 
    }
    int index = word[depth] - 'a';
    if (!root->children[index])
    //  Checks if the child node corresponding to the calculated index does not exist. If so, it returns false, indicating that the word is not found.
    {
        // printf("Word not found ");
        return false; // Word not found
    }
    // Recursively delete the word
    if (deleteWord(root->children[index], word, depth + 1))
    {
        free(root->children[index]);
        root->children[index] = NULL;
        // If the current node is a leaf node because we deleted its children and not the end of another word,
        // indicate the node can also be deleted
        return (!root->isEndOfWord && isLeaf(root));
    }
    return false;
}

// Prints Trie nodes
void printTrieNodes(struct TrieNode *node)
{
    if (!node)
        return;
    struct TrieNode *temp = node;
    printf("%c -> ", temp->character);
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        printTrieNodes(temp->children[i]);
    }
    printf("\n");
}

int main()
{
    struct TrieNode *root = createTrieNode('\0');
    char word[100];
    int choice;
    while (1)
    {
        printf("1. Insert a word\n2. Search for a word\n3. Delete a word\n4. Print Trie\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter a word to insert: ");
            scanf("%s", word);
            insertWord(root, word);
            break;
        case 2:
            printf("Enter a word to search: ");
            scanf("%s", word);
            printf("Search '%s': %s\n", word, searchWord(root, word) ? "Found" : "Not Found");
            break;
        // case 3:
        //     printf("Enter a word to delete: ");
        //     scanf("%s", word);
        //     deleteWord(root, word, 0);
        //     printf("Deleted '%s'\n", word);
        //     break;
        case 3:
            printf("Enter a word to delete: ");
            scanf("%s", word);
            if (deleteWord(root, word, 0))
            {
                printf("Deleted '%s'\n", word);
            }
            else
            {
                printf("Word '%s' not found\n", word);
            }
            break;
        case 4:
            printTrieNodes(root);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}