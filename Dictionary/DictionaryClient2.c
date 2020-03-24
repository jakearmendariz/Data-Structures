

#include "Dictionary.h"
/*
 * test the hash table really simple tests, you will want to make
 * many more tests.
 */

int main()
{

    HashTableObj *H;

    // you can make this hash table size anything you like that is a prime but the example
    // results will be different based on the has table size.
    H = newHashTable(3);

    insert(H, NULL);      //test empty string
    insert(NULL, "bird"); //test no table
    insert(H, "dog");
    insert(H, "cat");
    insert(H, "frog");
    insert(H, "banana");
    insert(H, "apple");
    insert(H, "pear");

    printHashTable(stdout, H);

    if (member(H, "pear") && member(H, "cat") && member(H, "banana"))
        printf("great! found the members\n");
    else
        printf("oops, found a problem");

    if (!delete (H, "pear"))
        printf("problem, should have found pear\n");
    else
        printf("great! deleted pear\n");

    if (member(H, "pear"))
        printf("problem, should not have found pear\n");
    else
        printf("great! pear is gone\n");

    if (member(H, NULL))
        printf("problem, should not have found empty string\n");
    else
        printf("great! string is empty\n");

    printHashTable(stdout, H);
    deleteHashTable(H);

    return 0;
}

