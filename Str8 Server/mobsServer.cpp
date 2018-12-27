#include "Server.h"
#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>

int countDistance(cords p1, cords p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void Server::mobs()
{
	while (1) {
		Sleep(350);

		for (mob &m : map.mobs) {

			for (player &p : map.players) {
				if (countDistance(p.position, m.position) < 7)
				{
					m.setTarget(&p);
					break;
				}
				else {
					m.removeTarget();
				}
			}

			if (!m.hasTarget()) {
				continue;
			}

			if (!(countDistance(m.getTarget()->position, m.position) < 2)) {
				if (m.getTarget()->position.x > m.position.x)
				{
					m.position.x++;
				}
				if (m.getTarget()->position.x < m.position.x)
				{
					m.position.x--;
				}
				if (m.getTarget()->position.y > m.position.y)
				{
					m.position.y++;
				}
				if (m.getTarget()->position.y < m.position.y)
				{
					m.position.y--;
				}
			}
			else
			{
				if (m.getTarget()->hp > 0)
					m.getTarget()->hp -= 1;
				if (m.getTarget()->hp <= 0)
					m.getTarget()->kill();
			}
			cout << "XBOT : " << m.position.x << " Y: " << m.position.y << endl;
			cout << "XGRACZ: " << m.getTarget()->position.x << " Y: " << m.getTarget()->position.y << endl;
			cout << map.players.size() << endl;
		}
	}
}