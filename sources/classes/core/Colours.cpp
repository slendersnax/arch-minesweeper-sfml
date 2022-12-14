#include "Colours.h"

sf::Color getSzin(Colour colour) {
	switch (colour) {
		case Colour::White:
			return sf::Color(255, 255, 255);
			break;
		case Colour::Black:
			return sf::Color(0, 0, 0);
			break;
		case Colour::Grey:
			return sf::Color(102, 102, 132);
			break;
		case Colour::BrightGrey:
			return sf::Color(132, 132, 162);
			break;
		case Colour::Red:
			return sf::Color(255, 0, 0);
			break;
		case Colour::BrightRed:
			return sf::Color(255, 70, 70);
			break;
		case Colour::Green:
			return sf::Color(0, 255, 0);
			break;
		case Colour::DarkGreen:
			return sf::Color(0, 124, 60);
			break;
		case Colour::Blue:
			return sf::Color(0, 0, 255);
			break;
		case Colour::PastelBlue:
			return sf::Color(0, 124, 200);
			break;
		case Colour::Purple:
			return sf::Color(190, 10, 200);
			break;
		case Colour::Yellow:
			return sf::Color(220, 220, 10);
			break;
		case Colour::Orange:
			return sf::Color(170, 69, 10);
			break;
		default:
			return sf::Color(255, 255, 255);
			break;
	}
}