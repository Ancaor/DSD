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
	//std::string str(arg2);
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
			//strcpy(result,(it->ip).c_str());
			//std::cout << it->ip << std::endl;
			
			//const char * aux = it->ip.c_str();
			//char *aux2 = "asd";
			//strcpy(aux2,aux);
			std::cout << it->pc << std::endl;
			std::cout << it->ip << std::endl;
			
			result = it->ip;
			//return &result;
		}
		
	}
	
	return &result;
}


int *
modificar_1_svc(char *arg1, char *arg2, int arg3,  struct svc_req *rqstp)
{
	static int  result = 0;

	for(auto it = registro.begin(); it != registro.end(); it++){
		if(it->pc == atoi(arg1)){
			it->ip = strdup(arg2);
			result = 2;
		}
	}

	return &result;
}
