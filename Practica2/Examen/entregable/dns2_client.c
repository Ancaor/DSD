/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "dns.h"
#include <iostream>

void
dnsprog_1(char *host,char *operacion, char *pc, char *ip, int dns)
{
	CLIENT *clnt;
	int  *result_1 = NULL;
	char *registrar_1_arg1 = pc;
	char *registrar_1_arg2 = ip;
	int  *result_2 = NULL;
	char *eliminar_1_arg1 = pc;
	char * *result_3 = NULL;
	char *buscar_1_arg1 = pc;
	// EXAMEN
	int  *result_4 = NULL;
	char *modificar_1_arg1 = pc;
	char *modificar_1_arg2 = ip;
	int modificar_1_arg3 = dns;
	//
#ifndef	DEBUG
	clnt = clnt_create (host, DNS2PROG, DNS2CVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	if(strcmp(operacion,"registrar") == 0){
	result_1 = registrar_1(registrar_1_arg1, registrar_1_arg2, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	std::cout << "\nResultado de registro:" << *result_1 << "\n";

}else if(strcmp(operacion,"eliminar") == 0){
	result_2 = eliminar_1(eliminar_1_arg1, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	std::cout << "\nResultado de eliminar entrada:" << *result_2 << "\n";

}else if(strcmp(operacion,"buscar") == 0){
	result_3 = buscar_1(buscar_1_arg1, clnt);
	if (result_3 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	std::cout << "\nResultado de busqueda de " << buscar_1_arg1 << " :" << *result_3 << "\n";
	
	

}else if(strcmp(operacion,"modificar") == 0){
	result_4 = modificar_1(modificar_1_arg1, modificar_1_arg2, modificar_1_arg3, clnt);
	if (result_4 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else if(*result_4 == 2){
		std::cout << "\nModificacion realizada con exito\n";
	}else std::cout << "\nModificacion no realizada\n";
}

/*
	r
*/

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	char *operacion;
	char *pc;
	char *ip;
	int dns;

	if (argc < 3) {
		printf ("usage: %s server_host operacion\n", argv[0]);
		exit (1);
	}

	host = argv[1];
	operacion = argv[2];
	pc = argv[3];
	
	

	if(strcmp(operacion,"registrar") == 0){
		ip = argv[4];
		if(argc < 5){
			printf ("usage: %s server_host registrar pc ip\n", argv[0]);
		exit (1);
		}
	}else if(strcmp(operacion,"eliminar") == 0){
		if(argc < 4){
			printf ("usage: %s server_host eliminar pc\n", argv[0]);
			exit (1);
		}
	}else if(strcmp(operacion,"buscar") == 0){
		if(argc < 4){
			printf ("usage: %s server_host buscar pc\n", argv[0]);
		exit (1);
		}
	}else if(strcmp(operacion,"modificar") == 0){
		ip = argv[4];
		dns = std::atoi(argv[5]);
		if(argc < 6){
			printf ("usage: %s server_host modificar pc nueva_ip dns\n", argv[0]);
		exit (1);
		}
	}
	dnsprog_1 (host,operacion,pc,ip,dns);
	//std::cout << "dasd";
exit (0);
}
