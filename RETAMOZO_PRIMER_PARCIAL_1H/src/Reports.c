#include "Client.h"
#include "utn.h"
#include "Advertisement.h"
#include "reports.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



/**
 * \brief Function to report the client with more ads, how many paused ads are, the sector number with more ads, client with more active ads and client with more paused ads
 * \param Client *clientArr: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param Advertisement *addArr: Pointer to an Advertisement array
 * \param int adLen: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int startReportMenu(Client *clientArr, int clientLen, Advertisement *addArr, int adLen){
	int retorno = -1;
	int option;
	if(clientArr!=NULL && clientLen >0 && addArr!=NULL && adLen > 0) {
			do{
				if(getNumber("\n REPORTS MENU\n"
							  "Please, choose an option\n"
							  "\n1)Client with more advertisements"
							  "\n2)Quantity of paused advertisements"
							  "\n3)Catgegory with more advertisements"
							  "\n4)Client with more actives advertisements"
							  "\n5)Client with more paused advertisements"
							  "\n7) Quantity "
							  "\n9) Find quantity of advertisements by entered category ID"
							  "\n6)Exit\n",
							  "\nERROR! Elija una opcion valida",
							  &option, 3, 10, 1) == 0) {
									switch(option) {
										case 1:
											if(report_clientWithMoreOrLessAdvertisements(clientArr, clientLen, addArr, adLen, 1) == 0){
												retorno = 0;
											}
											 break;
										case 2:
											if(helper_findPausedAdvertisements(addArr, adLen) ==0) {
												if(report_quantityOfPausedOrActiveAdvertisements(addArr,adLen, "PAUSADA") == 0){
													retorno = 0;
													}
											}
											else {
												printf("There are not paused advertisements.");
											}
											break;
										case 3:
											if(report_categoryWithMostAdvertisements(addArr, adLen)== 0){
												retorno = 0;
										    	}
											break;
										case 4:
											if(findActivesAdvertisements(addArr,adLen) == 0){
												if(report_clientWithMorePausedOrActiveAdvertisements(clientArr, clientLen, addArr, adLen, "ACTIVA") == 0){
													retorno = 0;
												}
											} else {
												printf("There are not actives advertisements to show.");
											}
											break;
										case 5:
											if(helper_findPausedAdvertisements(addArr, adLen) ==0) {
												if(report_clientWithMorePausedOrActiveAdvertisements(clientArr, clientLen, addArr, adLen, "PAUSADA") == 0){
													 retorno = 0;
											       } else {
													    printf("There are not paused advertisements.");
											       	 }
											 }
											 break;
										case 6:
											//	d) Imprimir lista de rubros ordenados de menor a mayor (sin repetir)
											break;
										case 7:
											//e) Cantidad de avisos activos totales OK
											if(findActivesAdvertisements(addArr,adLen) == 0){
											   if(report_quantityOfPausedOrActiveAdvertisements(addArr,adLen, "ACTIVA") == 0){
												  retorno = 0;
											   }
											}
										break;
										case 8:
											if(report_clientWithMoreOrLessAdvertisements(clientArr, clientLen, addArr, adLen, 2) == 0){
											   retorno = 0;
											}
										break;

										case 9:
											//g) Cantidad por rubro: Ingresar por consola un numero de rubro e imprimir la cantidad de avisos que existen de dicho rubro. ok
											if(report_categoryQuantityByPrompt(addArr,adLen) == 0 ) {
												  retorno = 0;

											}
											break;
										case 10:
											//h) Cantidad por cliente: Ingresar por consola un cuit e imprimir la cantidad de avisos que existen de dicho cliente.
											if(report_advertisementsByClientCuitPrompt(clientArr, clientLen, addArr, adLen) == 0){
												retorno = 0;
											}
										break;
									}
							}
				} while(option != 6);
		}
		return retorno;
}

int report_advertisementsByClientCuitPrompt(Client *clientArr, int clientLen, Advertisement *adArr, int adLen){
	int retorno=-1;
	int currentCounter;
	int maxCounter;
	char cuitNumber;
	Client clientIndex;
	if(clientArr!=NULL && clientLen> 0 && adArr!=NULL && adLen> 0 ){
		  if(getCuitCode("\n Please, add the client's CUIT code\n", "Invalid CUIT code. try again.\n", &cuitNumber, 3, CUIT_LEN) == 0){
			  printf("CUIT!!! > %c", cuitNumber);
			 if(helper_findClientIndexByCuit(clientArr, cuitNumber, clientLen, &clientIndex) == 0){
				for(int i=0; i<clientLen; i++){
					if(helper_addCounterClient(adArr, adLen, clientIndex.id, &currentCounter, "NORMAL_CLIENT_COUNTER") == 0 &&
						 ( i==0 || currentCounter > maxCounter)) {
						maxCounter = currentCounter;
							}
						}
					printf("--------------------------------------");
					printf("\nThe quantity of advertisements for CUIT n° %d is %d :\n ",cuitNumber, maxCounter);
					printf("--------------------------------------");
					retorno = 0;
			} else {
		  		  printf("\n This CUIT doesn't have any advertisement. \n");
		  }
		}
	  }
    return retorno;
}


/*Brief return the quantity number of the client with most advertisements (regardless if paused or unactive)
 * \param Client *clientArr: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param Advertisement *adArr: Pointer to an Advertisement array
 * \param int adLen: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 * */

int report_clientWithMoreOrLessAdvertisements(Client *clientArr, int clientLen, Advertisement *adArr, int adLen, int desiredQuantity){
	int retorno=-1;
	int currentCounter;
	int maxCounter;
	int lessCounter;
	Client bufferMax;
	if(clientArr!=NULL && clientLen> 0 && adArr!=NULL && adLen> 0 ){
	   if(desiredQuantity == 1){
		for(int i=0;i<clientLen;i++){
			if(helper_addCounterClient(adArr, adLen, clientArr[i].id, &currentCounter, "NORMAL_CLIENT_COUNTER") == 0 &&
					( i==0 || currentCounter > maxCounter)){
						maxCounter = currentCounter;
						bufferMax = clientArr[i];
					}
				}
				printf("\nClient with more advertisement is :\n ");
				printf("--------------------------------------");
				printf("\nCUIT: %s advertisements (quantity): %d \n", bufferMax.cuit, maxCounter);
				printf("--------------------------------------");
				retorno = 0;
	   } else {
		   if(desiredQuantity == 2){
				for(int i=0;i<clientLen;i++){
					if(helper_addCounterClient(adArr, adLen, clientArr[i].id, &currentCounter, "NORMAL_CLIENT_COUNTER") == 0 &&
							( i==0 || currentCounter < lessCounter)){
								lessCounter = currentCounter;
								bufferMax = clientArr[i];
							}
						}
				printf("\nClient with less advertisement is :\n ");
				printf("--------------------------------------");
				printf("\nCUIT: %s advertisements (quantity): %d \n", bufferMax.cuit, lessCounter);
				printf("--------------------------------------");
				retorno = 0;
		   }
	   }
	}
		return retorno;
}


/**
 * \brief Function to find the quantity of a determinated client with more paused or active advetisements, by an argument
 * \param Client *clientArr: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param Advertisement *adArr: Pointer to an Advertisement array
 * \param int adLen: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */

int report_clientWithMorePausedOrActiveAdvertisements(Client *clientArr, int clientLen, Advertisement *adArr, int adLen, char desiredStatus[]){
	int retorno=-1;
	int currentCounter;
	int maxCounter;
	Client bufferMax;
	if(clientArr!=NULL && clientLen> 0 && adArr!=NULL && adLen> 0 ){
	  if(strcmp(desiredStatus, "PAUSADA") == 0 ){
		  printf("ENTRE ACAAA");
			for(int i=0;i<clientLen;i++){
				if(helper_addCounterClient(adArr, adLen, clientArr[i].id, &currentCounter, "PAUSADA") == 0 && ( i==0 || currentCounter > maxCounter)){
					maxCounter = currentCounter;
					bufferMax = clientArr[i];
				}
			}
			printf("\nClient with more advertisement paused :\n ");
			printf("--------------------------------------");
			printf("\nCUIT: %s advertisements puased (quantity): %d \n", bufferMax.cuit, maxCounter);
			printf("--------------------------------------");
		retorno = 0;
	  } else {
		  if(strcmp(desiredStatus, "ACTIVA") ==0 ){
			for(int i=0; i< clientLen; i++) {
				helper_addCounterClient(adArr, adLen, clientArr[i].id, &currentCounter, "ACTIVA");
				if( i==0 || currentCounter > maxCounter){
					maxCounter = currentCounter;
					bufferMax = clientArr[i];
				}
			}
			printf("\nClient with more active advertisement :\n ");
			printf("--------------------------------------");
			printf("\nCUIT: %s active advertisements quantity: %d \n", bufferMax.cuit, maxCounter);
			printf("--------------------------------------");
			retorno = 0;
		  } else {
			  printf("\nYou don't have any paused advertisement.\n");
		  }
		}
	}
	return retorno;
}


/**
 * \brief Looking for the most categpry selected by quantity.
 * \param Advertisement *adArray: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return the index or (-1) if something went wrong
 */
int report_categoryWithMostAdvertisements(Advertisement *adArray, int len){
	int retorno=-1;
	int currentCounter = 0;
	int maxCounter;
	Advertisement advertisementBuffer;
	if(adArray != NULL && len > 0) {
		for(int i = 0; i < len; i++){
			if(adArray[i].isEmpty == FALSE && helper_addCounterByAdvertisementCategorie( adArray,len,adArray[i].categoryCode, &currentCounter)==0){
				if(i==0 || currentCounter>maxCounter){
					maxCounter = currentCounter;
					advertisementBuffer = adArray[i];
					retorno = 0;
				}
			}
		}
		printf("\nThe categorie with most advertisements is the categorory n° : %d\n", advertisementBuffer.categoryCode);
	}
	return retorno;
}

/**
 * \brief Returns the quantity of paused or active advertisements by an argument...
 * \param Advertisement *adArray: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return the index or (-1) if something went wrong
 */

int report_quantityOfPausedOrActiveAdvertisements(Advertisement *adArray, int len, char desiredState[]){
	int retorno=-1;
	int currentCounter = 0;
	int maxCounter;
	if(adArray != NULL && len > 0 ){
		if(strcmp(desiredState, "PAUSADA") == 0){
				for(int i = 0; i < len; i++){
					if(adArray[i].isEmpty == FALSE && helper_addCounterForPausedOrActiveAdvertisements( adArray,len, &currentCounter, "PAUSADA" )==0){
						if(i==0 || currentCounter>maxCounter){
							maxCounter = currentCounter;
							retorno = 0;
						}
					}
				}
				printf("\n--------------------------------------\n");
				printf("The quantity of paused advertisements is: %d", maxCounter);
				printf("\n--------------------------------------\n");

		} else {
			if(strcmp(desiredState, "ACTIVA") == 0){
				for(int i=0; i < len; i++) {
					if(helper_addCounterForPausedOrActiveAdvertisements(adArray, len, &currentCounter, "ACTIVA") ==0 ){
						if( i==0 || currentCounter > maxCounter){
							maxCounter = currentCounter;
							retorno = 0;
						}
					}
				}
				printf("\n--------------------------------------\n");
				printf("The quantity of active advertisements is :%d", maxCounter);
				printf("\n--------------------------------------\n");
			}
		}
	}
	return retorno;
}

/* TAREA
d) Imprimir lista de rubros ordenados de menor a mayor (sin repetir)
e) Cantidad de avisos activos totales OK
f) Cliente con menos avisos
g) Cantidad por rubro: Ingresar por consola un numero de rubro e imprimir la cantidad de avisos que existen de dicho rubro. ok
h) Cantidad por cliente: Ingresar por consola un cuit e imprimir la cantidad de avisos que existen de dicho cliente.
 * */

int report_categoryQuantityByPrompt(Advertisement *adArray, int len){
	int retorno=-1;
	int currentCounter = 0;
	int maxCounter;
	int categoryId;
	if(adArray != NULL && len > 0) {
		if(getNumber("\n Please, enter the category ID\n", "\nERROR! Wrong character. Just numbers.",  &categoryId, 3, 9, 1) == 0){
			for(int i = 0; i < len; i++){
				if(adArray[i].isEmpty == FALSE && helper_addCounterByAdvertisementCategorie(adArray,len, categoryId, &currentCounter)==0){
					if( i==0 || currentCounter > maxCounter){
						maxCounter = currentCounter;
						retorno = 0;
					}
				}
			}
			printf("\n The quantity of advertisiments with category %d is : %d\n", categoryId, maxCounter);
		}
	}
	return retorno;
}


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
	if(clientArr!=NULL && clientLen > 0 && addArr != NULL && addLen > 0 && clientId >0){
		if(findClientById(clientArr, clientId, clientLen, &clientIndex) ==0){
			if (findAdvertisementByClientId(addArr, addLen, clientArr[clientIndex].id) ==0 ){
				for(int i = 0; i < addLen; i++){
					if(addArr[i].clientId == clientArr[clientIndex].id) {
						printf(" ADDS FOR CLIENT ID° : %d" ,clientId);
						printf("-----------------------------------------------------------\n");
						printf("   CATEGORY  -   ID  -  DESCRIPCION   -   STATE \n");
						printf("-----------------------------------------------------------\n");
						printf("| %-5d| %-5d| %-30s| %-10s|\n",
								addArr[i].categoryCode,
								addArr[i].addId,
								addArr[i].description,
								addArr[i].state);
								printf("\n-----------------------------------------------------------\n");
					}
					retorno = 0;
				}
			} else {
				printf("You don't have active advertisements.\n");
			}

		} else {
			printf("\nClient not foundn \n");
		}
	}
	return retorno;
}

