/*
 =================================================================
 Laboratorio de programaci�n - Trabajo pr�ctico n�1
 Calculadora.c
 Created on: Sep 7, 2020
 Author: Enzo Retamozo
 =================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utn.h"

#define ATTEMPS 3

int main(void) {
	setbuf(stdout, NULL);
	int resultOperation;
	int firstNumber;
	int secondNumber;
	int selectedOption;

	if(getNumber(&firstNumber, "Por favor, ingrese el primer numero \n", "S�lo valores num�ricos.", ATTEMPS) == 0) {

		if (getNumber(&secondNumber, "Por favor, ingrese el segundo n�mero\n", "S�lo valores num�ricos.", ATTEMPS) == 0) {

			if (getNumber(&selectedOption, "Que operaci�n desea realizar ?\n 1-Sumar \n 2-Restar \n 3-Dividir \n 4-Multiplicar \n 5-Factorial 6 \n 7-Salir \n", "Por favor, elija una opci�n v�lida.", ATTEMPS) == 0) {

				switch(selectedOption){
					case 1:
						if(add(&resultOperation,firstNumber, secondNumber) == 0) {
							printf("\nEl resultado de %d + %d es: %d.", firstNumber, secondNumber, resultOperation);
							}
						break;
					case 2:
						if(subtract(&resultOperation,firstNumber, secondNumber) == 0){
							printf("\nEl resultado de %d - %d es: %d.", firstNumber, secondNumber, resultOperation);
						}
						break;
					case 3:
						if(division(&resultOperation,firstNumber, secondNumber) == 0){
							printf("\nEl resultado de %d / %d es: %d.", firstNumber, secondNumber, resultOperation);
						}

						break;
					case 4:
						if(multiply(&resultOperation,firstNumber, secondNumber) == 0){
							printf("\nEl resultado de %d * %d es: %d.", firstNumber, secondNumber, resultOperation);
						}
						break;
					case 5:
						if(factorial(&resultOperation, firstNumber) == 0){
						printf("\nEl resultado del factoreal de %d es: %d.", firstNumber, resultOperation);
							}
						if(factorial(&resultOperation, secondNumber) == 0){
						printf("\nEl resultado del factoreal de %d es: %d.", secondNumber, resultOperation);
							}
						break;
					case 6:
						printf("Programa finalizado.");
						return EXIT_SUCCESS;
				}
			} else {
				printf("Elija una opci�n correcta.");
			}
		} else {
			printf("Agot� los intentos para ingresar el segundo n�mero");
		}
	} else {
		printf("\nHa agotado el n�mero de intentos para el primer n�mero. Reinicie la aplicaci�n.");
	}
	return EXIT_SUCCESS;
}
