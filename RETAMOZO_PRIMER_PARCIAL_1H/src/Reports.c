#include "Client.h"
#include "utn.h"
#include "Advertisement.h"
#include "reports.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * \brief Prints all advertisement given a ID
 * \param Client *clientArr: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param Advertisement *addArr: Pointer to an Advertisement array
 * \param int addLen: Length of the array
 * \param int clientId: receive the ID to be search
 * \return (-1) if something went wrong, (0) if everything is OK
 */

int printClientAddsById(Client *clientArr, int clientLen, Advertisement *addArr, int addLen, int clientId) {
	int retorno=-1;
	int clientIndex;
	int addIndex;
	char bufferState[ADVERTISEMENT_STATE_LEN];
	if(clientArr!=NULL && clientLen > 0 && addArr != NULL && addLen > 0 && clientId >0){
		if(findClientById(clientArr, clientId, clientLen, &clientIndex)==0)	{
			printf("\n client ID : %d - Name: %s - Last Name: %s - CUIT: %s \n",
					clientArr[clientIndex].id, clientArr[clientIndex].name,
					clientArr[clientIndex].lastName, clientArr[clientIndex].cuit);
//			int findAddsByClientId(Advertisement *addArr, int addLEN, int clientId, int *pAddIndex);

			if (findAddsByClientId(addArr, addLen, clientArr[clientIndex].id, &addIndex) ==0 ){
				for(int i = 0; i < addLen; i++){
					if(addArr[i].state == "ACTIVA"){
						strncpy(bufferState, "ACTIVA", ADVERTISEMENT_STATE_LEN);
					} else {
						strncpy(bufferState, "PAUSADA", ADVERTISEMENT_STATE_LEN);
					} if(addArr[i].clientId == clientArr[clientIndex].id) {
						printf("\n Advertisement ID : %d - Estado: %s - texto: %s",addArr[i].clientId, bufferState, addArr[i].description);
					}
				}
			} else {
				printf("You don't have active advertisements.\n");
			}
			retorno=0;
		} else {
			printf("\nClient not foundn \n");
		}
	}
	return retorno;
}
