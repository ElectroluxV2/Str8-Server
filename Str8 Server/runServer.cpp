#include "Server.h"
#include <stdio.h>
#include <string>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <Windows.h>
#include <thread>

using namespace rapidjson;

void Server::run() {

	thread mobs(&Server::mobs, this);

	while (1) {

		fflush(stdout);

		// Clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		// Try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(soc, buf, BUFLEN, 0, (struct sockaddr *) &client, &client_len)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		printf("%s\n", buf);

		player p = parseResponse(buf);

		// Calculate view for player
		int rStartX = p.position.x - renderDistanceX;
		int rEndX = p.position.x + renderDistanceX;
		int rStartY = p.position.y - renderDistanceY;
		int rEndY = p.position.y + renderDistanceY;

		// Encode
		StringBuffer json;
		Writer<StringBuffer> writer(json);
		writer.StartObject();
		writer.Key("map");
		writer.StartArray();

		for (int y = rStartY; y < rEndY; y++) {
			writer.StartArray();
			for (int x = rStartX; x < rEndX; x++) {

				bool writeBlock = true;
				writer.StartArray();
				for (auto &playerToCheck : map.players) {
					if ((playerToCheck.position.y == y) && (playerToCheck.position.x == x)) {
						writeBlock = false;

						writer.Int(p.face);
						writer.Int(p.color);
						// BUG If more than one player stands on the same block,(should not be possible) only first one will be seen.
						// Save cpu
						break;
					}
				}
				for (auto &mob : map.mobs) {
					if ((mob.position.y == y) && (mob.position.x == x)) {
						writeBlock = false;

						writer.Int(mob.face);
						writer.Int(mob.color);
						// BUG If more than one mob stands on the same block,(should not be possible) only first one will be seen.
						// Save cpu
						break;
					}
				}

				if (writeBlock) {

					writer.Int(map.get(y, x).face);
					writer.Int(map.get(y, x).color);
				}
				writer.EndArray();
			}
			writer.EndArray();
		}
		writer.EndArray();

		writer.Key("cords");
		writer.StartObject();
		writer.Key("y");
		writer.Int(p.position.y);
		writer.Key("x");
		writer.Int(p.position.x);
		writer.Key("hp");
		writer.Int(p.hp);
		writer.EndObject();

		writer.EndObject();

		// Send the package
		if (sendto(soc, json.GetString(), strlen(json.GetString()), 0, (struct sockaddr *) &client, client_len) == SOCKET_ERROR)
		{
			printf("Packet:\n%s\nWas failed send to %d:%d.\nStackTrace: %d", json.GetString(), client.sin_addr, client.sin_port, WSAGetLastError());
		}
	}
}