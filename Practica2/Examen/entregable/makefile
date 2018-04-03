CLIENT = dns_client
SERVER = dns_server

LDLIBS += -lnsl

all : 
	g++ -g -std=c++11 dns_server.c dns_svc.c dns_xdr.c dns_clnt.c -o dns_server -lnsl 
	g++ -g -std=c++11 dns_client.c dns_clnt.c dns_xdr.c -o dns_cliente -lnsl 
	g++ -g -std=c++11 dns2_server.c dns2_svc.c dns_xdr.c -o dns2_server -lnsl
	g++ -g -std=c++11 dns2_client.c dns_clnt.c dns_xdr.c -o dns2_cliente -lnsl 
