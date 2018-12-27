#include "Server.h"
#include <stdio.h>

Server::Server() {
	client_len = sizeof(client);
	printf("Constructor run: %d\n", BUFLEN);
}


Server::~Server() {
	printf("Destructor run\n");
}
