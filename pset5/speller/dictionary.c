// Implements a dictionary's functionality

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Keep track of total of words
int word_counter;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain a hash value
    int index = hash(word);

    // Create temp node = table[index]
    node *cursor = table[index];

    // Compares word in cursor to word in dictionaty. Returns true or move cursor to next node
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;
}


// Loads dictionary into memory, returning true if successful, else false
// Insert words to the hashtable
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read strings from file one at a time.
    char word[LENGTH + 1]; //Buffer
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        // Copy word into new_node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        //Hash word to obtain a hash value
        int index = hash(word);

        //Insert node into hash table at that location
        if (table[index] == NULL)
        {
            table[index] = new_node;
        }
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }

        //Updated total words
        word_counter++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        //Set two temp nodes = to the i element in the table array
        node *cursor = table[i];
        node *temp = table[i];

        //Free each element in table[i]
        while (cursor != NULL)
        {
            cursor = cursor->next;

            free(temp);

            temp = cursor;
        }
    }
    return true;
}
