#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "dico.h"
#include "title.h"
#include "pendu2.h"
#include "high.h"

int main(int argc, char *argv[]){
	debut();
	return 0;
}

void debut(){
	int choise = 0;
 
	system("clear");

	titre();
	menu();

	choise = lireLettre();

	switch(choise){
		case 49:
			credit();
			break;
		case 50:
			play();
			break;
		case 51:
			play2();
			break;
		case 52:
			high();
			break;
		case 53:
			system("clear");
			exit(0);
			break;
	}

}

char lireLettre(){
	int lettre = 0;
	lettre = getchar();
	lettre = toupper(lettre);
	while(getchar() != '\n');
	return lettre;
}

int gagne(int *lettreTrouve, int tailleMot){
	int i;
	int gagnee = 1;
	for (i = 0; i < tailleMot; i++){
		if(lettreTrouve[i] == 0){
			gagnee = 0;
		}
	}
	return gagnee;
}

int recherche(char lettre, char *motSecret, int *lettreTrouve){
	int i;
	int bonneLettre = 0;
	for(i = 0;motSecret[i] != '\0'; i++){
		if (lettre == motSecret[i]){
			bonneLettre = 1;
			lettreTrouve[i] = 1;
		}
	}
	return bonneLettre;
}

void play2(){
	char lettre = 0;
	char motSecret[100] = {0};
	int *lettreTrouve = NULL;
	int vie = 10;
	int i = 0;
	int tailleMot = 0;
	int rejouer = 89;
	int round = 1;
	char pseudo[100] = {0};
	int ok = 0;
	int faute = 0;
	char lettreNope[26] = {0};
	
	system("clear");

	printf("Rentrez votre mot secret : ");
	scanf("%s", motSecret);
	
	system("clear");

	while(motSecret[i]){
		motSecret[i] = toupper(motSecret[i]);
		i++;
	}

	tailleMot = strlen(motSecret);
	
	lettreTrouve = malloc(tailleMot * sizeof(int));

	if(lettreTrouve == NULL){
		//BUGG
		printf("dema2");
		exit(0);
	}
	

	for(i = 0; i < tailleMot; i++){
		lettreTrouve[i] = 0;
	}

	printf("%s", motSecret);
	
	//game

	do{
		if (round == 1){
			printf("Etes vous pret ?");
			getchar();
		}else{
			printf("Il te reste %d vie(s)\n", vie);
		//	for (i = 0;i < 26;i++)	
		//	if 
		//		printf("%c", lettreNope[i]);
		//	}
			for (i = 0; i < tailleMot; i++){
				if(!lettreTrouve[i]){
					printf("*");
				}else{
					printf("%c", motSecret[i]);
				}
			}
		}
		printf("\n");	
		if(round != 1){
			printf("une lettre : ");
			lettre = lireLettre();
		
			if(!recherche(lettre, motSecret, lettreTrouve) && round != 1){
				vie--;
				faute++;
//				while(lettreNope[i+1] != NULL){
//					lettreNope[i] = lettreTrouve;
//					i++;
//				}
			}else{
				ok++;
			}
		}
	round++;
	system("clear");
	}while(vie > 0 && !gagne(lettreTrouve, tailleMot));

	if(gagne(lettreTrouve, tailleMot)){
		printf("\ngg\n");
	}else{
		printf("\nperdu le mot ete : %s\n\n", motSecret);
	}
	
	printf("Ton nom : ");
	scanf("%s", pseudo); 

	printf("Tu sera sauvgarde dans les score sous le pseudo : %s\n", pseudo);

	//je m'occupe de l'heure
	
	time_t current_time;
	char* c_time_string;

	current_time = time(NULL);

    	if (current_time == ((time_t)-1))
    	{
        	(void) fprintf(stderr, "Failure to obtain the current time.\n");
	        exit(0);
   	}

	c_time_string = ctime(&current_time);

    	if (c_time_string == NULL)
    	{
        	(void) fprintf(stderr, "Failure to convert the current time.\n");
 		exit(0);
    	}
		
	highAdd(pseudo, faute, ok, c_time_string, motSecret);
	
	free(lettreTrouve);
	
	getchar();
	system("clear");

	addMot(motSecret);
	printf("Ton mot : %s sera sauvegarde :D\n", motSecret);
	debut();
}

void play(){
	char lettre = 0;
	char motSecret[100] = {0};
	int *lettreTrouve = NULL;
	int vie = 10;
	int i = 0;
	int tailleMot = 0;
	int rejouer = 0;
	char pseudo[100] = {0};
	int ok = 0;
	int faute = 0;
	system("clear");

	if(!randMot(motSecret)){
		exit(0);
	}

	tailleMot = strlen(motSecret);
	
	lettreTrouve = malloc(tailleMot * sizeof(int));

	if(lettreTrouve == NULL){
		//BUGG
		printf("dema2");
		exit(0);
	}
	

	for(i = 0; i < tailleMot; i++){
		lettreTrouve[i] = 0;
	}
		
	//game

	do{
		printf("Il te reste %d vie(s)\n", vie);
		for (i = 0; i < tailleMot; i++){
			if(!lettreTrouve[i]){
				printf("*");
			}else{
				printf("%c", motSecret[i]);
			}
		}
		printf("\n");	
		printf("une lettre : ");
		lettre = lireLettre();

		if(!recherche(lettre, motSecret, lettreTrouve)){
			vie--;
			faute++;
		}else{
			ok++;
		}
	system("clear");
	}while(vie > 0 && !gagne(lettreTrouve, tailleMot));

	if(gagne(lettreTrouve, tailleMot)){
		printf("\nWhoo ! TU AS GAGNE. Tu as trouve : %s !\n", motSecret);
	}else{
		printf("\nperdu le mot ete : %s\n\n", motSecret);
	}

	free(lettreTrouve);

	printf("Ton nom : ");
	scanf("%s", pseudo); 

	printf("Tu sera sauvgarde dans les score sous le pseudo : %s", pseudo);

	//je m'occupe de l'heure
	
	time_t current_time;
	char* c_time_string;

	current_time = time(NULL);

    	if (current_time == ((time_t)-1))
    	{
        	(void) fprintf(stderr, "Failure to obtain the current time.\n");
	        exit(0);
   	}

	c_time_string = ctime(&current_time);

    	if (c_time_string == NULL)
    	{
        	(void) fprintf(stderr, "Failure to convert the current time.\n");
 		exit(0);
    	}

	highAdd(pseudo, faute, ok, c_time_string, motSecret);
	
	getchar();
	system("clear");
	debut();
}
