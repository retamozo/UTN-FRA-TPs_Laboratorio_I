#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "LinkedList.h"
#include "utn.h"


static int employee_isValidInt(char* numericChar);
static int employee_isString(char cadena[]);

/** \brief Dado parametros de tipo string, esta función da de alta un nuevo empleado.
 * \param char* idStr: id empleado
 * \param char* nombreStr: nombre del empleado
 * \param char* horasTrabajadasStr: horas trabajadas
 * \param char* sueldo: sueldo del empleado
 * \return DIRECCIÓN DE MEMORIA del tipo Employee si la función fue exitosa, caso contrario NULL;
 */

Employee* employee_newParametros(char* id,char* name,char* hours, char* salary) {
	Employee* pEmployee = NULL;

	if (id != NULL && name != NULL && hours != NULL && salary != NULL){
		pEmployee = employee_new();
		if (pEmployee != NULL &&
			employee_setIdText(pEmployee,id) == 0 &&
			employee_setNombreText(pEmployee,name) == 0 &&
			employee_setHoursText(pEmployee,hours) == 0 &&
			employee_setSalaryText(pEmployee,salary) == 0 ){
			return pEmployee;
		}
		else {
			pEmployee = NULL;
		}
	}
	return pEmployee;
}

/** \brief Mediante la función Malloc, se solicita memoria al programa para generar un nuevo empleado.
 * 	\return nueva dirección de memoria
 */
Employee* employee_new() {
	return (Employee*)malloc(sizeof(Employee));
}

/** \brief Asigno el id de un empleado en su campo correspondiente.
 * \param Employee* this: Puntero del empleado
 * \param char* id: Recibo el id, en forma de texto, a ser asignado a ese empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_setId(Employee* this, int id) {
	int retornar = -1;
	if(this!=NULL && id >= 0){
		this->id = id;
		retornar = 0;
	}
	return retornar;
}


/*
 * \brief employee_setIdFromTxtFile: Carga el id obtenido como texto en el campo del empleado
 * \param this Employee*: puntero a empleado
 * \param id char*: puntero al id que va a cargar
 * \return (-1) Error / (0) Ok
 */

int employee_setIdText(Employee* this, char* id) {
    int output = -1;
    if (this != NULL && id != NULL && employee_isValidInt(id) == 0) {
        this->id = atoi(id);
        output = 0;
    }
    return output;
}



/** \brief Asigna el nombre de un empleado recibiendo el mismo cómo char.
 * \param Employee* this: Puntero del empleado
 * \return int 0
 */
int employee_setNombreText(Employee* this,char* nombre) {
	int retorno = -1;
	if(this != NULL && employee_isString(nombre)==1 && nombre!=NULL){
		strncpy(this->nombre,nombre, NAME_LEN);
		retorno = 0;
	}
	return retorno;
}

/*
 * \brief employee_isValidInt: Valida que una cadena de caracteres, contenga números
 * \param string char*: puntero de la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (0) FALSE (1) TRUE (-1) ERROR
 */

static int employee_isValidInt(char string[]) {
	int retornar = 1;
	int i = 0;
	if(string!=NULL && strlen(string)>0){
		if(string[0]=='-'){
			i=1;
		}
		for(;i<strlen(string);i++){
			if(string[i]>'9' || string[i]<'0'){
				retornar=0;
				break;
			}
		}
	}
	return retornar;
}


/*
 *brief verifica que una cadena este en el rango de caracteres para ser un nombre valido.
 *param char cadena Cadena a ser analizada
 *param int limite longitud de la cadena.
 *return 0: failed . return 1: nombre valido.
 */

static int employee_isString(char cadena[]) {
	int respuesta = 1;
	for (int i = 0; i && cadena[i] != '\0'; i++) {
		if ((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			 cadena[i] != '.') {
			 	 respuesta = 0;
				 break;
		}
	}
	return respuesta;
}

/** \brief Asigno las horas trabajadas de un empleado en forma de texto
 * \param Employee* this: Puntero del empleado
 * \param char* horasTrabajadas: Recibo las horas trabajadas, en forma de texto, a asignar al empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */

int employee_setHoursText(Employee* this, char* horasTrabajadas){
    int output = -1;
    if (this != NULL && horasTrabajadas != NULL &&
    	employee_isValidInt(horasTrabajadas)==0){
        this->horasTrabajadas = atoi(horasTrabajadas);
        output = 0;
    }
    return output;
}

/** \brief Set an employee's salary
 * \param sueldo char* : Amounts of salary
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_setSalaryText(Employee* this, char* sueldo) {
	int retorno = -1;
	char buffer[BUFF_SIZE];
	if( this!=NULL && sueldo!=NULL && employee_isValidInt(sueldo)==1) {
			strncpy(buffer, sueldo, BUFF_SIZE);
			this -> sueldo = atoi(buffer);
			retorno = 0;
	}
	return retorno;
}

/** \brief Método para remover un puntero de empleado.
 * \param this Employee* : Lugar de memoria donde se encuentra el empleado a eliminar
 */
void employee_delete(Employee* this){
	if(this!=NULL){
		free(this);
	}
}

/* Brief: retorna el id de un empleado, pero en formato string.
 * \param Employee* this: Puntero del empleado
* \param int* id: Pasaje por referencia del id del empleado
* \return (0) OK | (-1) FAILURE
*/

int employee_getIdText(Employee* this,char* id) {
	int retorno = -1;

	if(this!=NULL && id!=NULL){
		sprintf(id,"%d",this->id);
		retorno = 0;
	}
	return retorno;
}


/** \brief Se obtiene el id de un empleado, dada una lista del tipo Employee
 * \param Employee* this: Puntero del empleado
 * \param int* id: Pasaje por referencia del id del empleado
 * \return (0) OK | (-1) FAILURE
 */

int employee_getId(Employee* this, int* id) {
	int retorno = -1;
	if(this!=NULL && id!=NULL){
		*id = this->id;
		retorno=0;
	}
	return retorno;
}

/** \brief Obtengo el nombre de un empleado
 * \param Employee* this: Puntero del empleado
 * \param char* name: Recibo el puntero a donde se va a guardar el nombre de ese empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_getNombre(Employee* this, char* nombre) {
	int retornar=-1;
	if(this!=NULL && nombre!=NULL) {
		strncpy(nombre, this->nombre, NAME_LEN);
		retornar=0;
	}
	return retornar;
}

/** \brief Función que imprime los datos de un empleado, utilizando los setters correspondientes a Employee
 *  \param Employee* this: Puntero del empleado
 *  \return (0) Si todo esta OK o (-1) Si algo salio mal
 */

int employee_print(Employee* this)
{
	int output=-1;
	char nombreAux[NAME_LEN];
	char idAux[BUFF_SIZE];
	char horasAux[BUFF_SIZE];
	char salarioAux[BUFF_SIZE];
	if(this!=NULL) {

		if( employee_getNombre(this, nombreAux) == 0 &&
			employee_getIdText(this, idAux) == 0	&&
			employee_getHorasTrabajadasText(this, horasAux) ==0 &&
			employee_getSueldoText(this, salarioAux) ==0 ) {
			printf("\n-------------------------------------------------------------");
			printf("\nID        Nombre              Horas trabajadas    Salario    ");
			printf("\n-------------------------------------------------------------");
			printf("%-6s %-10s  %5s %12s\n", idAux, nombreAux, horasAux, salarioAux);
			output = 0;
		}
	}
	return output;
}

/** \brief Funcion que obtiene las horas trabajadas de un empleado.
 * \param Employee* this: Puntero del empleado
 * \param int* horasTrabajadas: Pasaje por referencia de las horas trabajadas de ese empleado
 * \return (0) OK (-1) FAILURE
 */
int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas) {
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)	{
		*horasTrabajadas = this->horasTrabajadas;
		retorno=0;
	}
	return retorno;
}

/** \brief Funcion que obtiene las horas trabajadas de un empleado.
 * \param Employee* this: Puntero del empleado
 * \param char* horasTrabajadas: Pasaje por referencia de las horas trabajadas de ese empleado
 * \return (0) OK (-1) FAILURE
 */
int employee_getHorasTrabajadasText(Employee* this, char* horasTrabajadas) {
	int output=-1;
	if(this!=NULL && horasTrabajadas!=NULL)	{
		sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
		output=0;
	}
	return output;
}


/** \brief Obtengo el sueldo de un empleado
 * \param Employee* this: Puntero del empleado
 * \param float* sueldo: Pasaje por referencia del sueldo de un empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_getSueldo(Employee* this, float* sueldo) {
	int retorno = -1;
	if(this!=NULL && sueldo!=NULL) {
		*sueldo = this->sueldo;
		retorno=0;
	}
	return retorno;
}

/** \brief Obtengo el sueldo de un empleado
 * \param Employee* this: Puntero del empleado
 * \param float* sueldo: Pasaje por referencia del sueldo de un empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_getSueldoText(Employee* this,char* sueldo) {
	int output=-1;
	if(this!=NULL && sueldo!=NULL){
		sprintf(sueldo,"%d",this->sueldo);
		output=0;
	}
	return output;
}


/** \brief Método criterio. Utilizado para la función SORT del controller.
 *  \param void* employee1: Puntero void que castearemos al primer empleado
 *  \param void* employee2: Puntero void que castearemos al segundo empleado
 *  \return (1) Si el primer empleado tiene un nombre "mayor" al segundo, (-1) Si el segundo empleado tiene un nombre "mayor" al primero o (0) si son iguales
 */
int employee_compareByName(void* employee1, void* employee2) {
	int retorno;
	Employee* buffPrimero = (Employee*) employee1;
	Employee* buffSegundo = (Employee*) employee2;
	char bufferName1[BUFF_SIZE];
	char bufferName2[BUFF_SIZE];
	if(employee1!=NULL && employee2!=NULL) {
		employee_getNombre(buffPrimero, bufferName1);
		employee_getNombre(buffSegundo, bufferName2);
		if(strncmp(bufferName1,bufferName2,NAME_LEN)>0){
			retorno=1;
		} else {
			if(strncmp(bufferName1,bufferName2,NAME_LEN)<0) {
				retorno=-1;
			} else {
				retorno=0;
			}
		}
	}
	return retorno;
}



