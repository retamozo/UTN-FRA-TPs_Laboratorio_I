#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"
#include "Controller.h"

#define NAME_LEN 100


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int : 0 OK | -1 ERROR
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee){
		int retorno = -1;
		FILE* pFile;
		if(path!=NULL && pArrayListEmployee!=NULL){
			pFile = fopen(path, "r");
			if(pFile !=NULL && !parser_EmployeeFromText(pFile, pArrayListEmployee)){
				retorno = 0;
			} else {
				printf("\nEl archivo no existe");
			}
			fclose(pFile);
		}
	    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee){
	int retornar=-1;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL){
		pFile = fopen(path, "rb");
			if(pFile!=NULL && !parser_EmployeeFromBinary(pFile, pArrayListEmployee)){
				retornar=0;
			} else {
				printf("\nEl archivo no existe");
			}
		  fclose(pFile);
		}
	return retornar;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
		char bufferName[NAME_LEN];
		char bufferHours[BUFF_SIZE];
		char bufferSalary[BUFF_SIZE];
		char bufferID[BUFF_SIZE];

		Employee* buffer;
		if(pArrayListEmployee!=NULL  &&  !ll_isEmpty(pArrayListEmployee)) {
			if(getString("\nPor favor, ingrese el nombre del empleado: \n","\nERROR! No ingreso un nombre valido\n", bufferName, 3, NAME_LEN) ==0 &&
			   getString("\nPor favor, ingrese las horas trabajadas: ","\nERROR! formato de horas invalidas\n", bufferHours, 3,  9999999) ==0 &&
			   getString("\nPor favr, ingrese el salario: ","\nERROR! formato de salario invalido\n", bufferSalary , 3, 9999999) ==0 )	{
				sprintf(bufferID, "%d",controller_searchMaxId(pArrayListEmployee));
				printf("\nNuevo id generado: %s\n",bufferID);
				buffer = employee_newParametros(bufferID, bufferName, bufferHours, bufferSalary);
				ll_add(pArrayListEmployee,buffer);
			} else {
				printf("\nThe operation couldn´t be completed at -> controller_addEmployee ");
			}
		} else {
			printf("\nYou must first upload the employee list.\n ");
		}
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee) {

	int retorno =-1;
	int bufferId;
	int index;
	int option;
	char bufferName[NAME_LEN];
	char bufferHours[BUFF_SIZE];
	char bufferSalary[BUFF_SIZE];
	Employee* buffer;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee)) {
			if(getNumber("\nIngrese el id del empleado a modificar\n","\nError! por favor solo valores numericos",&bufferId,3,9,1) == 0 &&
			   controller_findById(pArrayListEmployee, bufferId, &index) ==0 && index > -1)	{
				buffer = ll_get(pArrayListEmployee, index);
				employee_print(buffer);
				if(getNumber("\nQue desea modificar?\n1)Nombre \n2)Horas \n3)Sueldo \n0)Regresar \n>:","\nError! por favor solo valores numericos", &option ,3, 9 ,1 )==0) {
					switch(option) {
					case 1:
						if(getString("\nIngrese el nuevo nombre: \n ","\nError! caracter inválido", bufferName, 3, NAME_LEN) ==0 &&
							employee_setNombreText(buffer, bufferName) ==0 )	{
							ll_set(pArrayListEmployee, index, buffer);
							retorno=0;
							printf("\nNombre modificado con éxito !\n");
						}
					break;
					case 2:
						if(getString("\nIngrese las horas a modificar","\nError! caracter inválido" , bufferHours, 3, 999999) == 0 &&
							employee_setHoursText(buffer, bufferHours) == 0 ) {
							ll_set(pArrayListEmployee, index, buffer);
							retorno=0;
							printf("\nUpdated data...\n");
						}
					break;

					case 3:
						if(getString("\nIngrese el salario a modificar","\nError! caracter inválido", bufferSalary, 3, 999999 ) ==0 &&
						   employee_setSalaryText(buffer,bufferSalary) ==0 ){
							ll_set(pArrayListEmployee, index, buffer);
							retorno = 0;
							printf("\nUpdated data...\n");
						}
					break;
					}
				}
			}
		}
		else
		{
			printf("\nNo data to edit...\n");
		}
		return retorno;
}

/** \brief Baja de empleado
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return (0) OK | (-1) FAIULURE
 */

int controller_removeEmployee(LinkedList* pArrayListEmployee) {
	int retornar=-1;
	int id;
	int index;
	int choosenOption;
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL) {
		if( !getNumber("\nIngrese el id del empleado que desea eliminar: \n", "\nError! por favor solo valores numericos\n", &id, 3, 9, 1) &&
			!controller_findById(pArrayListEmployee, id, &index) && index>-1) {
			printf("\nEmpleado encontrado!\n");
			bufferEmp = ll_get(pArrayListEmployee, index);
			employee_print(bufferEmp);
			if(!getNumber("\n\nDesea continuar? Presione 1 para eliminar o 2 para cancelar: ", "\nERROR! eliga una opcion valida", &choosenOption, 3, 9, 1) && choosenOption ==1 ){
				ll_remove(pArrayListEmployee, index);
				retornar=0;
				} else {
					printf("\nEmpleado NO eliminado\n");
				}
			} else {
				printf("\nNo se encontro un empleado con ese ID, vuelva a intentar");
			}
		}
	    return retornar;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return (0) OK | (-1) FAILURE
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee){
	int retornar = -1;
	int len = ll_len(pArrayListEmployee);
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee)) {
		for(int i=0; i<len;i++) {
			bufferEmp = ll_get(pArrayListEmployee, i);
			employee_print(bufferEmp);
			retornar=0;
		}
		printf("\n-------------------------------------------------------------");
	} else {
		printf("\nNo hay empleados para listar");
	}
    return retornar;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee) {
	int retorno = -1;
		int choosenOption;
		if(pArrayListEmployee != NULL && !ll_isEmpty(pArrayListEmployee)) {
			if(!getNumber("\n1) Ordenar de forma ascendente. \n2) Ordernar de forma descendiente\n", "\nError! por favor solo valores numericos\n", &choosenOption, 3, 9, 1)){
				ll_sort(pArrayListEmployee, employee_compareByName, choosenOption);
				retorno = 0;
			} else {
			printf("\nNo hay empleados para ordenar\n");
		}
	}
		return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee) {

	int retorno = -1;
	int len = ll_len(pArrayListEmployee);
	char buffName[NAME_LEN];
	char buffId[BUFF_SIZE];
	char buffHours[BUFF_SIZE];
	char buffSalary[BUFF_SIZE];
	FILE* pFile;
	Employee* bufferEmp;

	if(path!=NULL && pArrayListEmployee!=NULL) {
			pFile = fopen(path, "w");
			if(pFile != NULL) {
				ll_sort(pArrayListEmployee, employee_compareByName, 1);
				fprintf(pFile, "id,nombre,horasTrabajadas,sueldo\n");
				for(int i=0;i<len;i++)	{
					bufferEmp = ll_get(pArrayListEmployee, i);
					if( !employee_getNombre(bufferEmp, buffName) &&
						!employee_getHorasTrabajadasText(bufferEmp, buffHours) &&
						!employee_getIdText(bufferEmp, buffId) &&
						!employee_getSueldoText(bufferEmp, buffSalary)) {
						fprintf(pFile, "%s , %s, %s, %s\n",buffId, buffName, buffHours, buffSalary);
						retorno = 0;
					}
				}
				fclose(pFile);
			}
		}
	    return retorno;

}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee) {
	int retorno = -1;

	if(path !=NULL && pArrayListEmployee!=NULL) {

		int len = ll_len(pArrayListEmployee);
		Employee* bufferEmp;
		FILE* pFile;
		pFile = fopen(path, "wb");

		if(pFile!=NULL) {
			ll_sort(pArrayListEmployee, employee_compareByName, 1);
			for(int i=0 ; i<len ; i++) {
				bufferEmp = ll_get(pArrayListEmployee, i);
				fwrite(bufferEmp, sizeof(Employee),1, pFile);
				retorno = 0;
				}
				fclose(pFile);
			}
		}
		return retorno;
}


/** \brief Busca en la lista de empleados el maximo id y retorna ese valor + 1
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return el valor del maximo id encontrado + 1 o (-1) si algo salio mal
 */

int controller_searchMaxId(LinkedList* pArrayListEmployee){
	int retorno=-1;
	int len = ll_len(pArrayListEmployee);
	Employee* bufferEmp;
	int id;
	int maxId;
	if(pArrayListEmployee!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferEmp = ll_get(pArrayListEmployee, i);
			employee_getId(bufferEmp, &id);
			if(i==0 || id>maxId)
			{
				maxId = id;
				retorno = maxId+1;
			}
		}
	}
	return retorno;
}

/** \brief Dada una lista Linkedlist y un id, se busca un empleado.
 *
 * \param  LinkedList* pArrayListEmployee: Puntero a la LinkedList
 * \param int id: id del empleado a buscar.
 * \param int* index: Se devuelve el índice del empleado por referencia.
 * \return (0) OK | (-1) FAILURE
 */
int controller_findById(LinkedList* pArrayListEmployee, int id, int* index) {
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	int bufferId;
	Employee* bufferEmp;
	if(pArrayListEmployee != NULL && id > 0 && index != NULL) {
		for(int i=0;i<len;i++) {
			bufferEmp = ll_get(pArrayListEmployee, i);
			if(!employee_getId(bufferEmp, &bufferId) && bufferId == id)	{
				retornar = 0;
				*index = i;
				break;
			}
		}
	}
	return retornar;
}
