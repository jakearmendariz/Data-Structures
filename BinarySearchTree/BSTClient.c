
//---------------------------------------------------------------------
// BSTClient.c
//
// Jake Armendariz
// 1650932
// 12B
// Assignment 4
//
// Input oriented Test client for Binary Search Tree ADT
// see file BSTUI.h for definition of commands and acceptable input details.
// Handles all input, causes is an error if character is not graph
// Max input size for message is 150 characters
// Now has the abiltiy to delete indivual nodes
//---------------------------------------------------------------------
#define _POSIX_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "BST.h"
#include "BSTUI.h"
#include <strings.h>
/******************  function prototypes  *****************************/

void doQuit();
void showHelp();
void doErase(BSTObj **ptrT);
void doHeight(BSTObj *T);
void doHeight();
void doInsert(BSTObj **ptrT, char *arg);
void doPrint(BSTObj *T, char *order);
void doFind(BSTObj *T, char *term);
int inputLengthOK(char *inputStr);
int validCharacters(char *s);
void delete (char *term_to_be_deleted, BSTObj **ptrT);
/*
 * parseInput 
 *    Processes the text string input and divides the input into words that are 
 *    returned on w1, w2, w3
 *    This supports commands that have at most one argument:
 *    return the command in w1, first argument in w2, w3 for trailing junk
 *
 *    Return value indicates the outcome of parsing. Could be OK result which is command that
 *    was detected, e.g.
 *	  CMD_HELP
 *    of it could be an error was detected, e.g.
 *	  NO_ARGS_NEEDED	  
 *
 */
int parseInput(char *input, char *w1, char *w2, char *w3)
{
	int numArgs;

	/*
     * take the raw input string and read the contents to determine the action
     * fill in the argument if the command requires one.
     */

	// break the request up into words separated by whitespace

	numArgs = sscanf(input, "%s %s %s", w1, w2, w3);
	//printf("numArg = %d from sscanf w1 = %s, w2= %s, w3= %s\n",numArgs, w1, w2, w3);

	if (numArgs == EOF)
	{
		// no words, tell the user they can get help
		return CMD_NONE;
	}

	if (numArgs == 0)
	{
		// no words, tell the user they can get help
		return CMD_NONE;
	}
	//if they want a list of commands
	if (strcasecmp(CMD_HELP_STR, w1) == 0)
	{
		if (numArgs > 1)
		{
			return NO_ARGS_NEEDED;
		}
		else
		{
			return (CMD_HELP);
		}
	}
	//Erases the input
	if (strcasecmp(CMD_ERASE_STR, w1) == 0)
	{
		if (numArgs > 1)
		{
			return NO_ARGS_NEEDED;
		}
		return CMD_ERASE;
	}

	//Calls to end the program
	if (strcasecmp(CMD_QUIT_STR, w1) == 0)
	{
		if (numArgs > 1)
		{
			return NO_ARGS_NEEDED;
		}
		return CMD_QUIT;
	}

	if (strcasecmp(CMD_HEIGHT_STR, w1) == 0)
	{
		if (numArgs > 1)
		{
			return NO_ARGS_NEEDED;
		}
		return CMD_HEIGHT;
	}

	if (strcasecmp(CMD_INSERT_STR, w1) == 0)
	{
		if (numArgs > 2)
		{
			return EXTRA_ARG;
		}
		if (numArgs == 1)
		{
			return NEED_MORE_ARG;
		}
		if (validCharacters(w2) != 0)
		{
			return 111;
		}

		return CMD_INSERT;
		// your code here
	}

	if (strcasecmp(CMD_PRINT_STR, w1) == 0)
	{
		if (numArgs > 2)
		{
			return EXTRA_ARG;
		}

		return CMD_PRINT;
	}
	if (strcasecmp(CMD_DELETE_STR, w1) == 0)
	{
		if (numArgs > 2)
		{
			return EXTRA_ARG;
		}
		if (numArgs == 1)
		{
			return NEED_MORE_ARG;
		}
		return CMD_DELETE;
	}
	if (strcasecmp(CMD_FIND_STR, w1) == 0)
	{
		if (numArgs > 2)
		{
			return EXTRA_ARG;
		}
		if (numArgs == 1)
		{
			return NEED_MORE_ARG;
		}

		//Deletes a node

		return CMD_FIND;
	}
	// don't know what this is, doesn't match any commands

	return CMD_UNK;
}

/*
 * Parse the input, do the command or generate and error
 */
int main(int argc, char *argv[])
{
	BSTObj *T;
	char str[MAX_INPUT_LENGTH + 3]; // one more for one character over and null
	char cmdStr[MAX_INPUT_LENGTH + 1];
	char arg1[MAX_INPUT_LENGTH + 1];
	char arg2[MAX_INPUT_LENGTH + 1];
	char *inputStr;
	int action;
	int input_from_terminal;

	T = NULL;

	input_from_terminal = isatty(fileno(stdin));

	if (input_from_terminal)
		printf(COMMAND_PROMPT);

	// note that fgets reads the newline character "\n" and includes this in the string
	while ((inputStr = fgets(str, MAX_INPUT_LENGTH + 2, stdin)) != NULL)
	{

		//printf("fgets returned %s\n", inputStr);

		// check input line length
		if (!inputLengthOK(inputStr))
		{
			action = INPUT_TOO_LONG; // too big!
		}
		else
		{
			//printf("got request |%s|\n", inputStr);
			action = parseInput(inputStr, cmdStr, arg1, arg2);
			//printf("got action = %d\n", action);
		}
		//printf("%s\n", arg1);
		switch (action)
		{

		case CMD_NONE:
			break;
		case INPUT_TOO_LONG:
			printf(ERR_TOO_LONG, MAX_INPUT_LENGTH);
			break;
		case EXTRA_ARG:
			printf(ERR_EXTRA_ARG, arg1);
			break;
		case NEED_MORE_ARG:
			printf(ERR_NEED_ARG);
			break;
		case 111: //Invalid character
			printf(ERR_BAD_STR, validCharacters(arg1));
			break;
		case NO_ARGS_NEEDED:
			printf(ERR_NO_ARGS_NEEDED, cmdStr);
			break;
		case CMD_HELP:
			showHelp();
			break;
		case CMD_ERASE:
			doErase(&T);
			break;
		case CMD_QUIT:
			doQuit();
			break;
		case CMD_HEIGHT:
			doHeight(T);
			break;
		case CMD_INSERT:
			doInsert(&T, arg1);
			break;
		case CMD_DELETE:
			delete (arg1, &T);
			break;
		case CMD_PRINT:
			doPrint(T, arg1);
			break;
		case CMD_FIND:
			doFind(T, arg1);
			break;
		case CMD_UNK:
			printf(ERR_UNK_CMD, cmdStr);
			break;
		default:
			fprintf(stderr, "at default statement\n");
		}
		*arg1 = '\0';
		*arg2 = '\0';
		*cmdStr = '\0';

		if (input_from_terminal)
			printf(COMMAND_PROMPT);
	}
	makeEmpty(&T);
	exit(1);
}

/***************************************************************************************
 *
 * the functions that actually do the command requested by the user
 */

/**
 * Exits the program
 */
void doQuit()
{
	exit(0);
}

/**
 * Prints a message telling what the program cab do
 */
void showHelp()
{
	printf(HELP_MESSAGE);
}

/**
 * Deallocates everything
 */
void doErase(BSTObj **ptrT)
{
	makeEmpty(ptrT);
	printf(MSG_NONE);
}

void doHeight(BSTObj *T)
{
	printf("Height = %d\n", treeHeight(T, 0));
}

// insert the argument into the tree
void doInsert(BSTObj **ptrT, char *arg)
{
	// your code here
	if (insert(arg, ptrT) == 0)
	{
		printf(MSG_NONE);
	}
	else
	{
		printf(ERR_DUPLICATE, arg);
	}
}

// figure out which print the user wanted and do it
// if there is no ordering then use inorder as the default
void doPrint(BSTObj *T, char *order)
{
	if (T == NULL)
	{
		return; //printf("\n");
	}
	//	printf("Inside print method \n");
	if (strcasecmp(order, "inorder") == 0)
	{
		inorderTraverse(stdout, T);
	}
	else if (strcasecmp(order, "") == 0)
	{
		inorderTraverse(stdout, T);
	}
	else if (strcasecmp(order, "preorder") == 0)
	{
		preorderTraverse(stdout, T);
	}
	else if (strcasecmp(order, "postorder") == 0)
	{
		postorderTraverse(stdout, T);
	}
	else
	{
		printf(ERR_UNK_ARG, order);
	}
}

//Prints whether could find term or not
void doFind(BSTObj *T, char *term)
{
	if (T == NULL)
	{
		printf(ERR_NOT_FOUND, term);
	}
	else if (find(term, T) != NULL)
	{
		printf(MSG_FOUND, term);
	}
	else
	{
		printf(ERR_NOT_FOUND, term);
	}
	// your code here
}

//check if we have read past the allowed max, not that fgets passes the newline character in a string
// fgets does a read of MAX_INPUT_LENGTH + 1
int inputLengthOK(char *inputStr)
{

	int length = strlen(inputStr);

	if (length > MAX_INPUT_LENGTH)
	{
		char ch = '\0';
		while (ch != '\n')
		{
			ch = getchar();
		}
		return FALSE;
	}
	return TRUE;
}

/**
 * validCharcters
 *
 * @param s is the string to be checked
 * @returns 0 if the string is good and if not returns a 1
 * Traverses throiugh the string using the isgraph method
 */
int validCharacters(char *s)
{
	//printf("Inside validChars function\n");
	int count = 0;
	int length = strlen(s);
	//printf("String length: %d\n", (int)strlen(s));
	for (count = 0; count < length - 1; count++)
	{

		//This is the best way I have found of finding nongraphical characters
		//It took a lot of time and I am not sure if it is right
		if (s[count] == 94)
		{
			if (s[count + 1] == 'G' || s[count + 1] == 'A' || s[count + 1] == 'B' || s[count + 1] == 'C')
			{
				int a = s[count] + s[count + 1];
				a -= 158;
				return a;
			}
		}
	}
	return 0;
}
/**
 * delete
 * 
 * calls to delete and deallocate a node anywhere in tree
 * Returns a non-zero value if it doesn't worl
 */
void delete (char *term_to_find, BSTObj **T)
{
	if (*T == NULL)
	{
		printf(ERR_NOT_DELETED, term_to_find);
	}
	else if (deleteItem(term_to_find, T) == 0)
	{
		printf(MSG_DELETE, term_to_find);
	}
	else
	{
		printf(ERR_NOT_DELETED, term_to_find);
	}
}




