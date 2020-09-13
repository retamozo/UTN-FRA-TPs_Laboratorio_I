/*
 * unt.c
 *
 *  Created on: Sep 11, 2020
 *      Author: Enzo Retamozo
 */

#include <stdio.h>
#include <stdlib.h>

/* \brief getNumero: Solicita al usuario un número.
 * \param pResult: es la dirección de memoria (variable) donde guardará el número ingresado.
 * \param message: Texto informativo al momento de solicitar un valor al usuario.
 * \param errorMessage: Texto que se mostrará en caso de un rango de números inválido.
 * \param max: Valor máximo válido (no inclusive).
 * \param min: Valor mínimo válido (inclusive).
 * \param attemps: Es la cantidad de veces que será posible hacer esta operación para el usuario.
 * \return : 0 si la operación fue exitosa, -1 si se produjo un error.
 */

int getNumber(int* pResult, char* message, char* errorMessage, int attemps) {

	int _exit = -1;
	int bufferInt;
	int scanfResult;

	if (pResult != NULL &&
		message != NULL &&
		errorMessage != NULL &&
		attemps >= 0) {

		do {
			printf("%s", message);
			fflush(stdin);
			scanfResult = scanf("%d", &bufferInt);
			if (scanfResult == 1) {
				*pResult = bufferInt;
				_exit = 0;
				break;
			} else {
				attemps--;
				printf("%s Te quedan %d intentos \n", errorMessage, attemps);
				fflush(stdin);
			}
		} while (attemps > 0);
	}
	return _exit;
}

/* brief add: Toma dos números por parametro y calcula una suma de ellos.
 * param pResult: dirección de memoria (variable) donde se guardará el resultado de la sumatoria de ambos números.
 * param firstNumber: primer número ingresado.
 * param secondNumber: segundo número ingresad por el usuario.
 * return : 0 si la operación fue exitosa, -1 si se produjo un error.
 * */

int add(int* pResult, int firstNumber, int secondNumber) {
	int _exit = -1;
	if (pResult != NULL) {

		*pResult = (firstNumber + secondNumber);
		_exit = 0;
	}
	return _exit;
}

/* brief subtract: Toma dos números por parametro y calcula una resta de ellos.
 * param pResult: dirección de memoria (variable) donde se guardará el resultado de la resta de ambos números.
 * param firstNumber: primer número ingresado.
 * param secondNumber: segundo número ingresad por el usuario.
 * return : 0 si la operación fue exitosa, -1 si se produjo un error.
 * */

int subtract(int *pResult, int firstNumber, int secondNumber) {
	int _exit = -1;
	if (pResult != NULL) {
		*pResult = (firstNumber - secondNumber);
		_exit = 0;
	}
	return _exit;
}

/* brief multiply: Toma dos números por parametro y calcula una multiplicación de ellos.
 * param pResult: dirección de memoria (variable) donde se guardará el resultado de la multiplicación de ambos números.
 * param firstNumber: primer número ingresado.
 * param secondNumber: segundo número ingresad por el usuario.
 * return : 0 si la operación fue exitosa, -1 si se produjo un error.
 * */

int multiply(int *pResult, int firstNumber, int secondNumber) {
	int _exit = -1;
	if (pResult != NULL) {
		*pResult = (firstNumber * secondNumber);
		_exit = 0;
	}
	return _exit;
}

int factorial(int *pResult, int operator) {

	int resultOperation = 1;
	int repetitionsQuantity;
	int _exit = -1;

	if (pResult != NULL && operator > -1) {
		if (operator != 0) {
			for (repetitionsQuantity = operator; repetitionsQuantity > 1; repetitionsQuantity--) {
				resultOperation = resultOperation * repetitionsQuantity;
			}
			_exit = 0;
		} else {
			resultOperation = 1;
			_exit = 0;
		}
	}

	*pResult = resultOperation;
	return _exit;
}

/* \ brief division: dados un divisor y un dividendo, se realiza la operación de división de los mismos.
 * \ param pResult: es un puntero al espacio de memoria donde está el valor obtenido del usuario.
 * \ param divisor: es el número a dividir.
 * \ param dividend: es la base por la cual se dividirá al divisor.
 * \ retorna (0) si está ok / retorna (-1) si mal.
 */

int division(float* pResult, int divisor, int dividend) {
	int _exit = -1;
	if(pResult != NULL)	{
		if (dividend != 0) {
		*pResult = (float) divisor / dividend;
		_exit = 0;
		} else {
			printf("No se puede dividir por 0");
		}
	}
	return _exit;
}

