/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"


/* Funcion calculadora del cliente
	  Devuelve un entero con el resultado.
		se le pasan los dos numeros y un operador.
*/
int
calcprog_1(char *host,int arg1,char operator,int arg2)
{
	CLIENT *clnt;
	int  *result_1;                   // puntero a entero que almacena el resultado
	int arg_calculadora_1 = arg1;
	int arg_calculadora_2 = arg2;


#ifndef	DEBUG
	clnt = clnt_create (host, CALCPROG, CALCVER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	// El switch realiza una funcion dependiendo del valor del operador

	switch (operator) {
		case '+': result_1 = add_1(arg_calculadora_1,arg_calculadora_2,clnt); break;
		case '-': result_1 = sub_1(arg_calculadora_1,arg_calculadora_2,clnt);break;
		case '*': result_1 = mult_1(arg_calculadora_1,arg_calculadora_2,clnt);break; // Para que funcione en el terminal el operador * se escribe como \*
		case '/': result_1 = div_1(arg_calculadora_1,arg_calculadora_2,clnt);break;
	}

	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
	// Faltaria liberar memopria.


	// Devolvemos el contenido del puntero a resultado.
	return *result_1;
}


int
main (int argc, char *argv[])
{
	char *host;
	char operator;
	int arg1;
	int arg2;
	int result;

	if (argc < 5) {
		printf ("usage: %s server_host numero operador numeros\n", argv[0]);
		exit (1);
	}

	host = argv[1];
	arg1 = atoi(argv[2]);
	operator = *argv[3];
	arg2 = atoi(argv[4]);

	result = calcprog_1 (host,arg1,operator,arg2);

	// Imprimo resultado por pantalla
	printf("%d\n",result );
exit (0);
}
