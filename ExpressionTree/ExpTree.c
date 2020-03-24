#include "ExpTree.h"
/*
 * Read input string with contains a post-fix expression and buid the corresponding expression evaluation
 *
 * handles input of one post-fix expressio of integers n read from stdin. Examples:
 *   a b c + +    a b - c +   where a,b,c are integers
 * ignores all white space and uses C's sscanf to find acceptable integer formats. Input can flow over
 * multiple lines and is terminated with EOF. 
 *
 * This program only handles regular ints on your machine. So if you input very long int values they will be either
 * truncated or wrap around due to overflow, depening on what sscanf does will integer conversion from too long
 * string values.
 * 
 * Does not handle overflow in general, so if you have a resulting expression too large for an int, an overflow
 * generate unexpected results. 
 *
 */

tokenType convertToken(char *tokenStr, int *tokenVal);

TNode *newTNode(tokenType inputToken, int tokenVal, TNode *op1, TNode *op2);
const char *tokenToStr(tokenType tokenT);
void printNode(TNode *node);

ExpT *newExpressionTree()
{
    StackObj *S;

    S = newStack();
    return S;
}

void deleteTree(TNode *T)
{

    if (T != NULL)
    {
        T->value = 0; // neurotic
        deleteTree(T->leftOperand);
        deleteTree(T->rightOperand);
        free(T);
    }
}
//Calls on delete tree to delete the rest
void deleteExpressionTree(ExpT *T)
{

    TNode *node;
    StackObj *S = T;

    while ((node = (TNode *)pop(S)) != NULL)
    {
        deleteTree(node);
    }
    deleteStack(S);
}

void printNode(TNode *node)
{

    printf(" node addr = %p, type = %d, value = %d, leftOp = %p, rightOp = %p\n", node, node->type,
           node->value, node->leftOperand, node->rightOperand);
    printf("Token to string:%s\n", tokenToStr(node->type));
}

tokenType convertToken(char *tokenStr, int *tokenVal)
{

    tokenType retVal;
    char junkChars[MAX_TOKEN_LENGTH];
    int scanCount;

    // check what the token string might be
    scanCount = sscanf(tokenStr, "%d%s", tokenVal, junkChars);

    if (scanCount == 1)
    {
        //printf("token is an integer,str is %s, value = %d\n", tokenStr, *tokenVal);
        return OPERAND;
    }
    if (scanCount == 2)
    { // check no trailing characters
        fprintf(stderr, "ERROR, unaccceptable format, had some extra characters in the integer %d\n", *tokenVal);
        exit(EXIT_FAILURE);
    }

    if (scanCount > 2)
    {
        fprintf(stderr, "something weird in input parsing, exiting with str = %s\n", tokenStr);
        exit(EXIT_FAILURE);
    }
    // maybe an operator, try and check the format
    else
    {
        if (strlen(tokenStr) > MAX_OPERATOR_LENGTH)
        {
            printf("sorry, can't handle operators longer than 1 character\n");
            return END;
        }
        switch (tokenStr[0])
        {
        case '+':
            retVal = PLUS;
            break;
        case '-':
            retVal = MINUS;
            break;
        case '*':
            retVal = MUL;
            break;
        case '/':
            retVal = DIV;
            break;
        default:
            fprintf(stderr, "sorry, don't recognize this operator %c\n", tokenStr[0]);
            exit(EXIT_FAILURE);
        }
        //printf("got operator = %d\n", retVal);
        return retVal;
    }
}

// Document how to call  this function
TNode *newTNode(tokenType inputToken, int tokenVal, TNode *op1, TNode *op2)
{

    TNode *node;

    node = (TNode *)malloc((size_t)(sizeof(TNode)));
    node->type = inputToken;
    if (inputToken == OPERAND)
    { // this will be a leaf
        node->value = tokenVal;
        node->leftOperand = NULL;
        node->rightOperand = NULL;
    }
    else
    { // this will be an internal node
        node->leftOperand = op1;
        node->rightOperand = op2;
    }
    //printf("tree node created\n");
    //printNode(node);
    return node;
}

const char *tokenToStr(tokenType tokenT)
{

    const static char *tokenChars[] = {"+", "-", "*", "/", "^D"};

    return tokenChars[tokenT];
}

void print2DUtil(TNode *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->rightOperand, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    if (root->type == PLUS)
        printf("+\n");
    else if (root->type == MINUS)
        printf("-\n");
    else if (root->type == MUL)
        printf("*\n");
    else if (root->type == DIV)
        printf("/\n");
    else
    {
        printf("%d\n", root->value);
    }
    // Process left child
    print2DUtil(root->leftOperand, space);
}

/**
 * expressionEval
 * 
 * @param T is the root node
 * Calculates the value of the expression tree
 * returns an integer value
 */
int expressionEval(TNode *T)
{

    if (T->type != OPERAND && T->leftOperand->type == OPERAND && T->rightOperand->type == OPERAND)
    {
        if (T->type == PLUS)
            return T->leftOperand->value + T->rightOperand->value;
        else if (T->type == MINUS)
            return T->leftOperand->value - T->rightOperand->value;
        else if (T->type == MUL)
            return T->leftOperand->value * T->rightOperand->value;
        else if (T->type == DIV)
        {
            if (T->rightOperand->value == 0)
            {
                fprintf(stderr, "Error, 0 value in divisor\n");
            }
            return T->leftOperand->value / T->rightOperand->value;
        }
    }
    else if (T->type != OPERAND && T->leftOperand->type == OPERAND)
    {
        if (T->type == PLUS)
            return T->leftOperand->value + expressionEval(T->rightOperand);
        else if (T->type == MINUS)
            return T->leftOperand->value - expressionEval(T->rightOperand);
        else if (T->type == MUL)
            return T->leftOperand->value * expressionEval(T->rightOperand);
        else if (T->type == DIV)
        {
            if (expressionEval(T->rightOperand) == 0)
            {
                fprintf(stderr, "Error, 0 value in divisor\n");
            }
            return T->leftOperand->value / expressionEval(T->rightOperand);
        }
    }
    else if (T->type != OPERAND && T->rightOperand->type == OPERAND)
    {
        if (T->type == PLUS)
            return expressionEval(T->leftOperand) + T->rightOperand->value;
        else if (T->type == MINUS)
            return expressionEval(T->leftOperand) - T->rightOperand->value;
        else if (T->type == MUL)
            return expressionEval(T->leftOperand) * T->rightOperand->value;
        else if (T->type == DIV)
        {
            if (T->rightOperand->value == 0)
            {
                fprintf(stderr, "Error, 0 value in divisor\n");
            }
            return expressionEval(T->leftOperand) / T->rightOperand->value;
        }
    }
    else if (T->type != OPERAND)
    {
        if (T->type == PLUS)
            return expressionEval(T->leftOperand) + expressionEval(T->rightOperand);
        else if (T->type == MINUS)
            return expressionEval(T->leftOperand) - expressionEval(T->rightOperand);
        else if (T->type == MUL)
            return expressionEval(T->leftOperand) * expressionEval(T->rightOperand);
        else if (T->type == DIV)
        {
            if (expressionEval(T->rightOperand) == 0)
            {
                fprintf(stderr, "Error, 0 value in divisor\n");
            }
            return expressionEval(T->leftOperand) / expressionEval(T->rightOperand);
        }
    }

    return -1;
}
/**
 * inorderTraverse
 * 
 * prints with paraenthases
 * Depending on the type of term it will print out paraenthases amd proper values
 */
void inorderTraverse(FILE *out, TNode *T)
{
    printf("(");
    if (T == NULL)
    {
        return;
    }
    if (T->type != OPERAND && T->leftOperand->type == OPERAND && T->rightOperand->type == OPERAND)
    {

        if (T->type == PLUS)
            printf("(%d)+(%d)", T->leftOperand->value, T->rightOperand->value);
        else if (T->type == MINUS)
            printf("(%d)-(%d)", T->leftOperand->value, T->rightOperand->value);
        else if (T->type == MUL)
            printf("(%d)*(%d)", T->leftOperand->value, T->rightOperand->value);
        else if (T->type == DIV)
        {
            printf("(%d)/(%d)", T->leftOperand->value, T->rightOperand->value);
        }
    }
    else if (T->type != OPERAND && T->leftOperand->type == OPERAND)
    {
        if (T->type == PLUS)
        {
            printf("(%d)+", T->leftOperand->value);
            inorderTraverse(out, T->rightOperand);
            
        }
        else if (T->type == MINUS)
        {
            printf("(%d)-", T->leftOperand->value);
            inorderTraverse(out, T->rightOperand);
            printf(")");
        }
        else if (T->type == MUL)
        {
            printf("(%d)*", T->leftOperand->value);
            inorderTraverse(out, T->rightOperand);
            
        }
        else if (T->type == DIV)
        {
            printf("(%d)/", T->leftOperand->value);
            inorderTraverse(out, T->rightOperand);
            
        }
    }
    else if (T->type != OPERAND && T->rightOperand->type == OPERAND)
    {
        if (T->type == PLUS)
        {
            
            inorderTraverse(out, T->leftOperand);
            printf("+(%d)", T->rightOperand->value);
        }
        else if (T->type == MINUS)
        {
            
            inorderTraverse(out, T->leftOperand);
            printf("-(%d)", T->rightOperand->value);
        }
        else if (T->type == MUL)
        {
            
            inorderTraverse(out, T->leftOperand);
            printf("*(%d)", T->rightOperand->value);
        }
        else if (T->type == DIV)
        {
            
            inorderTraverse(out, T->leftOperand);
            printf("/(%d)", T->rightOperand->value);
        }
    }
    else if (T->type != OPERAND)
    {
        printf("(");
        if (T->type == PLUS)
        {
           
            inorderTraverse(out, T->leftOperand);
            printf("+");
            inorderTraverse(out, T->leftOperand);
        
        }
        else if (T->type == MINUS)
        {
            inorderTraverse(out, T->leftOperand);
            printf("-");
            inorderTraverse(out, T->leftOperand);
        }
        else if (T->type == MUL)
        {
           
            inorderTraverse(out, T->leftOperand);
            printf("*");
            inorderTraverse(out, T->leftOperand);
            
        }
        else if (T->type == DIV)
        {
            
            inorderTraverse(out, T->leftOperand);
            printf("/");
            inorderTraverse(out, T->leftOperand);
            
        }
    }
    printf(")");
}

/**
 * outputExpressionTree
 * 
 * recursivly runs through the tree getting values together
 * Finds the final value
 */
void outputExpressionTree(ExpT *T)
{

    TNode *node;
    StackObj *S = T;
    //printStack(S);
    // check if the expression tree is correct for evaluation
    // check overflow or underflow of operands
    if (stackSize(S) > 1)
    {
        fprintf(stderr, "ERROR extra operands in expression\n");
    }
    else
    {
        node = (TNode *)pop(S); // pop off the node to get access to it
        //print2DUtil(node, 0);
        inorderTraverse(stdout, node);
        printf(" = %d\n", expressionEval(node));
        push(S, node); // push the node back on so the stack retains the tree for deletion
    }
}

void inputExpressionTree(ExpT *T)
{

    char inputToken[MAX_TOKEN_LENGTH + 1];
    tokenType token;
    TNode *node, *op1, *op2;
    int tokenVal;
    StackObj *S;

    S = T;
    /**
     * Hey future jake
     * 
     * I changed this to an if statement but it used to be a while loop
     */
    while (scanf("%s", inputToken) > 0)
    {

        //printf("input token = %s\n", inputToken);

        token = convertToken(inputToken, &tokenVal);
        //printf( "converted token %d \n", token);
        if (token == OPERAND)
        {
            if ((node = newTNode(OPERAND, tokenVal, NULL, NULL)) == NULL)
                fprintf(stderr, "problem creating node\n");
            else
                push(S, (void *)node);
        }
        else
        {
            if ((op2 = pop(S)) == NULL)
            {
                fprintf(stderr, "sorry, out of operands for operators\n");
                exit(EXIT_FAILURE);
            }

            if ((op1 = pop(S)) == NULL)
            {
                fprintf(stderr, "sorry, out of operands for operator\n");
                exit(EXIT_FAILURE);
            }
            node = newTNode(token, 0, op1, op2);
            push(S, node);
        }
    }
}
