/*
 * Reports.h
 *
 *  Created on: Oct 13, 2020
 *      Author: Enzo
 */

#ifndef REPORTS_H_
#define REPORTS_H_
#include "utn.h"
#include "Client.h"
#include "Advertisement.h"

int printClientAddsById(Client *clientArr, int clientLen, Advertisement *addArr, int addLen, int clientId);
int startReportMenu(Client *clientArr, int clientLen, Advertisement *addArr, int adLen);
int report_categoryWithMostAdvertisements(Advertisement *adArray, int len);
int report_clientWithMoreOrLessAdvertisements(Client *clientArr, int clientLen, Advertisement *adArr, int adLen, int desiredQuantity);
int report_clientWithMorePausedOrActiveAdvertisements(Client *clientArr, int clientLen, Advertisement *adArr, int adLen, char desiredStatus[]);
int report_quantityOfPausedOrActiveAdvertisements(Advertisement *adArray, int len, char desiredState[]);
int report_categoryQuantityByPrompt(Advertisement *adArray, int len);
int report_advertisementsByClientCuitPrompt(Client *clientArr, int clientLen, Advertisement *adArr, int adLen);
#endif /* REPORTS_H_ */
