/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "dns.h"
#include <string>
#include <list>
#include <iostream>

struct fila{
	int pc;
	char *ip;
};

std::list<fila> registro;



int *
registrar_1_svc(char *arg1, char *arg2,  struct svc_req *rqstp)
{
	static int  result = 1;

	fila lafila;
	lafila.pc = atoi(arg1);	
	lafila.ip =  strdup(arg2);
	registro.push_back(lafila);
	
	return &result;
}

int *
eliminar_1_svc(char *arg1,  struct svc_req *rqstp)
{
	static int  result = 0;
	result = 0;

	for(auto it = registro.begin(); it != registro.end(); it++){
		if(it->pc == atoi(arg1)){
			free(it->ip);
			registro.erase(it);
			result = 1;
			return &result;
		}
	}

	return &result;
}

char **
buscar_1_svc(char *arg1,  struct svc_req *rqstp)
{
	static char * result = NULL;
	result = NULL;

	for(auto it = registro.begin(); it != registro.end(); it++){
		if(it->pc == atoi(arg1)){
			std::cout << it->pc << std::endl;
			std::cout << it->ip << std::endl;
			
			result = it->ip;
		}
		
	}
	
	if(result == (char *)NULL){
			CLIENT *clnt;

			#ifndef	DEBUG
			clnt = clnt_create ("localhost", DNS2PROG, DNS2CVER, "udp");
			if (clnt == NULL) {
				clnt_pcreateerror ("localhost");
				exit (1);
			}
			#endif	/* DEBUG */
			
			char ** a = buscar_1(arg1, clnt);
			
			if(a != (char ** )NULL)
			result = *a;
			

		}

	return &result;
}

//EXAMEN

int *
modificar_1_svc(char *arg1, char *arg2, int arg3,  struct svc_req *rqstp)
{
	static int  result = 0;
	result = 0;					//NECESARIO DUPLICAR ASIGNACION PARA QUE LA REALICE

	if(arg3 == 1){
		for(auto it = registro.begin(); it != registro.end(); it++){
			if(it->pc == atoi(arg1)){
				it->ip = strdup(arg2);	//strdup() CREA MEMORIA PARA LA IP
				result = 1;
			}
		}
	}else{				// SI EL ARGUMENTO 3 <dns> NO ES 1 BUSCARA EN EL DNS2
		CLIENT *clnt;

			#ifndef	DEBUG
			clnt = clnt_create ("localhost", DNS2PROG, DNS2CVER, "udp");
			if (clnt == NULL) {
				clnt_pcreateerror ("localhost");
				exit (1);
			}
			#endif	/* DEBUG */
			
			int *a = modificar_1(arg1, arg2, arg3, clnt);
			
			if(a != (int * )NULL)
			result = *a;
	}

	return &result;
}