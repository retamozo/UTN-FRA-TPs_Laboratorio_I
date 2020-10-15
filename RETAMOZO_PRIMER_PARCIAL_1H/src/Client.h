/*
 * Client.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Enzo
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#define MAX_CLIENTS 100
#define NAMES_LEN 20
#define CUIT_LEN 14
#include "utn.h"
#include "Advertisement.h"

typedef struct {
	int id;
	int isEmpty;
	char name[NAMES_LEN];
	char lastName[NAMES_LEN];
	char cuit[CUIT_LEN];
} Client;

int initClient(Client *clientArr, int len);
int findClientById(Client *clientArr, int id, int limit, int *pResult);
int addClient(Client *clientArr, int len);
int modifyClient(Client *clientArr, int len);
int deleteClient(Client *clientArr, int id, int len);
int isClientPositionUsed(Client *clientArr, int len);
int findFreeIndex(Client *clientArr, int limit, int *pResult);
int printClientDetails(Client *clientArr, int len);
int checkIfCuitAlreadyExists(Client *clientArr, int len, char *cuit, int index);
void addClient_FORCED(Client *clientArr, int arrLen);
int deleteClientAndAddsById(Client *clientArr, Advertisement *addArr, int clientId, int clientLEN, int addLEN);

#endif /* CLIENT_H_ */
