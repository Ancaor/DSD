#include <string.h>
#include <list>
#include <iostream>

using namespace std;

struct fila{
	int pc;
	char *ip;
};

std::list<fila> registro;



int *
registrar_1_svc(const char *arg1,const  char *arg2)
{
	static int  result = 1;

	fila lafila;
	lafila.pc = atoi(arg1);	
	std::string str(arg2);
	lafila.ip =  strdup(arg2);
	registro.push_back(lafila);
	 free(lafila.ip);
	 
	return &result;
}

int main(){
    std::string s = "1";
    std::string aaa = "aasda";
    const char * aa = s.c_str();
    const char * as = aaa.c_str();

    int *r = registrar_1_svc(aa,as);

    cout << registro.begin()->ip;
}
