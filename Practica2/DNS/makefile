CLIENT = dns_client
SERVER = dns_server

LDLIBS += -lnsl

all : $(CLIENT) $(SERVER)


$(CLIENT) : $(OBJECTS_CLNT) 
	g++ dns_client.c dns_clnt.c dns_xdr.c -o $(CLIENT) $(LDLIBS)

$(SERVER) : $(OBJECTS_SVC) 
	g++ dns_server.c dns_svc.c dns_xdr.c -o $(CLIENT) $(LDLIBS)

