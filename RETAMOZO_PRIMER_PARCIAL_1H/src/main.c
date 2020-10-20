/*
 ============================================================================
 Name        : RETAMOZO_PRIMER_PARCIAL_1H.c
 Author      : ENZO RETAMOZO
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reports.h"


int main(void) {
	setbuf(stdout, NULL);
	Client clientArr[MAX_CLIENTS];
	Advertisement addArr[MAX_ADVERTISEMENT];
	int optionSelected;
	int clientId;
	// NOTE: you should discomment these next 2 lines of code.
//	addClient_FORCED(clientArr, MAX_CLIENTS);

	if(initClient(clientArr,MAX_CLIENTS) == 0 && initAdvertisement(addArr, MAX_ADVERTISEMENT) == 0) {
		do {
			if (getMenu(&optionSelected, 3, 1, 9) == 0) {
				switch(optionSelected){
					case 1:
						if (addClient(clientArr, MAX_CLIENTS) == 0) {
							printf("\nClient added succesfully \n");
						} else {
							printf("\nSorry, something went wrong.\n");
						}

					break;
					case 2:
						if(modifyClient(clientArr, MAX_CLIENTS) == 0){
							printf("\nSUCCESS MODIFY CLIENT\n");
						} else {
							printf("\nSomething went wrong. Try again. \n");
						}
					break;
					case 3:
					if (getNumber("\nPlease, add the ID of the client to delete\n","\nError, invalid ID. Try again.\n", &clientId, 3,9, 1) == 0	&&
						printClientAddsById(clientArr, MAX_CLIENTS, addArr, MAX_ADVERTISEMENT, clientId) == 0 &&
						deleteAdvertisement(addArr, MAX_ADVERTISEMENT,clientId) == 0 &&
						deleteClient(clientArr, MAX_CLIENTS, clientId) == 0 ) {
						printf(
								"\nClient has been succesfully deleted with their active adds.!\n");
					} else {
						printf("\nThere are no active clients.\n");
					}
					break;
					case 4:
						if(addNewAdvertisement(addArr, MAX_ADVERTISEMENT, clientArr, MAX_CLIENTS) == 0){
							printf("\nAdvertisement created.\n");
						} else {
						  printf("\n You cannot create advertisements if you don't have any active client. \n");
						}
					break;
					case 5:
						if(findActivesAdvertisements(addArr, MAX_ADVERTISEMENT)==0) {
							if(pauseAdvertisements(addArr, MAX_ADVERTISEMENT, clientArr, MAX_CLIENTS) ==0) {
							   printf("\nAdvertisements paused succesfully\n");
			      			} else {
								printf("\nThere are no actives adds.\n");
			      			}
	     				}
						break;
					case 6:
						if(findActivesAdvertisements(addArr, MAX_ADVERTISEMENT)==0) {
							if(reanudeAdvertisements(addArr, MAX_ADVERTISEMENT, clientArr, MAX_CLIENTS) ==0) {
							   printf("\nAdvertisements reanuded succesfully\n");
			      			} else {
								printf("\nThere are no actives adds.\n");
			      			}
	     				}
						break;

					case 7:
						if(printClientDetails(clientArr, MAX_CLIENTS) != 0){
							printf("\n There are not actives clients. Please try load at least 1 client \n.");
						}
					break;

					case 8:
						if(isClientPositionUsed(clientArr, MAX_CLIENTS) == 0 && findActivesAdvertisements(addArr, MAX_ADVERTISEMENT) ==0){
							startReportMenu(clientArr,MAX_CLIENTS , addArr,MAX_ADVERTISEMENT);
							} else {
								printf("You need active clients and active advertisements to got into reports section.");
							}
					break;
				 }
			}
		} while (optionSelected != 9);
	}


    printf("\n Thanks! Goodbye.");
	return EXIT_SUCCESS;

}

//static int Informe_calcularAvisos(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso,int estado)
//{
//	int retorno=-1;
//	int avisosPorCliente=0;
//
//	for(int i=0; i<lenAvisos; i++)
//	{
//
//		/*
//		if(		listAviso[i].isEmpty == FALSE   &&
//				listAviso[i].estado == 1 	&&
//				listAviso[i].idCliente == id	)
//		{
//			avisosPorCliente++;
//		}
//		 */
//		if(listAviso[i].isEmpty == FALSE   && listAviso[i].idCliente == id)
//		{
//			switch(estado)
//			{
//				case 1:
//					if(listAviso[i].estado == 0)
//					{
//						avisosPorCliente++;
//					}
//				break;
//
//				case 2:
//					if(listAviso[i].estado == 1)
//					{
//						avisosPorCliente++;
//					}
//				break;
//
//				default:avisosPorCliente++;
//				break;
//			}
//		}
//	}
//	*pCountAviso = avisosPorCliente;
//	retorno=0;
//	return retorno;
//}
//
///** \brief
// * \param
// * \param
// * \return int Return (-1) if Error [Invalid len or NULL pointer or if can't find a employee] - (0) if Ok
// */
//int Informe_cantidadDeAvisosMAX(Aviso *listAviso, int lenAvisos,Cliente *listCliente,int lenCliente,int estado)
//{
//	int retorno = -1;
//	int actualCounter;
//	int maxContador;
//	Cliente bufferMaxCliente;
//
//	if(listAviso !=NULL && listCliente !=NULL && lenAvisos>0 && lenCliente>0)
//	{
//		printf("\nNOMBRE          APELLIDO        CUIT             CANTIDAD DE AVISOS\n");
//		for(int i=0;i<lenCliente;i++)
//		{
//			Informe_calcularAvisos(listAviso,lenAvisos,listCliente[i].id,&actualCounter,estado);
//			if(i==0 || actualCounter>maxContador)
//			{
//				maxContador = actualCounter;
//				bufferMaxCliente = listCliente[i];
//			}
//		}
//		printf("\n>CANTIDAD DE AVISOS MAX  %d",maxContador);
//		printf("\n%-15s %-15s %4s %15d \n",bufferMaxCliente.nombre,bufferMaxCliente.apellido,bufferMaxCliente.cuit,maxContador);
//		retorno=0;
//	}
//	return retorno;
//}
