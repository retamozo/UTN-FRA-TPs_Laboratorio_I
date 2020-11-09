#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "utn.h"

int main()
{
	setbuf(stdout, NULL);
	int optionSelected;
    int option = 0;
    int fileLoaded = FALSE;

    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
    	if(getMenu(&optionSelected, 3,1,10) == 0){
    		switch(optionSelected){
    		case 1:
    			if(fileLoaded == FALSE && controller_loadFromText("data.csv",listaEmpleados) == 0){
    				printf("\n Los empleados se han cargado correctamente.\n");
    				fileLoaded=TRUE;
    			} else {
    				if(getNumber("\nYa existe una lista, desea sobreescribirla?"
    						"Presione 1 para aceptar o 2 para cancelar\n",
							"\nERROR!", &option, 3, 3, 1) == 0 &&
    						option==1 && controller_loadFromText("data.csv", listaEmpleados) == 0){
    							printf("\nLos empleados se han reescrito correctamente\n");
    					} else {
						printf("\nNo se reescribieron los empleados\n");
    				}
    			}
    		break;
    		case 2:
    			if(fileLoaded == FALSE && controller_loadFromBinary("data.bin", listaEmpleados) == 0) {
    				printf("\nLos empleados se han cargado correctamente.\n");
    				fileLoaded = TRUE;
    			} else {
    					if( getNumber("\nYa existe una lista, desea sobreescribirla??: Presione 1 para aceptar o 2 para cancelar", "\nERROR!", &option, 3, 3, 1) == 0 &&
    					option==1 && controller_loadFromBinary("data.bin", listaEmpleados) == 0){
    							printf("\nLos empleados se han reescrito correctamente\n");
    							} else {
    								printf("\nNo se reescribieron los empleados\n");
    							}
    					}
    		break;
			case 3:
				if(fileLoaded) {
					if(controller_addEmployee(listaEmpleados) == 0){
					printf("\nEmpleado dado de alta correctamente!\n");
					}
				} else {
					printf("\nPrimero debe hacer la carga de los empleados\n");
				}
			break;
			case 4:
				if(ll_isEmpty(listaEmpleados) == 0)	{
					if(controller_editEmployee(listaEmpleados) == 0) {
						printf("\nEmpleado modificado exitosamente!\n");
					}
				} else {
					printf("\nPrimero debe hacer la carga de los empleados\n");
				}
			break;
			case 5:
				if(ll_isEmpty(listaEmpleados) == 0) {
					if(controller_removeEmployee(listaEmpleados) == 0) {
						printf("\nEmpleado dado de baja correctamente\n");
					}
				} else {
					printf("\nPrimero debe hacer la carga de los empleados\n");
				}
			break;
			case 6:
				if(ll_isEmpty(listaEmpleados) == 0) {
					if(controller_ListEmployee(listaEmpleados) == 0) {
						printf("\nFin de la impresion\n");
					}
				} else {
					printf("\nPrimero debe hacer la carga de los empleados\n");
				}
			break;
			case 7:
				if(ll_isEmpty(listaEmpleados) == 0) {
					if(controller_sortEmployee(listaEmpleados) == 0) {
						printf("\nFin del ordenamiento");
					}
				}
				else {
					printf("\nPrimero debe hacer la carga de los empleados\n");
				}
			break;
			case 8:
				if(fileLoaded && controller_saveAsText("data.csv", listaEmpleados) == 0){
					printf("\nEmpleados guardados correctamente en el archivo\n");
				} else {
					printf("\nPrimero debe hacer la carga de los empleados\n");
				}
			break;
			case 9:
				if(fileLoaded && controller_saveAsBinary("data.bin", listaEmpleados) == 0) {
					printf("\nEmpleados guardados correctamente en el archivo (binario)\n");
				} else {
					printf("\nPrimero debe hacer la carga de los empleados\n");
				}
			break;
    		}
    	}

    }while(option != 10);
    ll_deleteLinkedList(listaEmpleados);
    return EXIT_SUCCESS;
}

