#include <stdio.h>
#include <stdlib.h>
#include "Blockchain.h"

int main(int argc,char* argv[]){
	if(argc != 2){
		fprintf(stderr, "Error, 2 arguments expected, one ouput file");
		exit(EXIT_FAILURE);
	}
	FILE* out;
	//Opens the file and makes sure its good
	out = fopen(argv[1], "w");
	if(out == NULL){
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
		
	}
	Blockchain chain = newBlockchain();
	char hackable[] = "one";
	fprintf(out, "putting in first block = %d\n", append(chain, hackable));
	printBlockchain(out, chain);
	
	fprintf(out,"putting in second block = %d\n", append(chain, "two"));
	printBlockchain(out, chain);
	
//	fprintf(out,"putting in third block %d\n", append(chain, "three"));
	fprintf(out, "putting in third block = %d\n", append(chain, "three"));
//	append(chain, "three");
	fprintf(out,"how many total blocks now? = %d\n", size(chain));
	printf("Got through append\n");
	printBlockchain(out, chain);
	fprintf(out, "find block 1\n");
	Block b =  get(chain, 1);
	printBlock(out, b);
	printBlockchain(out, chain);
	fprintf(out, "valid = %d", valid(chain));
	
	//Testing printBlock()
	fprintf(out, "printing each block through block print calls \n");
	for (int i = 0; i < size(chain); i++) {
		printBlock(out ,get(chain, i));
	}
	fprintf(out, "about to remove last block\n");
	removeLast(chain);
	fprintf(out,"removed last block\n");
	printBlockchain(out, chain);

	 // now break the chain
	  //  b = get(chain, 0);
	   //   char* value =  data(b);
	   //    (*value) = (*value)+1; // change a value in the first block
          //attempt to append to an invalid chain
        //   fprintf(out, "putting in block should have 3 in the chain, %d\n", append(chain, "five"));
         
	 fprintf(out, "after appending a 3rd element with name five\n");
               // just won't be able to invalidate it
        printf("Here?"); 
	fprintf(out,"after append and bad chain valid = %d\n", valid(chain));
	      printBlockchain(out, chain);
	
	fclose(out);
	return 0;
}
