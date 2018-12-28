#include "Server.h"
#include <stdio.h>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

player* Server::parseResponse(char* response) {

	Document res;
	if (res.Parse(buf).HasParseError()) {
		printf("Parse error from %s:%d", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
	}

	if (res.HasMember("mes")) {
		printf("%s\n", buf);
		return map.getPlayer(res["nick"].GetString());
	}

	if (!res.HasMember("nick")) {
		printf("Invalid requisent");
	}

	string nick = res["nick"].GetString();

	player resPlayer;
	resPlayer.nick = nick;
	resPlayer.client = client;

	bool addPlayer = true;
	for (player &player : map.players) {
		if (player.nick == resPlayer.nick) {
			addPlayer = false;
			break;
		}
	}

	if (addPlayer) {
		map.players.push_back(resPlayer);
	}

	player* player = map.getPlayer(nick);

	const Value& moves = res["kb"]; // Using a reference for consecutive access is handy and faster.

	for (SizeType i = 0; i < moves.Size(); i++) {
		if (moves[i].GetString() == string("d")) {
			if (map.isSuitableForEntry(player->position.y, player->position.x + 1))
				player->position.x++;
		}
		else if (moves[i].GetString() == string("a")) {
			if (map.isSuitableForEntry(player->position.y, player->position.x - 1))
				player->position.x--;
		}
		else if (moves[i].GetString() == string("s")) {
			if (map.isSuitableForEntry(player->position.y + 1, player->position.x))
				player->position.y++;
		}
		else if (moves[i].GetString() == string("w")) {
			if (map.isSuitableForEntry(player->position.y - 1, player->position.x))
				player->position.y--;
		}
		else if (moves[i].GetString() == string("h")) {
			block b = map.get(player->position);
			b.face++;
			map.set(player->position, b);
		}
		else if (moves[i].GetString() == string("j")) {
			block b = map.get(player->position);
			b.face--;
			map.set(player->position, b);
		}
		else if (moves[i].GetString() == string("k")) {
			block b = map.get(player->position);
			b.color++;
			map.set(player->position, b);
		}
		else if (moves[i].GetString() == string("l")) {
			block b = map.get(player->position);
			b.color--;
			map.set(player->position, b);
		}
		else if (moves[i].GetString() == string("`")) {

		}
	}
	return player;
}