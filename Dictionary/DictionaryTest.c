#include "Dictionary.h"
#include <stdio.h>

int main()
{
    HashTableObj *H = newHashTable(5);
    insert(H, "JakeArmendariz");
    insert(H, "Gioh");
    insert(H, "Ezra");
    insert(H, "Danny");
    insert(H, "Thomas");

        if (member(H, "JakeArmendariz"))
    {
        printf("Found me\n");
    }

    if (member(H, "JakeArmendariz") && member(H, "Ezra") && member(H, "Danny"))
        printf("great! found the members\n");
    else
        printf("oops, found a problem\n");

    if (!delete (H, "Gioh"))
        printf("problem, should have found Gioh\n");
    else
        printf("great! deleted Gioh\n");

    deleteHashTable(H);
    printHashTable(stdout, H);
    return 0;
}
