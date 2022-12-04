#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Colours.h"

class Entity {
	private:
		int nWidth, nHeight;
		bool bIsMine, bRevealed, bFlagged;
		int nMinesAround;

		Colour sf_colour;
		sf::RectangleShape sf_rect;
		sf::Text sf_mineNumber;

	public:
		Entity(int _width, int _height, int _x, int _y, Colour _colour, sf::Font &_font);
		void setIsMine(bool _isMine);
		bool isMine();
		int getMinesAround();
		
		void setFlag();
		void takeFlag();
		bool isFlagged();

		void setNumberColour(Colour colour);

		void increaseMinesAround();
		
		void revealEntity();
		bool isRevealed();
		sf::RectangleShape getRect();
		void drawEntity(sf::RenderWindow &window);
};

#endif