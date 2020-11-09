/*
 * parser.h
 *
 *  Created on: Nov 1, 2020
 *      Author: Enzo
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);

#endif /* PARSER_H_ */
