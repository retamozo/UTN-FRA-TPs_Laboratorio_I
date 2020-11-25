/*
 * controller_addClient.c
 *
 *  Created on: Nov 20, 2020
 *      Author: Enzo
 */

#ifndef CONTROLLER_CLIENT_C_
#define CONTROLLER_CLIENT_C_
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "LinkedList.h"
#include "utn.h"
#include "client.h"
#include "controller.h"

/*	Brief: Añadir un empleado.
 *	param Linkedlist* this: puntero a la LinkedList.
 *	return 0 (si la función fue exitosa) | -1 (falló)
 * */

int controller_addClient(LinkedList* this){
	int _exit = -1;
	if(this != NULL){
		Client buffCli; = cli_add();
		if(ll_map(this, cli_findByCuit, buffCli -> cuit) == 0){
			cli_saveId(CLI_PATH_ID, buffCli -> clientId);
			ll_add(this, buffCli);
			_exit = 0;
		} else {
			printf(CLI_ADD_NEW_ERROR_MESSAGE);
		}
	}
	return _exit;
}


#endif /* CONTROLLER_CLIENT_C_ */
