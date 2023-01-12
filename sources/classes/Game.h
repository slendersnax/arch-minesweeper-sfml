#ifndef GAME_H
#define GAME_H

#include <vector>
#include "core/Entity.h"

class Game {
	private:
		int nWindowWidth, nWindowHeight, nStdWidth, nOffsetY;
	    int nRows, nCols;
	    int nMines;
	    std::vector<Entity> entities;

	    sf::Font sf_font;
	    sf::Text sf_flagsLeft;
	    sf::Text sf_endGameMsg;
	public:
		Game();
		void init();
		void reInit(); // reinitialise after a game
		void initEntities();
		void blankEntities();
		void initMines();
		void colourNumbers();
		void revealEntitiesAround(int pos);
		bool allMinesFlagged();
		void mainLoop();
};

#endif