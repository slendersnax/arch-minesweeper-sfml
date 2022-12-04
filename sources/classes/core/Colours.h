#ifndef COLOURS_H
#define COLOURS_H

#include <SFML/Graphics.hpp>

enum class Colour { White, Black, Grey, BrightGrey, Red, BrightRed, Green, DarkGreen, Blue, PastelBlue, Purple, Yellow, Orange };

sf::Color getSzin(Colour colour);

#endif