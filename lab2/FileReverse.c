/**
 * Description
 *	In this c program I will intake strings from a file called "in" and output a 
 * the string in reverse. The program will intake the input and ouput files via a 
 * command in the terminal.
 *
 * Main contains a system to intake and output the strings, it calls upon the only 
 * function to handle the actual reversing.(Program can only handle words of <=256 char
 *
 * stringReverse(char* str)-- Reverses the string via the pointer
 *
 * @author
 * 	Jake Armendariz: 1650932
 * Class
 *	12M
 * Due
 *	Jan 22, 2019
 *
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/**
 * Reverses the string
 * @param str is to be reversed
 */
void stringReverse(char* str){
	int i, j = strlen(str)-1;
	for(i = 0; i <= strlen(str)/2;i++){
		//temp holds the str[i] value as it is being overwritten in next line
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		j--;
	}
}

/**
 * main method, takes two arguments that we will use
 * if the arguments are not valid files the program will terminate
 * if files are valid in will be left unchanged and out will contain its strings in reverse
 */
int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Usage: %s some-string\n", argv[0]);
                printf("Need an input file, then an output file");
                exit(EXIT_FAILURE);
	}
	
	//Prints the arguments. Uncomment when debugging :)
	for(int i = 0; i < argc; i++){
		//printf("%s\n", argv[i]);
	}
	//input and output files
	FILE* in;
	FILE* out;
	//This will hold the letters, if input has more than 256 characters an error
	//will occur
	char word[256];

	//opens the file, if null it will terminate program and print a message
	in = fopen(argv[1], "r");
	if(in == NULL){
                printf("Unable to read from file %s\n", argv[1]);
        	exit(EXIT_FAILURE);
        }
	 //opens the file, if null it will terminate program and print a message
	out = fopen(argv[2], "w");
        if(out == NULL){
                printf("Unable to read from file %s\n", argv[2]);
                exit(EXIT_FAILURE);
        }
	
	while( fscanf(in, " %s", word) != EOF ){
		stringReverse(word);
                fprintf(out, "%s\n", word);
                printf("%s\n", word);
         }
	//Closes the input and output files
	fclose(in);
	fclose(out);
	return 0;

}

