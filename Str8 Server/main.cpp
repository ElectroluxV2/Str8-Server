/*
	Our Game Server
*/
#include "Server.h"

int main() {

	/// Create master object
	Server server;

	// TODO: Read server settings

	/// Init
	server.initialization();

	/// Run 4ever
	/// Pierwszy
	server.run();
}