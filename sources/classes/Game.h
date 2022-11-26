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
	public:
		Game();
		void init();
		void initEntities();
		void initMines();
		void revealEntitiesAround(int pos);
		bool allMinesFlagged();
		void mainLoop();
};

#endif