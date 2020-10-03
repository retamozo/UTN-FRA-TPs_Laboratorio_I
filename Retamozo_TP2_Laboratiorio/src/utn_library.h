/*
 * utn_library.h
 *
 *  Created on: Sept 24, 2020
 *      Author: Enzo Retamozo - Clase 9 | declaración de prototipos de funciones auxiliares
 */

#ifndef UTN_LIBRARY_H_
#define UTN_LIBRARY_H_

int isValidName(char* cadena,int limite);
int myGets(char *cadena, int longitud);
int getName(char* mensaje,char* mensajeError,char* pResultado, int reintentos, int limite);
int getNumber(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo);
int getNumberFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos);

#endif /* UTN_LIBRARY_H_ */
