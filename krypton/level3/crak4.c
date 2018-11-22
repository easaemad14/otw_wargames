#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void plets(int plets[26]){
	int i;
	char c = 'A';

	puts("Single letters:");
	for(i = 0; i < 26; i++){
		printf("%c = %i\n", c, plets[i]);
		c++;
	}
}

void pbigram(int pbigram[26][26]){
	int i, j;
	char cr = 'A', cc;

	puts("\nBigrams:");
	for(i = 0; i < 26; i++){
		cc = 'A';
		for(j = 0; j < 26; j++){
			printf("%c%c = %i\n", cr, cc, pbigram[i][j]);
			cc++;
		}
		cr++;
	}
}

int main(int argc, char *argv[]){
	FILE *fin;
	char *fname;
	int i, j, c1, c2;
	int lets[26];
	int bigram[26][26];
    
	/*
	 * Initialize variables
	 */
	//lets
        for(i = 0; i < 26; i++)
		lets[i] = 0;

	//bigram
	for(i = 0; i < 26; i++)
		for(j = 0; j < 26; j++)
			bigram[i][j] = 0;

	/*
	 * Open files and call count funtions for each map
	 */
        for(i = 1; i < argc; i++){
		fname = argv[i];
		if((fin = fopen(fname, "r")) == NULL)
			goto openerr;

		//Gonna do these one at a time for simplicity
		for(c1 = fgetc(fin); c1 != EOF; c1 = fgetc(fin)){
			//All capital letters in my found files
			if(isupper(c1))
				lets[c1%65] += 1;
		}

		//Let's rewind and do it again
		rewind(fin); //Same as fseek(fin, 0, SEEK_SET);
		c1 = fgetc(fin);
		if(c1 == EOF)
			continue; //No need to fgetc for c2

		for(c2 = fgetc(fin); c2 != EOF; c2 = fgetc(fin)){
			if(isupper(c1) && isupper(c2))
				bigram[c1%65][c2%65] += 1;
			c1 = c2;
		}

		fclose(fin);
        }

	plets(lets);
	pbigram(bigram);
	return 0;

openerr:
	printf("Unable to open file %s\n", fname);
	exit(1);
}
