/*
 * client.h
 *
 *  Created on: Nov 20, 2020
 *      Author: Enzo
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#define NAME_LEN 50
#define CUIT_LEN 14

/*Definición de mensajes útiles*/

#define CLI_ADD_NEW_MESSAGE "\n CLIENTE AÑADIDO EXITOSAMENTE\n"
#define CLI_ADD_NEW_ERROR_MESSAGE "\n LO SENTIMOS. OCURRIÓ UN ERROR TRATANDO DE CREAR EL CLIENTE.\n"
#define CLI_GET_NAME_MESSAGE "\n POR FAVOR, INGRESE SU NOMBRE\n"
#define CLI_GET_LAST_NAME_MESSAGE "\n POR FAVOR, INGRESE SU APELLIDO\n"
#define CLI_GET_NAMES_ERROR_MESSAGE "\n ERROR ! INTENTE DE NUEVO\n"
#define CLI_GET_CUIT_MESSAGE "\n POR FAVOR, INGRESE CUIT\n"
#define CLI_GET_CUIT_ERROR_MESSAGE "\n ERROR! INGRESE CUIT VÁLIDO.\n"


typedef struct{
	int clientId;
	char name[NAME_LEN];
	char lastName[NAME_LEN];
	char cuit[CUIT_LEN];
}Client;


Client* cli_add(void);
Client* cli_new();
void cli_delete(Client* this);
#endif /* CLIENT_H_ */
