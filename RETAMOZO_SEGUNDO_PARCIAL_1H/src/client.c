/*
 * client.c
 *
 *  Created on: Nov 20, 2020
 *      Author: Enzo Retamozo
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utn.h"
#include "client.h"


Client* cli_add(void){
	Client buffArr;
	Client* this;
	if(!getString(CLI_GET_NAME_MESSAGE, CLI_GET_NAMES_ERROR_MESSAGE, buffArr.name, 3) &&
	   !getString(CLI_GET_LAST_NAME_MESSAGE, CLI_GET_NAMES_ERROR_MESSAGE, buffArr.lastName, 3) &&
	   !getCuitCode(CLI_GET_CUIT_MESSAGE, CLI_GET_CUIT_ERROR_MESSAGE, buffArr.cuit, 3, CUIT_LEN)){
		buffArr.clientId = cli_newId();
	}
	return buffArr;
}

Client* cli_new(){
	return (Client*)malloc(sizeof(Client));
}

void cli_delete(Client* this){
	free(this);
}

/** \brief Obtengo el id de un empleado
 * \param Client* this: Puntero del empleado
 * \param int* id: Pasaje por referencia del id del empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */

int cli_getId(Client* this, int* id){
	int _exit = -1;
	if(this!=NULL && id!=NULL){
		*id = this -> clientId;
		_exit = 0;
	}
	return _exit;
}

/** \brief Busca en la lista de clientes el maximo id y retorna ese valor + 1
 * \param LinkedList* this: Puntero a la LinkedList
 * \return (+1) id máximo encontrado | (-1) si algo salio mal
 */

int cli_searchMaxId(LinkedList* this){
	int _exit = -1;
	if(this != NULL){
		Client* buffCli;
		int* id;
		int maxId;
		int len = ll_len(this);
		for(int i = 0; i < len ; i++){
			buffCli = ll_get(this, i);
			employee_getId(buffCli, &id);
			if( i == 0 || id > maxId){
				maxId = id;
				_exit = maxId++;
			}
		}
	}
	return _exit;
}

