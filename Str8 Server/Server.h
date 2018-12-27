#include <winsock2.h>
#include "structs.h"
#pragma comment(lib,"ws2_32.lib") // Winsock Library
class Server {
protected:
	/// Max buffor length
#define BUFLEN 512
/// Port to listen for incoming data
#define PORT 8888

// Response
	char buf[BUFLEN];

	// WinSock stuff
	WSADATA wsa;
	SOCKET soc;
	struct sockaddr_in server, client;
	int client_len, recv_len;

	// Map of blocks
	struct map map;

	// Rednder distance
	int renderDistanceX = 18;
	int renderDistanceY = 8;
public:
	void mobs();
	void initialization();
	void run();
	player parseResponse(char* response);
	Server();
	~Server();
};

