/*
 * Advertisement.h
 *
 *  Created on: Oct 15, 2020
 *      Author: Enzo
 */

#ifndef ADVERTISEMENT_H_
#define ADVERTISEMENT_H_
#include "utn.h"

#define MAX_TEXT_ADD 65
#define CATEGORY_LEN 20
#define MAX_ADVERTISEMENT 1000
#define ADVERTISEMENT_STATE_LEN 8

typedef struct{
	int addId;
	int clientId;
	char category[CATEGORY_LEN];
	char description[MAX_TEXT_ADD];
	char state[10];
	int isEmpty;
} Advertisement;

int printAddsByClientId(Advertisement *addArr, int clientId, int addLen);
int findAddsByClientId(Advertisement *addArr, int addLEN, int clientId, int *pAddIndex);
int initAdvertisement(Advertisement *addArr, int addLEN);
#endif /* ADVERTISEMENT_H_ */
