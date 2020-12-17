#include <SFML/Graphics.hpp>
#include <iostream>
#include "BasicBoard.h"
#include <map>
#include <string>
#include "Sprits.h"
using namespace std;
int main()
{
    bool startOver = false;
    bool win = false;
    bool lose = false;
    bool gameOver = false;
    bool debug = false;
    bool winOrLose = false;
    BasicBoard board;
    int flagCount = 0;
    vector<vector<int>> mineLocation;

    sf::RenderWindow window(sf::VideoMode(800, 600), "myWindow");
    window.setTitle("Minesweeper");
    sf::Event even;
    while (window.isOpen()) {
        window.clear();
        Sprits dra;
        int height=0;
        for (int i = 0; i < board.height; i++) {
            height = i * -32;
            vector<Tile*> row = board.board.at(i);
            sf::Sprite spret;
            for (int j = 0; j < board.width;j++) {
                Tile* tile = row.at(j);
                if (tile->revealed == false) {
                    spret.setTexture(dra.textures["tile_hidden"]);
                }
                else {
                    spret.setTexture(dra.textures["tile_revealed"]);
                }
                if (lose == true && tile->hasMine == true) {
                    spret.setTexture(dra.textures["tile_revealed"]);
                }
                if (tile->hasMine == true) {
                    mineLocation.push_back({ -32 * j, height });
                }
                spret.setOrigin(-32 * j, height);
                sf::FloatRect rect = spret.getGlobalBounds();
                tile->bound = rect;
                window.draw(spret);
                if (tile->revealed == true) {
                    if (tile->numMines > 0) {
                        sf::Sprite revDig;
                        if (tile->numMines == 1) {
                            revDig.setTexture(dra.textures["number_1"]);
                        }
                        if (tile->numMines == 2) {
                            revDig.setTexture(dra.textures["number_2"]);
                        }
                        if (tile->numMines == 3) {
                            revDig.setTexture(dra.textures["number_3"]);
                        }
                        if (tile->numMines == 4) { 
                            revDig.setTexture(dra.textures["number_4"]); 
                        }
                        if (tile->numMines == 5) {
                            revDig.setTexture(dra.textures["number_5"]);
                        }
                        if (tile->numMines == 6) {
                            revDig.setTexture(dra.textures["number_6"]);
                        }
                        if (tile->numMines == 7) {
                            revDig.setTexture(dra.textures["number_7"]);
                        }
                        if (tile->numMines == 8) {
                            revDig.setTexture(dra.textures["number_8"]);
                        }
                        revDig.setOrigin(-32 * j, height);
                        window.draw(revDig);
                    }
                }
                if (tile->flag == true) {
                    sf::Sprite sp(dra.textures["flag"]);
                    sp.setOrigin(-32 * j, height);
                    window.draw(sp);
                }
                if ((debug == true|| lose==true)&&tile->hasMine==true) {
                    sf::Sprite mine(dra.textures["mine"]);
                    mine.setOrigin(-32 * j, height);
                    window.draw(mine);
                }
            }
        }
        if (gameOver == true) {
            for (unsigned int i = 0; i < board.board.size(); i++) {
                vector<Tile*> row = board.board.at(i);
                for (int j = 0; j < row.size();j++) {
                    Tile* d = row.at(j);
                    d->revealed = true;
                }
            }
        }

        
        vector<int> indexes = dra.Digit(board.mineCount-flagCount);
        for ( int i = 0; i < indexes.size();i++) {
            sf::Sprite digit=dra.digSprit.at(indexes.at(i));
            digit.setOrigin(-22 * i, height - 32);
            window.draw(digit);
        }

        //debug and test buttons
        sf::Sprite debugB(dra.textures["debug"]);
        sf::Sprite testOne(dra.textures["test_1"]);
        sf::Sprite testTwo(dra.textures["test_2"]);
        sf::Sprite testThree(dra.textures["test_3"]);
        sf::Sprite happyFace(dra.textures["face_happy"]);
        sf::Sprite winFace(dra.textures["face_win"]);
        sf::Sprite loseFace(dra.textures["face_lose"]);
        testThree.setOrigin(-800+64+48, height - 32);
        dra.buttons.push_back("test 3");
        dra.buttonLocations.push_back(testThree.getGlobalBounds());

        testTwo.setOrigin(-800 + 64*2 + 48, height - 32);
        dra.buttons.push_back("test 2");
        dra.buttonLocations.push_back(testTwo.getGlobalBounds());
        
        testOne.setOrigin(-800 + 64*3 + 48, height - 32);
        dra.buttons.push_back("test 1");
        dra.buttonLocations.push_back(testOne.getGlobalBounds());

        debugB.setOrigin(-800 + 64 * 4 + 48, height - 32);
        dra.buttons.push_back("debug");
        dra.buttonLocations.push_back(debugB.getGlobalBounds());
        
        
        window.draw(testOne);
        window.draw(testTwo);
        window.draw(testThree);
        window.draw(debugB);

        if (gameOver != true) {
            happyFace.setOrigin(-800 + 64 * 6 + 48, height - 32);
            window.draw(happyFace);
        }
        if (win == true) {
            winFace.setOrigin(-800 + 64 * 6 + 48, height - 32);
            dra.buttons.push_back("face");
            dra.buttonLocations.push_back(winFace.getGlobalBounds());
            window.draw(winFace);
        }
        if (lose == true) {
            loseFace.setOrigin(-800 + 64 * 6 + 48, height - 32);
            dra.buttons.push_back("face");
            dra.buttonLocations.push_back(loseFace.getGlobalBounds());
            window.draw(loseFace);
        }
        //button stuff
        //left click
        string boardName;
        string buttonPress="nothing";
        while (window.pollEvent(even)) {
            if (even.type == sf::Event::EventType::Closed) {
                window.close();
            }
            if (even.type == sf::Event::MouseButtonPressed) {
                if (even.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePos = window.mapPixelToCoords(localPosition);
                    for (unsigned int i = 0; i < dra.buttonLocations.size(); i++) {
                        if (dra.buttonLocations.at(i).contains(mousePos)) {
                            buttonPress = dra.buttons.at(i);
                            //cout << buttonPress;
                        }
                    }
                    if (buttonPress == "debug") {
                        if (debug == true) {
                            debug = false;
                        }
                        else if (debug == false) {
                            debug = true;
                        }
                    }
                    if (buttonPress == "test 1") {
                        boardName = "boards/testboard1.brd";
                        startOver = true;
                    }
                    if (buttonPress == "test 2") {
                        boardName = "boards/testboard2.brd";
                        startOver = true;
                    }
                    if (buttonPress == "test 3") {
                        boardName = "boards/testboard3.brd";
                        startOver = true;
                    }
                    if (buttonPress == "face") {
                        startOver = false;
                        win = false;
                        lose = false;
                        gameOver = false;
                        winOrLose = false;
                        flagCount = 0;
                        board.RestartRandom();
                    }

                    if (buttonPress == "nothing" && gameOver == false && winOrLose == false) {
                        for (int i = 0; i < board.height; i++)
                        {
                            vector<Tile*> rowX = board.board.at(i);
                            for (int j = 0; j < board.width; j++) {
                                if (rowX.at(j)->bound.contains(mousePos) && rowX.at(j)->flag != true && rowX.at(j)->revealed != true) {
                                    rowX.at(j)->revealed = true;
                                    if (rowX.at(j)->hasMine == true) {
                                        lose = true;
                                    }
                                    else {
                                        if (rowX.at(j)->numMines > 0) {
                                        }
                                        else {
                                            board.RevealTiles(rowX.at(j));
                                        }
                                    }
                                }
                            }
                        }
                    }


                }
                //right click
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && gameOver == false && winOrLose == false) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePos = window.mapPixelToCoords(localPosition);
                    for (int i = 0; i < board.height; i++)
                    {
                        vector<Tile*> rowX = board.board.at(i);
                        for (int j = 0; j < board.width; j++) {
                            if (rowX.at(j)->bound.contains(mousePos)) {
                                if (rowX.at(j)->flag == false && rowX.at(j)->revealed != true) {
                                    rowX.at(j)->flag = true;
                                    flagCount += 1;
                                }
                                else if (rowX.at(j)->revealed == false) {
                                    rowX.at(j)->flag = false;
                                    flagCount--;
                                }

                            }
                        }
                    }
                }
            }
        }
        if (startOver == true) {
            board.Restart(boardName);
            startOver = false;
            win = false;
            lose = false;
            gameOver = false;
            winOrLose = false;
            flagCount = 0;
            
        }
        if (lose == true) {
            winOrLose = true;
        }
        win= board.CheckWin();
        if (win == true) {
            flagCount = board.mineCount;
             winOrLose = true;
             for (int i = 0; i < board.height; i++) {
                 vector<Tile*> vecTil = board.board.at(i);
                 for (int k = 0; k < board.width; k++) {
                     Tile* tileOne = vecTil.at(k);
                     if (tileOne->hasMine == true) {
                         tileOne->flag = true;
                     }
                 }
             }
            }
        window.display();
    
    }
  
    return 0;
}