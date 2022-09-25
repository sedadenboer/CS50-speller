/******************************************************
* dictionary.c
*
* Programmeren 2
* Seda den Boer
*
* Implements a dictionary's functionality
* Contains hash(), check(), load(), size() and unload()
******************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// initialize constants and variables
const unsigned int BUCKETS = 1000;
unsigned int hash_value;
int word_amount = 0;

// create struct (node in the hash table)
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// make hash table
node *table[BUCKETS];

/*
simple hash function (set BUCKETS = 26 for first letter hash function)
*/
// unsigned int hash(const char *word)
// {
//     int value = 0;

//     // loop though word
//     for (int i = 0, n = strlen(word); i < n; i++)
//     {
//         // make sure to get the same hash value, regardless of whether a word is in upper/lower case
//         value += tolower(word[i]);
//     }

//     // get a value in appropriate range
//     return value % BUCKETS;
// }

/*
djb2 hash function by Dan Bernstein, http://www.cse.yorku.ca/~oz/hash.html (altered to work for this program)
*/
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % BUCKETS;
}

/*
returns true if word is in dictionary, else false
*/
bool check(const char *word)
{
    // hash word to obtain a hash value
    hash_value = hash(word);

    // make cursor to traverse through linked list
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        // check if word and the word in first node are the same
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            // move cursor to the next node in the linked list
            cursor = cursor->next;
        }
    }
    return false;
}

/*
loads dictionary into memory, returning true if successful else false
*/
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *file = fopen(dictionary, "r");

    // if file is not opened, return false
    if (file == NULL)
    {
        return false;
    }

    // storage for value of node (character array)
    char word[LENGTH + 1];

    // read strings from file
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate memory for new node
        node *new_node = malloc(sizeof(node));

        // check if memory is allocated
        if (new_node == NULL)
        {
            return false;
        }

        // copy word into character array
        strcpy(new_node->word, word);

        // last node in a bucket points to null
        new_node->next = NULL;

        // hash word to obtain a hash value
        hash_value = hash(word);

        // insert node into hash table at location of hash value
        if (table[hash_value] == NULL)
        {
            // make table[hash] point to the new node
            table[hash_value] = new_node;
        }
        // insertion at front of linked list in case of multiple words at a certain hash index
        else
        {
            // make new node point to head of linked list, which is table[hash_value]
            new_node->next = table[hash_value];

            // reset head to the new node
            table[hash_value] = new_node;
        }
        // count the amount of words in file
        word_amount++;
    }
    fclose(file);

    // if dictionary is succesfully loaded into memory
    return true;
}

/*
returns number of words in dictionary if loaded, else 0 if not yet loaded
*/
unsigned int size(void)
{
    // word_amount was already initialized at 0
    return word_amount;
}

/*
unloads dictionary from memory, returning true if successful else false
*/
bool unload(void)
{
    for (int i = 0; i < BUCKETS; i++)
    {
        // iterate over hash table nodes with cursor pointer
        node *cursor = table[i];

        while (cursor != NULL)
        {
            // make a temporary pointer,tmp, which will iterate over nodes one step behind cursor
            node *tmp = cursor;
            cursor = cursor->next;

            // free memory with tmp
            free(tmp);
        }
    }
    return true;
}