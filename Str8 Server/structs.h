#include <vector>
#include <string>
using namespace std;

struct cords {
	int x = 0;
	int y = 0;
};

struct player {
	SOCKADDR_IN client;
	cords position = { 50, 50 };
	cords relativePosition = { 0, 0 };
	string nick = "";
	int hp = 100;
	char face = 'o';
	int color = 02;
	void kill()
	{
		face = 'x';
		color = 04;
	}

	bool equals(player p) {
		return (p.nick == nick);
	}
};


struct mob
{

	player *mTarget;
	bool mHasTarget = false;

	cords position = { 50, 50 };
	// Default pssive
	int color = 02;
	char face = 'M';

	void setTarget(player *target) {
		mTarget = target;
		color = 04;
		mHasTarget = true;
	}

	void removeTarget() {
		//target = NULL;
		color = 03;
		mHasTarget = false;
	}

	player* getTarget() {
		return mTarget;
	}

	bool hasTarget() {
		return this->mHasTarget;
	}
};

struct block {
	bool playerCanEnter;
	char face;
	int color;
};

struct map {
	vector<mob> mobs;
	vector<player> players;

	struct size {
		int y;
		int x;
		int totalIndexes;
	};

	size size;
	block *blocks;

	inline block& get(int y, int x) { return blocks[x * (size.y) + y]; }
	inline block& get(int index) { return blocks[index]; }
	inline void set(int y, int x, block block) { blocks[x * (size.y) + y] = block; }
	inline void set(int index, block block) { blocks[index] = block; }

	player& getPlayer(string nick) {
		for (player &player : players) {

			if (player.nick != nick) {
				continue;
			}
			return player;
		}
	}

	void initialize(int y, int x) {
		size.y = y;
		size.x = x;
		size.totalIndexes = (y) * (x);
		blocks = new block[size.totalIndexes];
	}

	void generate() {
		mob mob;
		for (int i = 0; i < 10; i++)
		{
			mob.position.x = 0 + rand() % 100;
			mob.position.y = 0 + rand() % 100;
			mob.face = to_string(i)[0];
			mobs.push_back(mob);
		}
		for (int index = 0; index < size.totalIndexes; index++) {



			int rnd = (rand() % 10) + 0;

			switch (rnd) {
			case 3:


			case 0:
			case 1:
			case 2:

			case 4:
			case 5:
			case 6:
			case 7:
				set(index, { true, ' ', 7 });
				break;
			case 8:
			case 9:
			default:
				set(index, { false, 'o', 15 });
				break;
			}
		}
	}
};
