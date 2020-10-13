
/* Enzo Retamozo - 1er Parcial Laboratiorio de programación - 13/10/2020 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utn.h"
#include "Client.h"

static int createNewId(void);

/*
 *brief initialize every value of the array as empty.
 *param Client* pArray array to be analize.
 *param int len Lenght of the array
 *return 0: everything is OK. return -1: Failed.
 */

int initClient(Client *clientArr, int len){
	int retorno = -1;
		if (clientArr != NULL && len > 0) {
			for (int i = 0; i < len; i++) {
				clientArr[i].isEmpty = TRUE;
			}
			retorno = 0;
		}
	return retorno;
}

/**
 * \brief Given a Client type array and an client id, remove the desired client.
 * \param Client *clientArr: Pointer to a Client array
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \return (0) OK || (-1) FAILURE
*/
int deleteClient(Client *clientArr, int len, int id) {
	int retorno = -1;
	if(clientArr != NULL && len > 0 && isClientPositionUsed(clientArr, len) == 0) {
		int selectedOpt;
		int index;
		if(getNumber("\n You are about to delete a client. Do you want proced? 1 - YES | 2 - NO \n ", "\nError! Select a valid option.", &selectedOpt, 2, 1, 2) == 0 &&
			selectedOpt==1 &&
			findClientById(clientArr, len, id, &index) ==0 &&
			clientArr[index].isEmpty==FALSE &&
			index >=0 )	{
				clientArr[index].isEmpty = TRUE;
				retorno = 0;
		}
	}
	return retorno;
}

/*
 *brief Loop throught a Client array, looking for a 'isEmpty' field flaged as TRUE
 *param Client* clientArr. Employee pointer type for the array.
 *param int limit: Lenght of the clientArr.
 *param int * pResult pointer to place the found index.
 *return 0: everything is OK. return -1: Failed.
 */
int findFreeIndex(Client *clientArr, int limit, int *pResult) {
	int retorno = -1;
	int i;
	if (clientArr != NULL && limit > 0 && pResult != NULL) {
		for (i = 0; i < limit; i++) {
			if (clientArr[i].isEmpty == TRUE) {
				*pResult = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


/* \ Brief: given a Client array structure, creates a new client asking for Name, Last Name and Cuit number. Also, generates a dinamic ID number.
 * \ param Client *clientArr: a pointer with a Client structure.
 * \ param len: length of *clientArr
 * \ return (0) OK | (-1) ERROR
 * */


int addClient(Client *clientArr, int len){
	int retorno = -1;
	Client buffClient;
	if(clientArr != NULL && len > 0){
		int index;
		if(findFreeIndex(clientArr, len, &index) == 0 &&
		   index >= 0 &&
		   getString("\nPlease, add the client's name.\n", "Invalid name, try again.\n", buffClient.name, 3, NAMES_LEN ) == 0 &&
		   getString("\nPlease, add the client's last name.\n", "Invalid last name, try again.\n", buffClient.lastName, 3, NAMES_LEN ) == 0 &&
		   getCuitCode("\n Please, add the client's CUIT code\n", "Invalid CUIT code. try again.\n", buffClient.cuit, 3, CUIT_LEN) == 0 &&
		   checkIfCuitAlreadyExists(clientArr, len, buffClient.cuit, index) == 0
		){
			buffClient.id = createNewId();
			buffClient.isEmpty = FALSE;
			clientArr[index] = buffClient;
			retorno = 0;
			printClientDetails(&clientArr[index],len);
		}
	}
	return retorno;
};

/*
 *brief Loop through a Client array, looking for a 'isEmpty' field flaged as TRUE and the ID of the Client array matches with the given ID
 *param Client* clientArr. a array pointer with a Client structure.
 *param int id: Client's id to find.
 *param int limit: Lenght of pArray.
 *param int *pResult pointer to place the found index.
 * return (0) OK | (-1) ERROR
 */

int findClientById(Client *clientArr, int id, int limit, int *pResult) {
	int retorno = -1;
	if (clientArr != NULL && limit > 0 && id > 0 && pResult != NULL) {
		for (int i = 0; i < limit; i++) {
			if (clientArr[i].id == id && clientArr[i].isEmpty == TRUE) {
				*pResult = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Compare a new desired CUIT with a already created one, asking for Cuit and index.
 * \param Client *list: Pointer to a Client array
 * \param int len: Length of the array
 * \param char *cuit: Pointer of the cuit to compare
 * \param int index: receive the index of an already registered client (to skip)
 * \return (-1) if something went wrong or (0) if OK
 */
int checkIfCuitAlreadyExists(Client *clientArr, int len, char *cuit, int index){
	int retornar = 0;
	if(clientArr != NULL && len > 0) {
		for(int i = 0; i < len; i++) {
			if(i != index && strncmp(clientArr[i].cuit, cuit, CUIT_LEN)==0) {
				printf("\nCUIT already exists (CUIT found)\n");
				retornar = 1;
			}
		}
	}
	return retornar;
}

/* Brief - given a array with a Client structure (client previously initiated), find the Client by the Id, and let user modify her/his Client data.
 * param *clientArr - Client array pointer.
 * param len - Lenght of the clientArr
 * return (0) OK | (-1) FAILURE
 * */

int modifyClient(Client *clientArr, int len){
	int retorno = -1;
	if(clientArr != NULL && len > 0){
		int id;
		int index;
		Client buffClient;
		printClientDetails(clientArr,len);
		if(getNumber("\nPlease, add the ID of the client to modify\n", "\nError, invalid ID. Try again.\n", &id, 3,9,1) == 0 &&
		   findClientById(clientArr,id, len, &index ) == 0 &&
		   getString("\nPlease, enter the new client's name.\n", "Invalid name, try again.\n", buffClient.name, 3, NAMES_LEN ) == 0 &&
		   getString("\nPlease, enter the new client's last name.\n", "Invalid name, try again.\n", buffClient.name, 3, NAMES_LEN ) == 0 &&
		   getCuitCode("\n Please, add the client's CUIT code\n", "Invalid CUIT code. try again.\n", buffClient.cuit, 3, CUIT_LEN) == 0 &&
		   checkIfCuitAlreadyExists(clientArr,len,buffClient.cuit, index) == 0
		   ){
			 strncpy(clientArr[index].name, buffClient.name, NAMES_LEN);
			 strncpy(clientArr[index].lastName,buffClient.lastName, NAMES_LEN);
			 strncpy(clientArr[index].cuit, buffClient.cuit, CUIT_LEN);
			 retorno = 0;
	      } else {
	    	  printf("\n Error - client not found \n");
	      }
	 }
	return retorno;
}

/**
 * \brief This one prints all fields of a Client array structure
 * \param Client *list: Pointer to a Client array
 * \param int len: Length of the array
 * \return (0) OK | (-1) FAILURE
 */
int printClientDetails(Client *clientArr, int len) {
	int retorno = -1;
	if(clientArr) {
		for(int i=0;i<len;i++) {
			if(clientArr[i].isEmpty == FALSE){
				printf("\nID: %d - Name: %s - Last Name: %s - CUIT: %s\n", clientArr[i].id, clientArr[i].name, clientArr[i].lastName, clientArr[i].cuit);
				retorno = 0;
			}
		}
	}
	return retorno;
}


/**
 * \brief Loop through a Client array, and check if the isEmpty prop is false (which means a client exists)
 * \param Client *list: Pointer to a Client array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int isClientPositionUsed(Client *clientArr, int len) {
	int retornar = -1;
	if(clientArr != NULL && len > 0) {
		for(int i=0; i<len; i++) {
			if(clientArr[i].isEmpty == FALSE){
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}


static int createNewId(void){
	static int id = 0;
	id++;
	return id;
};
