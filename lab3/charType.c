/**
 * Jake Armendariz
 * 1650932
 * January 25, 2019
 *
 * charType.c
 * This program will run through an input file and extract the numeric, alphabetic, punctuation and whitespace characters. It will tell the user how much was used and alot of other cool stuff :)
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>
void extract(char*s,char* a,char* d, char* p, char* w );

int main(int argc, char* argv[]){
	FILE* in;        // handle for input
 	FILE* out;       // handle for output
	char* line;      // string holding each line input
	/*
 	 * @param a is alphabetical characters
 	 * @param d is digits
 	 * @param p is punctuation
 	 * @param w is whitespace
 	 */
	char* a; char* d; char* p; char* w;
	// check command line for correct number of argument
	if( argc != 3 ){
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// open input file for reading
	if( (in=fopen(argv[1], "r"))==NULL ){
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	//Output file for reading
	if((out=fopen(argv[2], "w")) == NULL){
		printf("Unable to write to file %s\n", argv[2]);
	        exit(EXIT_FAILURE);
	}
	
	//Allocates memory for each string
	line = calloc(256, sizeof(char));
	a  = calloc(256, sizeof(char));
	d  = calloc(256, sizeof(char));
	p = calloc(256, sizeof(char));
	w = calloc(256, sizeof(char));
	//Keeps track of line number
	int counter = 0;
	//Calls extract onto every line of text in the input file. 
	//From there it prints out the contents into the output file :)
	//Based on number of characters detected it is plural or singular :)
	while(fgets(line, 255, in) != NULL){
		//printf("%s\n", line);
		counter++;
		extract(line, a, d, p, w);
		fprintf(out, "\nline %d contains:\n", counter);
		if(strlen(a) <= 1){
			fprintf(out,"%d alphabetical character: %s\n",(int)strlen(a), a);
		}
		else{
			 fprintf(out,"%d alphabetical characters: %s\n",(int)strlen(a), a);
		}
		if(strlen(d) <= 1){
                        fprintf(out, "%d numeric character: %s\n",(int)strlen(d), d);
                }
                else{
                         fprintf(out, "%d numeric characters: %s\n",(int)strlen(d), d);
                }
		if(strlen(p) <= 1){
                        fprintf(out, "%d punctuation character: %s\n",(int)strlen(p), p);
                }
                else{
                         fprintf(out, "%d punctuation characters: %s\n",(int)strlen(p), p);
                }
		if(strlen(w) <= 1){
                        fprintf(out, "%d whitespace character: %s\n",(int)strlen(w), w);
                }
                else{
                         fprintf(out, "%d whitespace characters: %s\n",(int)strlen(w), w);
                }

	}
	fprintf(out,"\n\n");

	//To end the program we free up the space to ensure no memory leakage and close the input,output
	fclose(in);
	fclose(out);
	free(line);
	free(a);
	free(d);
	free(p);
	free(w);
}

/**
 * @param char* s is the string that will be divided up into it's seperate parts
 * @param a is alphabetical characters
 * @param d is digits
 * @param p is punctuation
 * @param w is whitespace
 * extract breaks apart string s into a, d, p and w.
 * By the end of the program s will remain unchanged but the other strings will be full of correct contents
 */
void extract(char* s,char* a, char* d, char* p, char* w ){
	//i counts for string s, the others count for the corresponding strings
	int i = 0, one = 0, two = 0, three = 0, four = 0;
	//Sorts through string s, dividing up its parts into correct strings
	while(s[i] != '\0' && i < 255){
		if(isalpha((int)(s[i]))){
			a[one++] = s[i];
		}
		else if(isdigit((int)(s[i]))){
			d[two++] = s[i];
		}
		else if(ispunct((int)(s[i]))){
                       p[three++] = s[i];
                }
		else if(isspace((int)(s[i]))){
                        w[four++] = s[i];
                }
		i++;
	}
	//Ends each of the strings
	a[one] = '\0';
	d[two] = '\0';
	p[three] = '\0';
	w[four] = '\0';
}

