/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALCULADORA_H_RPCGEN
#define _CALCULADORA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct add_1_argument {
	int arg1;
	int arg2;
};
typedef struct add_1_argument add_1_argument;

struct sub_1_argument {
	int arg1;
	int arg2;
};
typedef struct sub_1_argument sub_1_argument;

struct mult_1_argument {
	int arg1;
	int arg2;
};
typedef struct mult_1_argument mult_1_argument;

struct div_1_argument {
	int arg1;
	int arg2;
};
typedef struct div_1_argument div_1_argument;

#define CALCPROG 0x20000199
#define CALCVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define ADD 1
extern  int * add_1(int , int , CLIENT *);
extern  int * add_1_svc(int , int , struct svc_req *);
#define SUB 2
extern  int * sub_1(int , int , CLIENT *);
extern  int * sub_1_svc(int , int , struct svc_req *);
#define MULT 3
extern  int * mult_1(int , int , CLIENT *);
extern  int * mult_1_svc(int , int , struct svc_req *);
#define DIV 4
extern  int * div_1(int , int , CLIENT *);
extern  int * div_1_svc(int , int , struct svc_req *);
extern int calcprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ADD 1
extern  int * add_1();
extern  int * add_1_svc();
#define SUB 2
extern  int * sub_1();
extern  int * sub_1_svc();
#define MULT 3
extern  int * mult_1();
extern  int * mult_1_svc();
#define DIV 4
extern  int * div_1();
extern  int * div_1_svc();
extern int calcprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_add_1_argument (XDR *, add_1_argument*);
extern  bool_t xdr_sub_1_argument (XDR *, sub_1_argument*);
extern  bool_t xdr_mult_1_argument (XDR *, mult_1_argument*);
extern  bool_t xdr_div_1_argument (XDR *, div_1_argument*);

#else /* K&R C */
extern bool_t xdr_add_1_argument ();
extern bool_t xdr_sub_1_argument ();
extern bool_t xdr_mult_1_argument ();
extern bool_t xdr_div_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALCULADORA_H_RPCGEN */
