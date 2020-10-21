/*
 * Advertisement.h
 *
 *  Created on: Oct 15, 2020
 *      Author: Enzo
 */

#ifndef ADVERTISEMENT_H_
#define ADVERTISEMENT_H_
#include "Client.h"
#include "utn.h"

#define MAX_TEXT_ADD 65
#define CATEGORY_LEN 20
#define MAX_ADVERTISEMENT 1000
#define ADVERTISEMENT_STATE_LEN 8
#define CHANGE_TO_ACTIVE TRUE
#define CHANGE_TO_PAUSED FALSE


typedef struct{
	int addId;
	int clientId;
	int categoryCode;
	char description[MAX_TEXT_ADD];
	char state[10];
	int isEmpty;
	int isActive;
} Advertisement;


int printAddsByClientId(Advertisement *addArr, int clientId, int addLen);
int initAdvertisement(Advertisement *addArr, int addLEN);
int deleteAdvertisement(Advertisement *addArr, int addLEN, int addvertisementId);
int findAdvertisementByClientId(Advertisement *addArr, int len, int id);
int findActivesAdvertisements(Advertisement *addArr, int len);
int addNewAdvertisement(Advertisement *addArr, int addLen, Client *clientArr,  int clientLen);
int pauseAdvertisements(Advertisement *addArr, int len, Client *clientArr, int clientLen);
int pintAdvertisementsDetails(Advertisement *addArr, int addLen);
int findAdvertesimentByClientId(Advertisement *addArr, int len, int id, int *pResultado);
int helper_addCounterClient(Advertisement *addArr, int adLen, int id, int *pCounter, char desiredState[]);
int helper_addCounterForPausedOrActiveAdvertisements(Advertisement *adList, int adLen, int *pCounter, char desiredState[]);
int helper_addCounterByAdvertisementCategorie(Advertisement *adArray, int len, int categoryCode, int *pCounter);
int helper_findPausedAdvertisements(Advertisement *adArray, int len);
int reanudeAdvertisements(Advertisement *addArr, int len, Client *clientArr, int clientLen);
int helper_addCounterByAdvertisementCategorie(Advertisement *adArray, int len, int categoryCode, int *pCounter);
int sortByCategory(Advertisement *pArray,int len);

#endif /* ADVERTISEMENT_H_ */
