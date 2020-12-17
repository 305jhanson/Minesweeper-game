#include "Tile.h"
using namespace std;
Tile::Tile() {
	hasMine = false;
	revealed = false;
	flag = false;
	numMines = 0;
}
void Tile::AddNeighbor(Tile* neighbor) {
	neighbors.push_back(neighbor);
}
void Tile::CheckMines() {
	for (unsigned int i = 0; i < neighbors.size();i++) {
		if (neighbors.at(i)->hasMine == true) {
			numMines++;
		}
	}
}