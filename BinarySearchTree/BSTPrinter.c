//Can print Tree in more viewable way... Start with root 0
void print2DUtil(BSTObj *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->rightChild, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%s\n", root->term);

    // Process left child
    print2DUtil(root->leftChild, space);
}
