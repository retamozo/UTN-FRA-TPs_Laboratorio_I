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
#include "Advertisement.h"

int main(void) {
	setbuf(stdout, NULL);
	Client clientArr[MAX_CLIENTS];
	Advertisement addArr[MAX_ADVERTISEMENT];
	int optionSelected;
	int clientId;
	// NOTE: you should discomment these next 2 lines of code.


	if(initClient(clientArr,MAX_CLIENTS) == 0 && initAdvertisement(addArr, MAX_ADVERTISEMENT) == 0) {
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
					case 3:
//					int deleteClientAndAddsById(Client *clientArr, Advertisement *addArr, int clientId, clientLEN, addLEN)
						if(getNumber("\nPlease, add the ID of the client to delete\n", "\nError, invalid ID. Try again.\n", &clientId, 3,9,1) == 0) {
							if(deleteClientAndAddsById(clientArr, addArr, clientId, MAX_CLIENTS, MAX_ADVERTISEMENT) == 0){
							  printf("\n Adds by client ID n° %d has been deleted\n",clientId );
							} else {
							  printf("\n Something went wrong trying to delete a client and their adds.\n");
							}
						}

					break;
				 }
			}
		} while (optionSelected != 9);
	}


    printf("\n Thanks! Goodbye.");
	return EXIT_SUCCESS;

}
