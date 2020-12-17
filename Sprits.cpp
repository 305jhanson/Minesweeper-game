#include "Sprits.h"
#include "BasicBoard.h"
#include <iostream>
using namespace std;
Sprits::Sprits() {
    textures["tile_hidden"].loadFromFile("images/tile_hidden.png");
    textures["tile_revealed"].loadFromFile("images/tile_revealed.png");
    textures["test_1"].loadFromFile("images/test_1.png");
    textures["test_2"].loadFromFile("images/test_2.png");
    textures["test_3"].loadFromFile("images/test_3.png");
    textures["tile_revealed"].loadFromFile("images/tile_revealed.png");
    textures["number_1"].loadFromFile("images/number_1.png");
    textures["number_2"].loadFromFile("images/number_2.png");
    textures["number_3"].loadFromFile("images/number_3.png");
    textures["number_4"].loadFromFile("images/number_4.png");
    textures["number_5"].loadFromFile("images/number_5.png");
    textures["number_6"].loadFromFile("images/number_6.png");
    textures["number_7"].loadFromFile("images/number_7.png");
    textures["number_8"].loadFromFile("images/number_8.png");
    textures["mine"].loadFromFile("images/mine.png");
    textures["flag"].loadFromFile("images/flag.png");
    textures["digits"].loadFromFile("images/digits.png");
    textures["debug"].loadFromFile("images/debug.png");
    textures["face_happy"].loadFromFile("images/face_happy.png");
    textures["face_lose"].loadFromFile("images/face_lose.png");
    textures["face_win"].loadFromFile("images/face_win.png");
    for (int i = 0; i < 11; i++) {
        sf::Sprite dig(textures["digits"]);
        dig.setTextureRect(sf::IntRect(21 * i, 0, 21, 32));
        digSprit.push_back(dig);
    }
}

vector<int> Sprits::Digit(int num) {
    vector<int> ret;
    if (num < 0) {
        ret.push_back(10);
        num = -num;
    }

    int third = num % 10;
    num = num / 10;
    int second = num % 10;
    num = num/10;
    int first = num%10;
    ret.push_back(first);
    ret.push_back(second);
    ret.push_back(third);
    return ret;
}