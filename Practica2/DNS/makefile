CLIENT = dns_client
SERVER = dns_server

LDLIBS += -lnsl

all : 
	g++ -g dns_server.c dns_svc.c dns_xdr.c -o dns_server -lnsl 
	g++ -g dns_client.c dns_clnt.c dns_xdr.c -o dns_cliente -lnsl 