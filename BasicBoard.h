#pragma once
#include <vector>
#include <string>
#include "Tile.h"
#include <vector>
class BasicBoard {
public:
	int height = 16;
	int width = 25;
	int tileCount = 400;
	int windowSize = 800 * 600;
	int mineCount = 0;
	std::vector<std::vector<Tile*>> board;
	BasicBoard();
	BasicBoard(std::string file);
	void Restart(std::string boardName);
	void Check();
	bool CheckWin();
	void RevealTiles(Tile* til);
	void RestartRandom();
};
