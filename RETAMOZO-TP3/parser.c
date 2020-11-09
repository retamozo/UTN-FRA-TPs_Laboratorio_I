#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#define BUZZ_LEN 1000

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee){

	int retorno = -1;
	Employee* buffEmp;
	char buffId[BUZZ_LEN];
	char buffName[BUZZ_LEN];
	char buffHours[BUZZ_LEN];
	char buffSalary[BUZZ_LEN];
	if(pFile!=NULL && pArrayListEmployee!=NULL){
		do {
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",buffId,buffName,buffHours,buffSalary)==4){
				buffEmp = employee_newParametros(buffId, buffName, buffHours, buffSalary);
				ll_add(pArrayListEmployee, buffEmp);
				retorno = 0;
			}
		} while(feof(pFile)==0);
		fclose(pFile);
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee){
	int retorno = -1;
	Employee* bufferEmployee;
	int read;
	if(pFile != NULL && pArrayListEmployee != NULL) {
		do{
			bufferEmployee = employee_new();
			if(bufferEmployee != NULL) {
				read = fread(bufferEmployee,sizeof(Employee),1,pFile);
				if(read == 1){
					ll_add(pArrayListEmployee, bufferEmployee);
				} else {
					employee_delete(bufferEmployee);
					break;
				}
			}
		} while(!feof(pFile));
		retorno = 0;
	}
	return retorno;
}
