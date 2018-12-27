#include "Server.h"
#include <stdio.h>

void Server::initialization() {
	// Initialise winsock
	printf("Initialising Winsock...  ");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("[FAILED]\nStackTrace: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("[DONE]\n");

	// Create a socket
	printf("Creating socket...  ");
	if ((soc = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("[FAILED]\nStackTrace: %d\n", WSAGetLastError());
	}
	printf("[DONE]\n");

	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	// Bind
	printf("Bind to port %d...  ", server.sin_port);
	if (bind(soc, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("[FAILED]\nStackTrace: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("[DONE]\n");

	// Initialize map
	printf("Initialising map...  ");
	map.initialize(100, 100);
	// TODO: loading map from file
	map.generate();
	printf("Map file not found, generated new one...  ");
	printf("[DONE]\n");
}