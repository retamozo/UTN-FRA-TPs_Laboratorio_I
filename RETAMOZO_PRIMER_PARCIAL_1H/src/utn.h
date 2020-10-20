/*
 * utn.h
 * Prototipos de las funciones auxiliares
 */

#ifndef UTN_H_
#define UTN_H_
#define TRUE 1
#define FALSE 0

int isString(char cadena[], int limite);
int myGets(char cadena[], int longitud);
int getString(char mensaje[], char mensajeError[], char pResultado[], int reintentos, int limite);
int getNumber(char *mensaje, char *mensajeError, int *pResultado, int reintentos, int maximo, int minimo);
int getNumberFloat(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int reintentos);
int getCuitCode(char msg[], char msgError[], char pResult[], int attemps, int limit);
int getMenu(int *pResult, int attemps, int min, int max);
//getStringAlphanumeric("\nEnter a brief description for the new advisement.:\n", "\nERROR! Invalid characters \n: ", buffer.description, 3, MAX_TEXT_ADD)==0){

int getStringAlphanumeric(char msg[], char msgError[], char *pResult, int attemps, int len);
#endif /* UTN_H_ */
