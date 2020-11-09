#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

#define NAME_LEN 100
#define SALARY_LEN 999999
#define BUFF_SIZE 4096


typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* id,char* name,char* hours, char* salary);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_setIdText(Employee* this, char* id);

int employee_getId(Employee* this,int* id);
int employee_getIdText(Employee* this,char* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_setNombreText(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);


int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_setHoursText(Employee* this, char* hours);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);
int employee_getHorasTrabajadasText(Employee* this, char* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_setSalaryText(Employee* this, char* sueldo);
int employee_getSueldoText(Employee* this,char* sueldo);
int employee_compareByName(void* employee1, void* employee2) ;
int employee_print(Employee* this);


#endif // employee_H_INCLUDED
