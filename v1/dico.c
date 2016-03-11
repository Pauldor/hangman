#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dico.h"

int randMot(char *motPioche){
	FILE* dico = NULL;
	int nbrMot = 0, motChoisi =0, i = 0;
	int lettreLu = 0;

	dico = fopen("dico.paul", "r");
	
	if (dico == NULL){
		printf("bug, pas de dico");
		return 0;
	}

	do{
		lettreLu = fgetc(dico);
		if(lettreLu == '\n'){
			nbrMot++;
		}
	}while( lettreLu != EOF);


	motChoisi = alea(nbrMot);

	rewind(dico);
	while(motChoisi > 0){
		lettreLu = fgetc(dico);
		if(lettreLu == '\n'){
			motChoisi--;
		}
	}

	fgets(motPioche, 100, dico);
	motPioche[strlen(motPioche) - 1] = '\0';
	fclose(dico);

	return 1;
}

int alea(int max){
	srand(time(NULL));
	return (rand() % max);
}
