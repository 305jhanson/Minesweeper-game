#include "BasicBoard.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <iterator>
using namespace std;






BasicBoard::BasicBoard() {
	// random mines
	vector<int> randomIndexs;
	int random = rand() % tileCount;
	randomIndexs.push_back(random);
	while (randomIndexs.size() != 50) {
		random = rand() % tileCount;
		if (find(randomIndexs.begin(), randomIndexs.end(), random) == randomIndexs.end()) {
			randomIndexs.push_back(random);
		}
	}
	for (unsigned int i = 0; i < randomIndexs.size(); i++) {
		//std::cout << randomIndexs.at(i) << endl;
	}







	//initialize board
	vector<Tile*> row;
	vector<Tile*> rowUp;
	vector<Tile*> rowDown;
	for ( int i = 0; i < height; i++) {
		row.clear();
		for ( int j = 0; j < width; j++) {
			row.push_back(new Tile);
		}
		board.push_back(row);
	}
	for (int i = 0; i < height; i++) {
		if (i == 0) {
			row.clear();
			rowUp.clear();
			row = board.at(0);
			rowUp = board.at(1);
			for (int j = 0; j < width; j++) {
				Tile* tile = row.at(j);
				if (j == 0) {
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j + 1));
				}
				else if (j == width - 1) {
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j - 1));
				}
				else {
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(rowUp.at(j - 1));
					tile->AddNeighbor(rowUp.at(j + 1));
				}
			}
		}
		else if (i == height - 1) {
			row.clear();
			rowDown.clear();
			row = board.at(i);
			rowDown = board.at(i - 1);
			for (int j = 0; j < width; j++) {
				Tile* tile = row.at(j);
				if (j == 0) {
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j + 1));
				}
				else if (j == width - 1) {
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j - 1));
				}
				else {
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j + 1));
					tile->AddNeighbor(rowDown.at(j - 1));
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(row.at(j + 1));
				}
			}
		}
		else {
			row.clear();
			rowDown.clear();
			rowUp.clear();
			row = board.at(i);
			rowDown = board.at(i - 1);
			rowUp = board.at(i + 1);
			for (int j = 0; j < width; j++) {
				Tile* tile = row.at(j);
				if (j == 0) {
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j + 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j + 1));
				}
				else if (j == width - 1) {
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j - 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j - 1));
				}
				else {
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j + 1));
					tile->AddNeighbor(rowDown.at(j - 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j + 1));
					tile->AddNeighbor(rowUp.at(j - 1));
				}
			}
		}
	}
	mineCount = 50;
	for (unsigned int i = 0; i < randomIndexs.size(); i++) {
		int mineNum = randomIndexs.at(i);
		int row = mineNum / width;
		int index = mineNum % width;
		vector<Tile*> rowA = board.at(row);
		Tile* tile = rowA.at(index);
		tile->hasMine = true;
	}

	for (int i = 0; i < height; i++) {
		vector<Tile*> rowCheck = board.at(i);
		for (int j = 0; j < width; j++) {
			Tile* tel = rowCheck.at(j);
			if (tel->hasMine == false) {
				tel->CheckMines();
			}
		}
	}




}

BasicBoard::BasicBoard(string file) {
	ifstream myFile(file);
	char c;
	int one=0;
	int in = 0;
	int jn = -1;
	int numT = 0;
	vector<vector<int>> b;
	vector<vector<int>> positions;
	vector<int> rowa;
	if (myFile.is_open()) {
		while (myFile.get(c)) {
			if (c == '0') {
				//cout << 0;
				rowa.push_back(0);
			}
			if ( c == '1') {
				//cout << 1;
				rowa.push_back(1);
				mineCount += 1;
			}
			if (rowa.size() == 25) {
				b.push_back(rowa);
				rowa.clear();
				//cout << endl;
			}

		}
	}

	vector<Tile*> row;
	vector<Tile*> rowUp;
	vector<Tile*> rowDown;
	for ( int i = 0; i < height; i++) {
		row.clear();
		for ( int j = 0; j < width; j++) {
			row.push_back(new Tile);
		}
		board.push_back(row);
	}
	for (int i = 0; i < height; i++) {
		if (i == 0) {
			row.clear();
			rowUp.clear();
			row = board.at(0);
			rowUp = board.at(1);
			for (int j = 0; j < width; j++) {
				Tile* tile = row.at(j);
				if (j == 0) {
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j + 1));
				}
				else if (j == width - 1) {
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j - 1));
				}
				else {
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(rowUp.at(j - 1));
					tile->AddNeighbor(rowUp.at(j + 1));
				}
			}
		}
		else if (i == height - 1) {
			row.clear();
			rowDown.clear();
			row = board.at(i);
			rowDown = board.at(i - 1);
			for (int j = 0; j < width; j++) {
				Tile* tile = row.at(j);
				if (j == 0) {
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j + 1));
				}
				else if (j == width - 1) {
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j - 1));
				}
				else {
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j + 1));
					tile->AddNeighbor(rowDown.at(j - 1));
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(row.at(j + 1));
				}
			}
		}
		else {
			row.clear();
			rowDown.clear();
			rowUp.clear();
			row = board.at(i);
			rowDown = board.at(i - 1);
			rowUp = board.at(i + 1);
			for (int j = 0; j < width; j++) {
				Tile* tile = row.at(j);
				if (j == 0) {
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j + 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j + 1));
				}
				else if (j == width - 1) {
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j - 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j - 1));
				}
				else {
					tile->AddNeighbor(row.at(j + 1));
					tile->AddNeighbor(row.at(j - 1));
					tile->AddNeighbor(rowDown.at(j));
					tile->AddNeighbor(rowDown.at(j + 1));
					tile->AddNeighbor(rowDown.at(j - 1));
					tile->AddNeighbor(rowUp.at(j));
					tile->AddNeighbor(rowUp.at(j + 1));
					tile->AddNeighbor(rowUp.at(j - 1));
				}
			}
		}
	}
	vector<Tile*> actual;
	for (unsigned int i = 0; i < b.size();i++) {
		vector<int> rowC = b.at(i);
		actual = board.at(i);
		for (unsigned int j = 0; j < rowC.size();j++) {
			if (rowC.at(j) == 1) {
				Tile* tile = actual.at(j);
				tile->hasMine = true;
			}
		}
	}
	for (int i = 0; i < height; i++) {
		vector<Tile*> rowCheck = board.at(i);
		for (int j = 0; j < width; j++) {
			Tile* tel = rowCheck.at(j);
			if (tel->hasMine == false) {
				tel->CheckMines();
			}
		}
	}
}

void BasicBoard::Check() {
	for ( int i = 0; i < height; i++) {
		vector<Tile*> row = board.at(i);
		for ( int j = 0; j < width; j++) {
			//cout << row.at(j)->hasMine;
		}
		//cout << endl;
	}

}
void BasicBoard::RestartRandom() {
	mineCount = 0;
	for (int i = 0; i < height; i++) {
		vector<Tile*> row = board.at(i);
		for (int j = 0; j < width;j++) {
			Tile* tel = row.at(j);
			tel->revealed = false;
			tel->hasMine = false;
			tel->numMines = 0;
			tel->flag = false;
		}
	}
	vector<int> randomIndexs;
	int random = rand() % tileCount;
	randomIndexs.push_back(random);
	while (randomIndexs.size() != 50) {
		random = rand() % tileCount;
		if (find(randomIndexs.begin(), randomIndexs.end(), random) == randomIndexs.end()) {
			randomIndexs.push_back(random);
		}
	}

	mineCount = 50;
	for ( int i = 0; i < randomIndexs.size(); i++) {
		int mineNum = randomIndexs.at(i);
		int row = mineNum / width;
		int index = mineNum % width;
		vector<Tile*> rowA = board.at(row);
		Tile* tile = rowA.at(index);
		tile->hasMine = true;
	}

	for (int i = 0; i < height; i++) {
		vector<Tile*> rowCheck = board.at(i);
		for (int j = 0; j < width; j++) {
			Tile* tel = rowCheck.at(j);
			if (tel->hasMine == false) {
				tel->CheckMines();
			}
		}
	}
}

void BasicBoard::Restart(std::string boardName) {
	mineCount = 0;
	for (int i = 0; i < height; i++) {
		vector<Tile*> row=board.at(i);
		for (int j = 0; j < width;j++) {
			Tile* tel = row.at(j);
			tel->revealed = false;
			tel->hasMine = false;
			tel->numMines = 0;
			tel->flag = false;
		}
	}
	vector<vector<int>> b;
	vector<vector<int>> positions;
	vector<int> rowa;
	ifstream myFile(boardName);
	char c;
	if (myFile.is_open()) {
		while (myFile.get(c)) {
			if (c == '0') {
				//cout << 0;
				rowa.push_back(0);
			}
			if (c == '1') {
				//cout << 1;
				rowa.push_back(1);
				mineCount += 1;
			}
			if (rowa.size() == 25) {
				b.push_back(rowa);
				rowa.clear();
				//cout << endl;
			}
		}
	}

			vector<Tile*> actual;
			for (unsigned int i = 0; i < b.size();i++) {
				vector<int> rowC = b.at(i);
				actual = board.at(i);
				for (unsigned int j = 0; j < rowC.size();j++) {
					if (rowC.at(j) == 1) {
						Tile* tile = actual.at(j);
						tile->hasMine = true;
					}
				}
			}

			for (int i = 0; i < height; i++) {
				vector<Tile*> rowCheck = board.at(i);
				for (int j = 0; j < width; j++) {
					Tile* tel = rowCheck.at(j);
					if (tel->hasMine == false) {
						tel->CheckMines();
					}
			}
		}
	}
bool BasicBoard::CheckWin() {
	bool win=true;
	for (int i = 0; i < height; i++) {
		vector<Tile*> rowCheck = board.at(i);
		for (int j = 0; j < width; j++) {
			Tile* tel = rowCheck.at(j);
			if (tel->revealed == false&&tel->hasMine==false) {
				win = false;
			}
		}
	}
	return win;
}


void BasicBoard::RevealTiles(Tile* til) {
	if (til->numMines == 0 && til->hasMine == false) {
		if (til->flag == false) {
			til->revealed = true;
		}
		for (unsigned int i = 0; i < til->neighbors.size(); i++) {
			Tile* te = til->neighbors.at(i);
			bool noRevealed;
			if (te->hasMine == false) {
				noRevealed = te->revealed;
				if (te->flag == false) {
					te->revealed = true;
				}
				if (noRevealed == false&& te->flag==false) {
					RevealTiles(te);
				}
			}
		}
	}
}