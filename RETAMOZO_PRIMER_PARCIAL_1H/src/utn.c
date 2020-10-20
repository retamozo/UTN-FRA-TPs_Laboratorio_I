/*
 * utn.c
 *
 *
 *      Author: Enzo Retamozo - UTN Libreria de funciones comunes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#define LIMITE_STRING 4059

static int isFloat(char *arrays, int limite);
static int isNumericChar(char *cadena);
static int getInt(int *pResultado);
static int getFloat(float *pFloat);
static int isValidCuit(char cuit[]);
static int checkAlphaNum(char* string, int len);

/**
 * \brief utn_getAlphaNum: Asks the user for an alphanumeric value
 * \param char* message: Message for the user
 * \param char* errMessage: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \param int len: length allowed for the value entered.
 * \return (-1) Error / (0) Ok
 */

int getStringAlphanumeric(char* message, char* errMessage, char* pValue,int retries, int len){
	char bufferString[len];
	int retorno = -1;

	if(message != NULL && errMessage != NULL && pValue != NULL && retries >= 0 && len > 0){
		do {
			printf("%s",message);
			if(myGets(bufferString, len) == 0 &&
			   strnlen(bufferString,sizeof(bufferString)-1)<= len &&
			   checkAlphaNum(bufferString,len) == 0 ) {
				strncpy(pValue,bufferString,len);
				retorno = 0;
				break;
			} else 	{
				printf("%s Quedan %d reintentos\n",errMessage, retries);
				retries--;
			}
		} while(retries >= 0);
	}
	return retorno;
}

/**
 * \brief checkAlphaNum: Checks the string for invalid characters
 * Allows upper and lower case letters, numbers and spaces
 * \param char* string: Pointer to string to check
 * \param int len: max lenght allowed of the string
 * \return (-1) Error / (0) Ok
 */

static int checkAlphaNum(char* string, int len){
	int retorno = 0;
	if(string != NULL && len > 0) {
		for(int i=0; i<=len && string[i] != '\0';i++) {
			if((string[i] != ' ') &&
			   (string[i] != '.') &&
			   (string[i] != '-') &&
			   (string[i] != '@') &&
			   (string[i] < 'a' || string[i] > 'z') &&
			   (string[i] < 'A' || string[i] > 'Z') &&
			   (string[i] < '0' || string[i] > '9')){
				retorno = -1;
				break;
			}
		}
	}
	return retorno;
}


/**
 * \brief convierte la cadena recibida en un número entero.
 * \param puntero con el string validado.
 * \return 0: ok. return -1: fallo.
 */

static int getInt(int *pResultado) {
	int retorno = -1;
	char buffer[4096];
	if (myGets(buffer, sizeof(buffer)) == 0 && isNumericChar(buffer)) {
		retorno = 0;
		*pResultado = atoi(buffer);
	}
	return retorno;
}

/*
 * \brief valida que la cadena recibida sea un número entero.
 * \param puntero con la cadena validada.
 * \return 1: true, si es un número entero.Return 0: false, no lo es.
 */

static int isNumericChar(char *cadena) {
	int retorno = 1;
	int i = 0;
	if (cadena[0] == '-') {
		i = 1;
	}
	for (; cadena[i] != '\0'; i++) {
		if (cadena[i] > '9' || cadena[i] < '0') {
			retorno = 0;
			break;
		}
	}
	return retorno;

}
/*
 * brief : Solicita un numero flotante al usuario.
 * pResultado : puntero con el valor validado.
 * mensaje : El mensaje que imprime para pedir un valor.
 * mensajeError: mensaje que impreso si el rango no es valido.
 * minimo : valor minimo valido
 * maximo : valor maximo valido
 * Reintentos: cantidad de veces que tiene el usuario para ingresar un valor valido
 * Return 0= OK.Return -1: error.
 */

int getNumberFloat(float *pResultado, char *mensaje, char *mensajeError,
		float minimo, float maximo, int reintentos) {
	int retorno = -1;
	float bufferFloat;
	int resultadoScan;
	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL
			&& minimo <= maximo && reintentos > 0) {
		do {
			printf("%s", mensaje);
			fflush(stdin);
			resultadoScan = getFloat(&bufferFloat);
			if (resultadoScan && minimo <= bufferFloat && maximo >= bufferFloat) {
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			} else {
				printf("%s", mensajeError);
				printf("\n-REINTENTOS: %d \n", reintentos);
				reintentos--;
			}

		} while (reintentos >= 0);
	}
	return retorno;
}

/*
 * getFloat: verifica si la cadena ingresada es flotante
 * pFloat: puntero numero float
 * Return 1: OK. return 0:error.
 *
 */

static int getFloat(float *pFloat) {
	int retorno = 0;
	char bufferFloat[5000];
	if (pFloat != NULL) {
		fflush(stdin);

		if (!myGets(bufferFloat, sizeof(bufferFloat)) && isFloat(bufferFloat, sizeof(bufferFloat))) {
			*pFloat = atof(bufferFloat);
			retorno = 1;
		}
	}
	return retorno;
}

/*
 * isFloat: Verifica si la cadena ingresada es flotante
 * cadena: cadena de caracteres a ser analizada
 * limite: limite de la cadena
 * Return: 1 (verdadero) si la cadena es flotante , 0 (falso) si no y -1 en caso de ERROR de parametro
 */

static int isFloat(char *floatArr, int limite) {
	int retorno = -1;
	int i = 0;
	int contadorDePuntos = 0;

	if (floatArr != NULL && limite > 0) {
		retorno = 1;
		if (floatArr[0] != '+' || floatArr[0] != '-') {
			i = 1;
		}
		while (floatArr[i] != '\0') {
			if ((floatArr[i] < '0' || floatArr[i] > '9')
					&& floatArr[i] != '.') {
				retorno = 0;
				break;
			}
			if (floatArr[i] == '.') {
				contadorDePuntos++;
				if (contadorDePuntos > 1) {
					retorno = 0;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}

/*
 * \brief valida que la cadena recibida sea un string valido.
 * \param char mesaje: Mensaje impreso para obtener una cadena
 * \param char mensajeError: mensaje impreso para notificar que la cadena no cumple con las condiciones.
 * \param espacio en memoria donde copiaremos la cadena previamente validada.
 * \param int reintentos: cantidad de veces que el usuario puede volver a intentar ingresar un valor valido.
 * \param int limite: longitud de la cadena.
 * \return -1: failed  Return 0:Ok.
 */

int getString(char mensaje[], char mensajeError[], char pResultado[], int reintentos, int limite) {
	int retorno = -1;
	char bufferChar[LIMITE_STRING];

	if (mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos > 0) {
		do {
			printf("%s", mensaje);
			if(myGets(bufferChar, LIMITE_STRING) == 0 && isString(bufferChar, LIMITE_STRING) == 1 && strnlen(bufferChar, sizeof(bufferChar)) < limite)	{
				retorno = 0;
				strncpy(pResultado, bufferChar, limite);
				break;
			} else {
			  printf("%s", mensajeError);
			reintentos--;
		  }
	   } while (reintentos >= 0);
	}
	return retorno;
}

/*
 *brief verifica que una cadena este en el rango de caracteres para ser un nombre valido.
 *param char cadena Cadena a ser analizada
 *param int limite longitud de la cadena.
 *return 0: failed . return 1: nombre valido.
 */

int isString(char cadena[], int limite) {
	int respuesta = 1;
	for (int i = 0; i <= limite && cadena[i] != '\0'; i++) {

		if ((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			 cadena[i] != '.') {
			 	 respuesta = 0;
				 break;
		}
	}
	return respuesta;
}

/*
 *brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena un maximo de 'longitud -1' caracteres.
 *param char cadena: Cadena a  analizar
 *param int longitud Define el tamaño maximo de la cadena
 *return (0) OK || (-1) FAIL
 */

int myGets(char cadena[], int longitud) {
	int retorno = -1;

	if (cadena != NULL && longitud > 0 && fgets(cadena, longitud, stdin) == cadena) {
		fflush(stdin);
			if ( cadena[strlen(cadena)- 1] == '\n' && cadena[0] != '\n') {
				cadena[strlen(cadena) - 1] = '\0';
			}
		retorno = 0;
	}
	return retorno;
}

/*
 * \brief Mediante el ingreso de los parametros mencionados debajo, pide y realiza la validación de un número entero.
 * \param char*mensaje: pide  un número entero.
 * \param char * mensajeError: mensaje de error en caso de que las condiciones no se cumplan.
 * \param int* pResultado: puntero con el numero adquirido
 * \param int reintentos: veces en las que el usuario podra volver a ingresar un valor valido.
 * \param int maximo: valor maximo a introducir
 * \param int minimo: valor minimo a introducir.
 * \return 0 si ha salido ok. -1 si no.
 */

int getNumber(char mensaje[], char  mensajeError[], int *pResultado, int reintentos, int maximo, int minimo) {
	int retorno = -1;
	int bufferInt;

	if (mensaje != NULL && mensajeError != NULL && pResultado != NULL
			&& reintentos >= 0 && maximo >= minimo) {
		do {
			printf("%s", mensaje);

			if (getInt(&bufferInt) == 0 && bufferInt >= minimo	&& bufferInt <= maximo) {
				retorno = 0;
				*pResultado = bufferInt;
				break;
			} else {
				printf("%s", mensajeError);
				reintentos--;
			}
		} while (reintentos >= 0);
	}
	return retorno;
}

int getCuitCode(char msg[], char msgError[], char pResult[], int attemps, int limit) {
	int retorno = -1;
	char bufferString[LIMITE_STRING];
	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0) {
		do {
			printf("%s", msg);
			if(myGets(bufferString, LIMITE_STRING) == 0 &&
			   isValidCuit(bufferString) == 1) {
				strncpy(pResult,bufferString, limit);
				retorno = 0;
				break;
			} else {
				printf("%s", msgError);
				if(attemps > 0)	{
					printf("Le quedan %d intentos\n", attemps);
				}
				attemps--;
			}
		} while(attemps >= 0);
	}
	return retorno;
}

/* \Brief : in order to mimic a Argentinian CUIT code number , this fn evaluates if the string passed as arg matches with the simulated CUIT code mask
 * \param pResult: CUIT code
 * */
static int isValidCuit(char cuitCode[]) {
	int retorno;
	if(cuitCode != NULL && strlen(cuitCode) > 0 && cuitCode[2] == '-' && cuitCode[11] == '-' && cuitCode[12] != '\0')	{
		int dashCounter=0;
		retorno = 1;
		for(int i = 0;cuitCode[i] != '\0'; i++) {
			if(cuitCode[i] == '-') {
				dashCounter++;
			}
			if(dashCounter > 2 || ((cuitCode[i] < '0' || cuitCode[i] > '9') && cuitCode[i] != '-')){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int getMenu(int *pResult, int attemps, int min, int max) {
	int retorno = -1;
	char bufferString[LIMITE_STRING];
	int bufferInt;

	if(pResult != NULL && attemps >= 0 && min <= max){
		do {
			printf("\nWelcome ! Please, choose one of the available options below.");
			printf( "\n1) Add new client "
					"\n2) Modify client "
					"\n3) Delete a client "
					"\n4) Share a new advertisiment "
					"\n5) Frezze advertisiments "
					"\n6) Resume advertisiments "
					"\n7) Print clients "
					"\n8) Reports menu "
					"\n9) Exit"
					"\n");

			if(myGets(bufferString, LIMITE_STRING) == 0 && isNumericChar(bufferString) == 1) {
				bufferInt = atoi(bufferString); //convert string to integer !
				if(bufferInt >= min && bufferInt <= max)	{
					*pResult = bufferInt;
					retorno = 0;
					break;
				} else {
					printf("\nError! Please, pick a valid option.\n");
					attemps--;
				}
			} else {
				printf("\nError! Please select a valid option \n. ");
				attemps--;
			}
		} while(attemps >= 0);
	}
	return retorno;
}
