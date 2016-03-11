#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "high.h"
#include "pendu2.h"
#include <ctype.h>

int highAdd(char *pseudo, int fautes, int ok, char *time, char *mot){
	FILE* high = NULL;
	high = fopen("high.paul", "a");
	float ratio = 0;
	int taillePseudo = 0;
	int i;
	char *espace = " ";
	if(high == NULL){
		printf("pas de fichier highscore");
		return 0;
	}
	
	taillePseudo = strlen(pseudo);

	fprintf(high ,"%s", pseudo);

	for(i=0; i < (20 - taillePseudo); i++){
		fprintf(high ,"%s", espace);
	}

	fprintf( high, ",fautes : %d",fautes);
	if (fautes > 10){
		fprintf(high," ,");
	}else{
		fprintf(high,"   ,");
	}
	fprintf( high,"ok : %d",ok);
	
	if (ok > 10){
		fprintf(high,",");
	}else{
		fprintf(high,"   ,");
	}

	fprintf(high,"%s , %s\n", mot,  time); 	

	fclose(high);
	}

void high(){
	system("clear");
	printf("Ici sont tous les score des joueurs (dans un ordre aleatoire :/) :\n\n");

	int c;
	FILE *file;
	file = fopen("high.paul", "r");
	if (file) {
   		while ((c = getc(file)) != EOF)
		        printf("%c", c);
   	 fclose(file);
	}
		
	getchar();
	debut();
}

void addMot(char *motSecret){
	FILE* dico = NULL;
	dico = fopen("dico.paul", "a");



	if (dico == NULL){
		printf("pas de dico");
		exit(0);
	}

	fprintf(dico,"%s\n", motSecret);
	fclose(dico);
}
