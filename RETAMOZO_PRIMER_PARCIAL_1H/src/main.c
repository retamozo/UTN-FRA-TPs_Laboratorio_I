/*
 ============================================================================
 Name        : RETAMOZO_PRIMER_PARCIAL_1H.c
 Author      : ENZO RETAMOZO
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Client.h"

int main(void) {
	setbuf(stdout, NULL);
	Client clientArr[MAX_CLIENTS];
	int optionSelected;
//	int clientId;

	if(initClient(clientArr,MAX_CLIENTS) == 0) {
		do {
			if (getMenu(&optionSelected, 3, 1, 9) == 0) {
				switch(optionSelected){
					case 1:
					if (addClient(clientArr, MAX_CLIENTS) == 0) {
						printf("\nClient added succesfully \n");
					} else {
						printf("\nSorry, something went wrong.\n");
					}
					break;
					case 2:
					if(modifyClient(clientArr, MAX_CLIENTS) == 0){
						printf("\nSUCEES MODIFY CLIENT\n");
					} else {
						printf("\nSomething went wrong. Try again. \n");
					}
					break;
				 }
			}
		} while (optionSelected != 9);
	}


    printf("\n Thanks! Goodbye.");
	return EXIT_SUCCESS;

}
