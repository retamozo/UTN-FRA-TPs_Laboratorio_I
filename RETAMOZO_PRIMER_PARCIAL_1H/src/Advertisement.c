#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Advertisement.h"




static int idGenerate(void);

/**
 * \brief Function to auto-generate an ID
 * \return the id
 */
static int idGenerate(void)
{
	static int id=0;
	id = id+1;
	return id;
}
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
				addArr[i].isActive = FALSE;
			}
			retorno = 0;
		}
	return retorno;
}

/*
 * \brief Function to find an Advertisement index receiving a client ID
 * \param Advertisement *addArr: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the id to be searched
 * \return the index or (-1) if something went wrong
 */


int findAdvertisementByClientId(Advertisement *addArr, int len, int id){
	int retornar = -1;
	if(addArr != NULL && len > 0 && id > 0){
		for(int i=0;i<len;i++)	{
			if(addArr[i].clientId== id &&
					addArr[i].isEmpty==FALSE &&
					(addArr[i].isActive==TRUE || addArr[i].isActive==FALSE)){
				retornar = i;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Look for almost 1 active advertisement
 * \param Advertisement *adArray: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return (1) is there any active field TRUE or (0) if not
 */
int findActivesAdvertisements(Advertisement *addArr, int len){
	int retornar = -1;
	if(addArr != NULL && len > 0)	{
		for(int i=0; i<len; i++) {
			if(addArr[i].isActive == TRUE) {
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function pauses an advertisement by ID (change isActive field to FALSE)
 * \param Advertisement *addArr: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param Client *clientArr: Pointer to an Client array
 * \param int clientLen: Client array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */



int pauseAdvertisements(Advertisement *addArr, int len, Client *clientArr, int clientLen){
	int retorno = -1;
	int id;
	int clientIndex;
	int addIndex;
	int choosedOption;
	if(addArr != NULL && len > 0 && clientArr != NULL && clientLen > 0
		&& findActivesAdvertisements(addArr, len) == 0){
		if(getNumber("\n\nEnter the client id to see an advertisements details.\n ", "\nError! invalid character. try again \n ", &id, 3, 9, 1) == 0 &&
			findClientById(clientArr, len, id, &clientIndex) ==0 ) {
	     	printAddsByClientId(addArr, id, len);
			if(findAdvertesimentByClientId(addArr, len, id, &addIndex) == 0 &&
			   getNumber("\nAre you sure to pause this add? 1 - YES | 0 - NO \n" , "\nERROR! Enter 1 o 2 ", &choosedOption, 3, 9, 1) == 0
					&& choosedOption == 1)	{
				       addArr[addIndex].isActive = FALSE;
				       strcpy(addArr[addIndex].state, "PAUSADA");
				       retorno = 0;
			} else {
				printf("\nAdvertisement not found\n");
			}
		} else {
			printf("\nThis client doesn't exists.\n");
		}
	}
	return retorno;
}

/**
 * \brief Function to remove an advertisement searched by ID
 * \param Advertisement *addArr: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \return (-1) if something went wrong, (0) if everything is OK
*/
int deleteAdvertisement(Advertisement *addArr, int addLEN, int addvertisementId) {
	int retornar = -1;
	if(addArr != NULL && addLEN > 0)	{
		int selectedOption;
		if(getNumber("\n Please, press 1 to confirm, or 0 to go back. \n: ",
				"\nError, please only 1 or 0: ", &selectedOption, 3, 9, 1) == 0 &&
				selectedOption == 1) {
			for(int i=0 ; i < addLEN; i++) {
				if(findAdvertisementByClientId(addArr, addLEN, addvertisementId) > -1 ) {
				addArr[i].isEmpty = TRUE;
				}
			}
		 retornar = 0;
		}
	}
	return retornar;
}


/**
 * \brief Function to find an Advertisement index receiving a client ID
 * \param Advertisement *addArr: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the id to be searched
 * \return the index or (-1) if something went wrong
 */
int findAdvertesimentByClientId(Advertisement *addArr, int len, int id, int *pResultado){
	int retornar = -1;
	if(addArr != NULL && len > 0 && id > 0){
		for(int i=0;i<len;i++) {
			if(addArr[i].clientId==id && addArr[i].isEmpty==FALSE && (addArr[i].isActive==TRUE || addArr[i].isActive==FALSE)){
				*pResultado = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

int searchAvailableAdvertisementIndex(Advertisement *addArr, int len, int *pIndex) {
	printf("ENTRE A SEARHC");
	int retornar = -1;
	if(addArr != NULL){
		for(int i = 0; i < len; i++){
			if(addArr[i].isEmpty == TRUE){
				retornar = 0;
				*pIndex = i;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function pauses an advertisement by ID (change isActive field to FALSE)
 * \param Advertisement *addArr: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param Client *clientArr: Pointer to an Client array
 * \param int clientLen: Client array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */

int reanudeAdvertisements(Advertisement *addArr, int len, Client *clientArr, int clientLen){
	int retorno = -1;
	int id;
	int clientIndex;
	int addIndex;
	int choosedOption;
	if(addArr != NULL && len > 0 && clientArr != NULL && clientLen > 0
		&& findActivesAdvertisements(addArr, len) == 0){
		if(getNumber("\n\nEnter the client id to pause ", "\nError! invalid character. try again \n ", &id, 3, 9, 1) == 0 &&
			findClientById(clientArr, len, id, &clientIndex) ==0 ) {
	     	printAddsByClientId(addArr, id, len);
			if(findAdvertesimentByClientId(addArr, len, id, &addIndex) == 0 &&
			   getNumber("\nAre you sure to reanude this add? 1 - YES | 0 - NO \n" , "\nERROR! Enter 1 o 2 ", &choosedOption, 3, 9, 1) == 0
					&& choosedOption == 1)	{
				       addArr[addIndex].isActive = TRUE;
				       strcpy(addArr[addIndex].state, "PAUSADA");
				       retorno = 0;
			} else {
				printf("\nAdvertisement not found\n");
			}
		} else {
			printf("\nThis client doesn't exists.\n");
		}
	}
	return retorno;
}


int addNewAdvertisement(Advertisement *addArr, int addLen, Client *clientArr, int clientLen) {
	int retorno = -1;
	Advertisement buffer;
	int index;
	int clientIndex;
	int clientId;
	if(addArr != NULL && clientLen > 0 && searchAvailableAdvertisementIndex(addArr, addLen, &index) == 0 && index >= 0 &&
		getNumber("\nEnter the client ID: ", "\nERROR! Invalid character. Try again.\n: ", &clientId, 3, 9, 1) == 0 ) {
		  if(findClientById(clientArr, clientId, clientLen, &clientIndex) == 0) {
			if(getNumber("\nEnter categoryCode code:\n", "\nERROR! Only valid categoryCode codes : ", &buffer.categoryCode, 3, 9, 1) == 0 &&
		       getStringAlphanumeric("\nEnter a brief description for the new advisement.:\n", "\nERROR! Invalid characters \n: ", buffer.description, 3, MAX_TEXT_ADD)==0){
				buffer.addId = idGenerate();
				buffer.isEmpty = FALSE;
				buffer.isActive = TRUE;
				buffer.clientId = clientId;
				strcpy(buffer.state, "ACTIVA");
				addArr[index] = buffer;
				retorno = 0;
				printf("\n new Advertisement ID %d", addArr[index].addId);
	           }
		  } else {
			  printf("Sorry, but user with id n° %d doesn't exists.", clientId );
		  }
	  }
	return retorno;
}


int printAddsByClientId(Advertisement *addArr, int clientId, int addLen){
	int retorno = -1;
	if(addArr != NULL && clientId > 0 && addLen > 0 && findAdvertisementByClientId(addArr, clientId, addLen) == 0 ){
		printf(" ADDS FOR CLIENT ID° : %d \n" ,clientId);
		printf("-----------------------------------------------------------\n");
		printf("   CATEGORY  -   ID  -  DESCRIPCION   -   STATE \n");
		printf("-----------------------------------------------------------\n");
		for(int i=0; i < addLen ;i++) {
			if(addArr[i].isEmpty == FALSE && addArr[i].clientId == clientId){
				printf("| %-14d| %-5d| %-65s| %-20s|\n",
			  	addArr[i].categoryCode,
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

/**
 * \brief This one prints all fields of a Advertisement array structure
 * \param Client *addArr: Pointer to a addArr array
 * \param int addLen: Length of the array
 * \return (0) OK | (-1) FAILURE
 */
int pintAdvertisementsDetails(Advertisement *addArr, int addLen) {
	int retorno = -1;
	if(addArr != NULL) {
		for(int i=0; i < addLen;i++) {
			if(addArr[i].isEmpty == FALSE){
				printf("\n-Advertisement ID: %d"
						"\n-Client ID: %d "
						"\n-Description %s "
						"\nState : %s\n",
						addArr[i].addId,
						addArr[i].clientId,
						addArr[i].description,
						addArr[i].state);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 * \brief Helper function to add an counter given your condition. Essentially, the main condition behind this function s if the advertisement client id matches with the passed client id as argument.
 * \param Advertisement *adArray: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \param int *pCounter: Pointer of the counter
 * \return (-1) if something went wrong, (0) if everything is OK
 */

int helper_addCounterClient(Advertisement *addArr, int adLen, int id, int *pCounter, char desiredState[]) {
	int retornar=-1;
	if(addArr!=NULL && adLen>0)	{
	int counter = 0;
		for(int i=0;i < adLen; i++) {
			if(addArr[i].isEmpty == FALSE && addArr[i].clientId == id ){
				if(strcmp(desiredState, "ACTIVA") == 0 || strcmp(desiredState, "NORMAL_CLIENT_COUNTER") == 0 ) {
					counter++;
				}
				else {
					if(strcmp(desiredState, "PAUSADA") == 0 && addArr[i].isActive == FALSE && addArr[i].isEmpty == FALSE &&  strcmp(addArr[i].state, "PAUSADA") == 0 )	{
						counter++;
				       }
				    }
			    }
			}
	    *pCounter = counter;
		retornar = 0;
	}
	return retornar;
}

/**
 * \brief Helper function which returns an counter quantity for active or paused advertisement, flagged by an argument.
 * \param Advertisement *adArray: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \param int *pCounter: Pointer of the counter
 * \param char desiredState: should be PAUSADA or ACTIVA
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int helper_addCounterForPausedOrActiveAdvertisements(Advertisement *adList, int adLen, int *pCounter, char desiredState[]){
	int retornar=-1;
	int counter=0;
	if(adList!=NULL && adLen>0) {
		for(int i=0;i<adLen;i++) {
			if(adList[i].isActive == FALSE && strcmp(adList[i].state, "PAUSADA") == 0)	{
				counter++;
			} else {
				if(adList[i].isActive == TRUE && strcmp(adList[i].state, "ACTIVA") == 0){
				counter++;
				}
			}
		}
		*pCounter = counter;
		retornar=0;
	}
	return retornar;
}

/**
 * \brief Function to search in the advertisement array if there's any paused ad
 * \param Advertisement *adArray: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return (1) is there any active field TRUE or (0) if not
 */

int helper_findPausedAdvertisements(Advertisement *adArray, int len){
	int retornar = -1;
	if(adArray != NULL && len > 0)	{
		for(int i=0; i<len; i++) {
			if(adArray[i].isActive == FALSE && strcmp(adArray[i].state, "PAUSADA") == 0 ){
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}
/**
 * \brief This function adds 1 for every advertisement when the category id and a id passed as argument matches.
 * \param Advertisement *adArray: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return (1) is there any active field TRUE or (0) if not
 */
int helper_addCounterByAdvertisementCategorie(Advertisement *adArray, int len, int categoryCode, int *pCounter){
	int retorno = 1;
	if(adArray != NULL && len > 0){
		int counter = 0;
		for(int i = 0; i < len; i++){
			if(adArray[i].isEmpty == FALSE && adArray[i].categoryCode == categoryCode ){
				counter++;
				retorno = 0;
			}
		}
		*pCounter = counter;
	}
	return retorno;
}
