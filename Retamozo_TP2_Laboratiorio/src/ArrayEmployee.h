/*
 * ArrayEmployee.h
 *
 *  Created on: Sep 29, 2020
 *      Author: Enzo
 */

#ifndef ARRAYEMPLOYEE_H_
#define ARRAYEMPLOYEE_H_

#define TRUE 1
#define FALSE 0
#define MAX_LEN_NAME 50
#define MAX_EMPLOYEES_QUANTITY 1000

typedef struct {
	int id;
	char name[MAX_LEN_NAME];
	char lastName[MAX_LEN_NAME];
	float salary;
	int sector;
	int isEmpty;
} Employee;

int emploDyee_mainMenu(int* pOpcion);
int employee_report(int* pOpcion);
int initEmployee(Employee* pArray, int len);
int employee_GetData(Employee* pArray,int len);
int employee_add(Employee* pArray,int len ,int indice,char* name,char* lastName,int sector,float salary,int id);
int findFreeIndex(Employee* pArray, int len, int* pResultado);
int modifyEmployeeData(Employee* pArray,int limite);
int employee_delete(Employee* pArray,int limite);
int employee_sortEmployee(Employee* pArray, int len,int order);
int employee_print(Employee* pArray, int len);
int employee_totalAverageSalaries(Employee* pArray,int len);
int employee_higherSalary(Employee* pArray,int len,float promedio, int* pResultado);
int employee_averageSalary(float salario,int cantidadId,float* pResultado);
int employee_countingById(Employee* pArray,int len,int* cantidadId);
int employee_salary(Employee* pArray,int len,float* pResultado);
int employee_searchIndexById (Employee* pArray, int limite,int idBuscar,int * pIndice);


#endif /* ARRAYEMPLOYEE_H_ */
