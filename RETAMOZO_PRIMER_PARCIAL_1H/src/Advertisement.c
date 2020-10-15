#include <stdio.h>
#include <stdlib.h>
#include "Advertisement.h"
#include "Client.h"
#include "Reports.h"


/*
 *brief initialize every value of the array as empty.
 *param Advertisement* addArr array to be analize.
 *param int len Lenght of the array
 *return 0: everything is OK. return -1: Failed.
 */
int initAdvertisement(Advertisement *addArr, int addLEN){
	int retorno = -1;
		if (addArr != NULL && addLEN > 0) {
			for (int i = 0; i < addLEN; i++) {
				addArr[i].isEmpty = TRUE;
			}
			retorno = 0;
		}
	return retorno;
}

/*
 * \brief Function to find an Advertisement index receiving a client ID
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the id to be searched
 * \return the index or (-1) if something went wrong
 */


int findAddsByClientId(Advertisement *addArr, int addLEN, int clientId, int *pAddIndex) {
	int retornar = -1;
	if(addArr != NULL && addLEN > 0 && clientId > 0){
		for(int i=0;i < addLEN; i++) {
			if(addArr[i].clientId == clientId && addArr[i].isEmpty == FALSE &&  addArr[i].state == "ACTIVE") {
				*pAddIndex = i;
				retornar = 0;
				break;
			} else {
				printf("\n this client doesn't have any active advertisement. \n");
			}
		}
	}
	return retornar;
}


/**
 * \brief Function to remove an advertisement searched by ID
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \return (-1) if something went wrong, (0) if everything is OK
*/
int deleteAdvertisement(Advertisement *addArr, int addLEN, int addvertisementId) {
	int retornar = -1;
	if(addArr != NULL && addLEN > 0)	{
		int selectedOption;
		if(getNumber("\n Please, press 1 to confirm, or 0 to go back. \n: ", "\nError, please only 1 or 0: ", &selectedOption, 3, 9, 1) == 0 && selectedOption == 1) {
			for(int i=0;i < addLEN; i++) {
				if(addArr[i].addId == addvertisementId ) {
				addArr[i].isEmpty = TRUE;
				retornar = 0;
				break;
				}
			}
		}
	}
	return retornar;
}


int printAddsByClientId(Advertisement *addArr, int clientId, int addLen){
	int retorno = -1;
	if(addArr != NULL && clientId > 0 && addLen > 0 && findAddsByClientId(addArr, clientId, addLen) == 0 ){
		printf(" ADDS FOR CLIENT ID° : %d \n" ,clientId);
		printf("-----------------------------------------------------------\n");
		printf("   CATEGORY  -   ID  -  DESCRIPCION   -   STATE \n");
		printf("-----------------------------------------------------------\n");
		for(int i=0; i < addLen ;i++) {
			if(addArr[i].isEmpty == FALSE && addArr[i].clientId == clientId){
				printf("| %-14s| %-5d| %-65s| %-20s|\n",
			  	addArr[i].category,
				addArr[i].addId,
				addArr[i].description,
				addArr[i].state);
		        printf("\n-----------------------------------------------------------\n");
				retorno = 0;
			}
		}
	} else {
		printf("\nThis client doesn't have any advertisement.\n");
	}
	return retorno;
}



