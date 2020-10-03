/*
 ============================================================================
 Name        : TP2 - Laboratorio de programación I
 Author      : Enzo Retamozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayEmployee.h"
#include "utn_library.h"
#define QTY_EMPLOYEE 1000

int main(void) {
	setbuf(stdout, NULL);

	Employee arrEmployee[QTY_EMPLOYEE];

	int optionSelected;
	int reportOption;
	int order;
	int flagEmployee = 0;

if (initEmployee(arrEmployee, QTY_EMPLOYEE) == 0) {
	do {
		getNumber(
				"\n 1-Alta \n 2- Imprimir \n 3-Baja  \n  4-Modificar 5-Imprimir indice 6- buscarLibre 7- SALIR \n ",
				"Error, intente de nuevo", &optionSelected, 3, 7, 1);
			switch (optionSelected) {
				case 1:

						if (employee_GetData(arrEmployee, QTY_EMPLOYEE) == 0) {
							printf("\nEmpleado cargado correctamente\n");
							flagEmployee = 1;
						}
						break;
				case 2:
				if (modifyEmployeeData(arrEmployee, QTY_EMPLOYEE) == 0
						&& flagEmployee == 1) {
					printf("\nEmpleado modificado correctamente\n");
				} else {
					printf("No se pudo realizar la modificacion\n");
				}
				break;
				case 3:
				if (employee_delete(arrEmployee, QTY_EMPLOYEE) == 0
						&& flagEmployee == 1) {
					printf("\nEmpleado borrado correctamente\n");
				}
				break;
				case 4:

					do {
						switch (employee_report(&reportOption)) {
							case 1:
							if (getNumber(
											"\nOpcion 1 :Ordenar de manera ascendente.\n"
											"Opcion 2 : Ordenar de manera descendente.\n"
											"OPCION 3 : VOLVER AL MENU DE INFORMES.\n\n"
											"Ingrese opcion elegida: ",
											"\nError,Opcion incorrecta.\n", &order, 3, 3, 1)
									== 0) {
								employee_sortEmployee(arrEmployee, QTY_EMPLOYEE,
										order);
							}
							break;

							case 2:
							employee_print(arrEmployee, QTY_EMPLOYEE);
							break;
							case 3:
							employee_totalAverageSalaries(arrEmployee,
									QTY_EMPLOYEE);
							break;
					  } while (optionSelected != 4);


		    	} while(optionSelected!=5);

		   }
	   } while(optionSelected != 7 );

	return EXIT_SUCCESS;

    }
}
