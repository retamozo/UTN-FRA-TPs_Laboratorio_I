/*
 *  utn.c
 *  Created on: Sep 8, 2020
 *  Author: Enzo Retamozo
 */

#ifndef SRC_LIB_H_
#define SRC_LIB_H_

int getNumber(int *pResult, char *message, char *errorMessage, int attemps);
int add(int* pResult, int firstNumber, int secondNumber);
int subtract(int* pResult, int firstNumber, int secondNumber);
int multiply(int* pResult, int firstNumber, int secondNumber);
int division(int* pResult, int divisor, int dividend);
int factorial(int *pResult, int operator);
#endif /* SRC_LIB_H_ */
