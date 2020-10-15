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

#endif /* REPORTS_H_ */
