#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Tile {
public:
	bool flag;
	bool hasMine;
	bool revealed;
	std::vector<Tile*> neighbors;
	int numMines;
	Tile();
	void AddNeighbor(Tile* neighbor);
	void CheckMines();
	sf::FloatRect bound;
};