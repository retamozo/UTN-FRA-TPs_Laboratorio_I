/*
 * employee.c
 *
 *
 *      Author: Enzo Retamozo / 2020 Octubre
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ArrayEmployee.h"
#include "utn_library.h"
#define NAME_LEN 50
#define QTY_EMPLOYEE 1000

static int createNewId(void);

/*
 *brief initialize every value of the array as empty.
 *param Employee* pArray array to be analize.
 *param int limit Lenght of the array
 *return 0: everything is OK. return -1: Failed.
 */

int initEmployee(Employee *pArray, int limit) {
	int retorno = -1;
	if (pArray != NULL && limit > 0) {
		for (int i = 0; i < limit; i++) {
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}



/*
 *brief static generates a new id.
 *param void,no params.
 *return id: return a new id.
 */

static int createNewId(void) {
	static int id = 0;
	id++;
	return id;
}

/*
 *brief Loop throught a Employee array, looking for a 'isEmpty' field flaged as TRUE
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the list.
 *param int * pResult pointer to place the found index.
 *return 0: everything is OK. return -1: Failed.
 */
int findFreeIndex(Employee *pArray, int limit, int *pResult) {
	int retorno = -1;
	int i;
	if (pArray != NULL && limit > 0 && pResult != NULL) {
		for (i = 0; i < limit; i++) {
			if (pArray[i].isEmpty == TRUE) {
				*pResult = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*
 *brief Given a Employee array, start a register for a new one employee.
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the list.
 *return 0: everything is OK. return -1: Failed.
 */
int employee_GetData(Employee *pArray, int limit) {

	int retorno = -1;
	char name[NAME_LEN];
	char lastName[NAME_LEN];
	int sector;
	float salary;
	int index;
	int id;

	if (pArray != NULL && limit > 0) {

		if (findFreeIndex(pArray, QTY_EMPLOYEE, &index) == 0
				&& getName("\nIngrese el nombre: ",
						"\nError, no es un nombre valido.", name, 3,
						NAME_LEN) == 0
				&& getName("Ingrese el apellido: ",
						"Error, no es un apellido valido", lastName, 3,
						NAME_LEN) == 0
				&& getNumberFloat(&salary, "ingrese el salario: ",
						"Error no es un salario valido\n", 0.00, 9999999.99, 3)
						== 0
				&& getNumber(
						"\nIngrese el sector al que pertenece:\nOpcion 1: Contaduria\nOpcion 2:IT\nOpcion 3:Recursos Humanos\nOpcion 4:Mantenimiento\nNumero a ingresar: \n",
						"\nError, sector invalido.\n", &sector, 3, 4, 1) == 0) {
			id = createNewId();
			employee_add(pArray, limit, index, name, lastName, sector, salary,
					id);
			printf("El ID de este empleado es: %d", pArray[index].id);
			retorno = 0;
		}
	}
	return retorno;
}

/*
 *brief  Registers the employee to the employee list.
 *param Employee* pArray pointer of type Employee to the list of employee.
 *param int limit: lenght of the list
 *param int index: position in the array.
 *param char*name pointer to a name to be added.
 *param char * lastName: pointer to the lastName to be added.
 *param int sector: sector in which the employee works
 *param float salary: salary of the employee
 *param int id: id of the employee.
 *return 0: everything is OK. return -1: Failed.
 */
int employee_add(Employee *pArray, int limit, int index, char *name,
		char *lastName, int sector, float salary, int id) {
	int retorno = -1;

	if (pArray != NULL && limit > 0 && index >= 0 && index < limit
			&& pArray[index].isEmpty == TRUE && name != NULL && lastName != NULL
			&& sector > 0 && salary < 9999999.99 && id > 0) {
		strncpy(pArray[index].name, name, NAME_LEN);
		strncpy(pArray[index].lastName, lastName, NAME_LEN);
		pArray[index].sector = sector;
		pArray[index].salary = salary;
		pArray[index].id = id;
		pArray[index].isEmpty = FALSE;
		retorno = 0;
	}
	return retorno;
}

/*
 *brief Given a Employee array,, this fn let a client handle a new employee data.
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the list.
 *return 0: everything is OK. return -1: Failed.
 */
int modifyEmployeeData(Employee *pArray, int limit) {
	int retorno = -1;
	int searchedId;
	int indexToModify;
	int option;
	int flagId = 1;
	Employee bufferEmployee;

	if (employee_print(pArray, limit) == 0) {
		if (getNumber("\nIngrese el ID para la modificacion de datos",
				"Error: numero invalido", &searchedId, 3, 1000, 1) == 0
				&& pArray != NULL && limit > 0 && searchedId > 0) {
			if (employee_searchIndexById(pArray, limit, searchedId,
					&indexToModify) == 0) {
				if (pArray[indexToModify].isEmpty == FALSE) {
					flagId = 0;
					getNumber(
							"Opciones a modificar\nOpcion 1: Nombre\nOpcion 2: Apellido\nOpcion 3: Salario\nOpcion 4: Sector\n"
									"Ingrese campo a modificar: ",
							"ERORR, No es un campo valido\n", &option, 3, 4, 1);

					switch (option) {
					case 1:
						if (getName("Ingrese el nuevo nombre: ",
								"\nError: nombre invalido.",
								bufferEmployee.name, 3, NAME_LEN) == 0) {
							strncpy(pArray[indexToModify].name,
									bufferEmployee.name, NAME_LEN);
						}
						break;
					case 2:
						if (getName("Ingrese apellido: ",
								"\nError: apellido invalido.",
								bufferEmployee.lastName, 3, NAME_LEN) == 0) {
							strncpy(pArray[indexToModify].lastName,
									bufferEmployee.lastName, NAME_LEN);
						}

						break;
					case 3:
						if (getNumberFloat(&bufferEmployee.salary,
								"Ingrese salario: ", "Error: salario invalido",
								0, 200000, 3) == 0) {
							pArray[indexToModify].salary =
									bufferEmployee.salary;
						}
						break;
					case 4:
						if (getNumber(
								"Ingrese el nuevo sector al que pertenece:\nOpcion1:Contaduria\nOpcion2:IT\nOpcion3:Recursos Humanos\nOpcion4:Mantenimiento\nNumero a ingresar: ",
								"Error: sector invalido.",
								&bufferEmployee.sector, 3, 4, 1) == 0) {
							pArray[indexToModify].sector =
									bufferEmployee.sector;
						}
						break;
					}
					retorno = 0;
				}
			}
		}

	}
	if (flagId == 1) {
		printf("No se encontró el id");
	}
	return retorno;
}

/*
 *brief Search and index by ID.
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the list.
 *param int seachedId: id to be searched.
 *param int * pIndex: integer pointer for the found index.
 *return 0: everything is OK. return -1: Failed.
 */
int employee_searchIndexById(Employee *pArray, int limit, int searchedId,
		int *pIndex) {
	int retorno = -1;
	int i;
	if (pArray != NULL && limit > 0 && pIndex != NULL && searchedId >= 0) {
		for (i = 0; i < limit; i++) {
			if (pArray[i].isEmpty == FALSE && pArray[i].id == searchedId) {
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	} else {
		printf("Hubo un error!");
	}
	return retorno;
}

/*
 *brief Deletes the employee by letting the index in ".isEmpty=TRUE".
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the list.
 *return 0: everything is OK. return -1: Failed.
 */
int employee_delete(Employee *pArray, int limit) {
	int retorno = -1;
	int i;
	int searchedId;

	if (getNumber("Ingrese el ID del empleado que desea eliminar.",
			"Error: ID invalido", &searchedId, 3, 1000, 1) == 0
			&& pArray != NULL && limit > 0 && searchedId > 0) {
		for (i = 0; i < limit; i++) {
			if (pArray[i].isEmpty == FALSE && pArray[i].id == searchedId) {
				pArray[i].isEmpty = TRUE;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*
 *brief Accumulates the salaries of the employees by going through the array looking for the variable "isEmpty=FALSE"
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the list.
 *param float* pResult. Pointer for the acumulated salaries
 *return 0: everything is OK. return -1: Failed.
 */
int employee_salary(Employee *pArray, int limit, float *pResult) {
	int retorno = -1;
	int i;
	float acumulator = 0;

	if (pArray != NULL && limit > 0 && pResult != NULL) {
		for (i = 0; i < limit; i++) {
			if (pArray[i].isEmpty == FALSE) {
				acumulator = acumulator + pArray[i].salary;
				retorno = 0;
			}
		}
	}
	*pResult = acumulator;
	return retorno;
}

/*
 *brief Counts the quantity of ID to get the quantity of employees.
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the list.
 *param float* pResult. Pointer for the acumulated ids.
 *return 0: everything is OK. return -1: Failed.
 */
int employee_countingById(Employee *pArray, int limit, int *pResult) {
	int retorno = -1;
	int counterId = 0;
	int i;

	if (pArray != NULL && limit > 0 && pResult != NULL) {
		for (i = 0; i < limit; i++) {
			if (pArray[i].isEmpty == FALSE && pArray[i].id > 0) {
				counterId++;
				retorno = 0;
			}
		}
	}
	*pResult = counterId;
	return retorno;
}

/*
 *brief gets an average of the salaries of the employees.
 *param Employee* pArray. Employee pointer type for the array.
 *param int countedIds: quantity of ids/employees.
 *param float* pResult. Pointer for the result of the division of the total salary by the quantity of employees.
 *return 0: everything is OK. return -1: Failed.
 */
int employee_averageSalary(float salary, int countedIds, float *pResult) {
	int retorno = -1;
	float average;
	if (salary > 0 && countedIds > 0 && pResult != NULL) {
		average = salary / countedIds;
		*pResult = average;

		retorno = 0;

	}
	return retorno;
}

/*
 *brief Gets the employee/s with the highest salary/ies.
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the array.
 *param float average: average value of salaries.
 *param int * pResult: pointer for the
 *return 0: everything is OK. return -1: Failed.
 */
int employee_higherSalary(Employee *pArray, int limit, float average,
		int *pResult) {
	int retorno = -1;
	int i;
	int highSalariesCounter = 0;

	if (pArray != NULL && limit > 0 && average > 0 && pResult != NULL) {
		for (i = 0; i < limit; i++) {
			if (pArray[i].isEmpty == FALSE && pArray[i].salary > average) {
				highSalariesCounter++;
				retorno = 0;
			}
		}
	}
	*pResult = highSalariesCounter;

	return retorno;
}

/*
 *brief Joins the averages calculated in order to show print them when the user selects the involved option.
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: lenght of the array;
 *return 0: everything is OK. return -1: Failed.
 */
int employee_totalAverageSalaries(Employee *pArray, int limit) {
	int retorno = -1;
	float totalSalary;
	int totalEmployee;
	float totalAverage;
	int highestAverageSalary;

	if (employee_salary(pArray, limit, &totalSalary) == 0
			&& employee_countingById(pArray, limit, &totalEmployee) == 0) {
		employee_averageSalary(totalSalary, totalEmployee, &totalAverage);
	}
	printf("\nSalario total de empleados: $%.2f\n"
			"Salario promedio de empleados: $%.2f", totalSalary, totalAverage);
	if (employee_higherSalary(pArray, limit, totalAverage,
			&highestAverageSalary) == 0) {
		printf("\nCantidad de empleados que superan el promedio: %d",
				highestAverageSalary);
	} else {
		printf("\nNingun empleado supera el promedio");
	}

	return retorno;
}

/*
 *brief prints the list of employees.
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: lenght of the array;
 *return 0: everything is OK. return -1: Failed.
 */
int employee_print(Employee *pArray, int limit) {
	int retorno = -1;
	if (pArray != NULL && limit > 0) {
		for (int i = 0; i < limit; i++) {
			if (pArray[i].isEmpty == FALSE) {
				printf("\n\nEmpleada/o:\n\n"
						"Apellido   "
						"Nombre     "
						"Id   "
						"Sector    "
						"Sueldo\n");

				if (pArray[i].isEmpty == 0) {
					printf("%-11s"
							"%-11s"
							"%-5d"
							"%-9d "
							"%-6f\n", pArray[i].lastName, pArray[i].name,
							pArray[i].id, pArray[i].sector, pArray[i].salary);
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}

/*
 *brief Options for the user to get a report.
 *param int* pOption. pointer to the option chosen by the user.
 *return 0: everything is OK. return -1: Failed.
 */

int employee_report(int *pOption) {
	int retorno;
	printf("\n\n");
	printf("Ingrese una opcion:\n");
	printf("-Opcion 1: Ordenar.\n");
	printf("-Opcion 2: Imprimir.\n");
	printf(
			"-Opcion 3: Promedio salarial y cantidad de empleados que superan el mismo.\n");
	printf("-Opcion 4: Volver al menu.\n");
	getNumber("\nIngresa la opcion: ", "Hubo un error!", &retorno, 3, 4, 1);
	*pOption = retorno;
	return retorno;
}

/*
 *brief Sorts the employee list with an order choosen by the user (ascendant, descendant).
 *param Employee* pArray. Employee pointer type for the array.
 *param int limit: Lenght of the list.
 *param int order: option choosen that will determine the way the list is going to be ordered.
 *return 0: everything is OK. return -1: Failed.
 */

int employee_sortEmployee(Employee *pArray, int limit, int order) {
	Employee bufferEmployee;
	int retorno = -1;
	int i;
	int flagOrder = 1;

	if (pArray != NULL && limit > 0 && (order > 0 || order < 5)) {
		while (flagOrder == 1) {
			flagOrder = 0;
			for (i = 0; i < limit - 1; i++) {
				if (order == 1 && pArray[i].sector < pArray[i + 1].sector) {
					bufferEmployee = pArray[i];
					pArray[i] = pArray[i + 1];
					pArray[i + 1] = bufferEmployee;
					flagOrder = 1;
				} else if (pArray[i].sector == pArray[i + 1].sector
						&& strncmp(pArray[i].lastName, pArray[i + 1].lastName,
								NAME_LEN) > 0) {
					bufferEmployee = pArray[i];
					pArray[i] = pArray[i + 1];
					pArray[i + 1] = bufferEmployee;
					flagOrder = 1;
				}
				if (order == 2 && pArray[i].sector > pArray[i + 1].sector) {
					bufferEmployee = pArray[i];
					pArray[i] = pArray[i + 1];
					pArray[i + 1] = bufferEmployee;
					flagOrder = 1;
				} else if (pArray[i].sector == pArray[i + 1].sector
						&& strncmp(pArray[i].lastName, pArray[i + 1].lastName,
								NAME_LEN) > 0) {
					bufferEmployee = pArray[i];
					pArray[i] = pArray[i + 1];
					pArray[i + 1] = bufferEmployee;
					flagOrder = 1;
				}

			}
			if (order == 3) {
				break;
			}

		}
	}
	return retorno;
}
