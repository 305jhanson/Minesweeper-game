#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
class Sprits {
public:
	std::unordered_map<std::string, sf::Texture> textures;
	std::vector<sf::FloatRect> boxes;
	std::vector<sf::Sprite> digSprit;
	Sprits();
	std::vector<int> Digit(int num);
	std::vector<std::string> buttons;
	std::vector<sf::FloatRect> buttonLocations;



};
