#include <iostream>
#include <time.h>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "core/Entity.h"
#include "core/helper_functions.h"

Game::Game() {
	nWindowWidth = 500;
	nWindowHeight = 500;
	nOffsetY = 40;
	nStdWidth = 25;
	nMines = nStdWidth * 2;

	nRows = nWindowHeight / nStdWidth;
	nCols = nWindowWidth / nStdWidth;
}

// initialisers -------------------------------------
void Game::init() {
	srand(time(NULL));
	sf_font.loadFromFile("/home/abi/Documents/Projects_abi/made on linux/cpp-linux/sfml-projects/minesweeper/sources/classes/res/CONSOLA.TTF");

	this->sf_flagsLeft.setFont(sf_font);
	this->sf_flagsLeft.setString("Flags: 0");
	this->sf_flagsLeft.setPosition(10, 5);
	this->sf_flagsLeft.setCharacterSize(24);
	this->sf_flagsLeft.setFillColor(getSzin(Colour::Green));

	this->sf_endGameMsg.setFont(sf_font);
	this->sf_endGameMsg.setString("Press y to play again,\nn to close");
	this->sf_endGameMsg.setPosition(140, 7);
	this->sf_endGameMsg.setCharacterSize(12);
	this->sf_endGameMsg.setFillColor(getSzin(Colour::White));

	this->initEntities();
	this->initMines();
	this->colourNumbers();
}

void Game::reInit() {
	this->sf_flagsLeft.setString("Flags: " + intToString(this->nMines));
	this->sf_flagsLeft.setFillColor(getSzin(Colour::Green));

	this->blankEntities();
	this->initMines();
	this->colourNumbers();
}

// creating the entities/minefield
// we only do this once
void Game::initEntities() {
	entities.clear();

	for(int i = 0; i < nRows; i ++) {
		for(int j = 0; j < nCols; j ++) {
			entities.push_back(Entity(nStdWidth, nStdWidth, j * nStdWidth, i * nStdWidth + nOffsetY, Colour::BrightGrey, sf_font));
		}
	}
}

// reset the minefield
// i was getting core dump errors when i was deleting the whole shebang
// and creating a new field's worth of entities so...
void Game::blankEntities() {
	for(unsigned int i = 0; i < entities.size(); i ++) {
		entities[i].reset();
	}
}

void Game::initMines() {
	std::vector<int> clearEntities;
	clearEntities.clear();

	// we want to mine the field without a while loop
	// so we create an array of the indexes of the non-mine entities (which, at this point, is all of them)
	// when we create a mine from one of these, we simply pop() that index
	for(unsigned int i = 0; i < entities.size(); i ++) {
		clearEntities.push_back(i);
	}

	for(int i = 0; i < nMines; i ++) {
		int r = rand() % clearEntities.size();
		int newMineIndex = clearEntities[r];
		clearEntities.erase(clearEntities.begin() + r);


		// making the field a mine
		entities[newMineIndex].setIsMine(true);

		bool bNorthNeighbour = false;
		bool bSouthNeighbour = false;
		bool bWestNeighbour  = false;
		bool bEastNeighbour  = false;

		// increasing the mine counters of the fields around this field

		// has northern neighbour aka not in first row
		if (newMineIndex - nCols >= 0) {
			bNorthNeighbour = true;
			entities[newMineIndex - nCols].increaseMinesAround();
		}

		// has southern neighbour aka not in last row
		if ((unsigned int)(newMineIndex + nCols) < entities.size()) { 
			bSouthNeighbour = true;
			entities[newMineIndex + nCols].increaseMinesAround();
		}

		// has western neighbour
		if (newMineIndex % nCols > 0) {
			bWestNeighbour = true;
			entities[newMineIndex - 1].increaseMinesAround();
		}

		// has eastern neighbour
		if (newMineIndex % nCols < nCols - 1) {
			bEastNeighbour = true;
			entities[newMineIndex + 1].increaseMinesAround();
		}


		if(bNorthNeighbour && bWestNeighbour)
			entities[newMineIndex - nCols - 1].increaseMinesAround();

		if(bNorthNeighbour && bEastNeighbour)
			entities[newMineIndex - nCols + 1].increaseMinesAround();

		if(bSouthNeighbour && bWestNeighbour)
			entities[newMineIndex + nCols - 1].increaseMinesAround();

		if(bSouthNeighbour && bEastNeighbour)
			entities[newMineIndex + nCols + 1].increaseMinesAround();

	}
}

// setting the colours for the numbers
void Game::colourNumbers() {
	for(unsigned int i = 0; i < entities.size(); i ++) {
		switch(entities[i].getMinesAround()) {
			case 1:
				entities[i].setNumberColour(Colour::BrightRed);
				break;
			case 2:
				entities[i].setNumberColour(Colour::PastelBlue);
				break;
			case 3:
				entities[i].setNumberColour(Colour::Yellow);
				break;
			case 4:
				entities[i].setNumberColour(Colour::BrightGrey);
				break;
			case 5:
				entities[i].setNumberColour(Colour::DarkGreen);
				break;
			case 6:
				entities[i].setNumberColour(Colour::Orange);
				break;
			case 7:
				entities[i].setNumberColour(Colour::Purple);
				break;
			case 8:
				entities[i].setNumberColour(Colour::White);
				break;
			default:
				break;
		}
	}
}

// recursive function to reveal the field and all zero fields around
// might work with only four directions but i like it like this right now
void Game::revealEntitiesAround(int pos) {
	if(!entities[pos].isMine()) {
		if(!entities[pos].isRevealed()) {
			entities[pos].revealEntity();

			if(!entities[pos].isMine() && entities[pos].getMinesAround() == 0) {
				bool bCanRevealNorth = false;
				bool bCanRevealSouth = false;
				bool bCanRevealWest = false;
				bool bCanRevealEast = false;

				if(pos - nCols >= 0) {
					bCanRevealNorth = true;
					revealEntitiesAround(pos - nCols);
				}
				
				if((unsigned int)(pos + nCols) < entities.size() - 1) {
					bCanRevealSouth = true;
					revealEntitiesAround(pos + nCols);
				}
				
				if(pos % nCols > 0) {
					bCanRevealWest = true;
					revealEntitiesAround(pos - 1);
				}
				
				if(pos % nCols < nCols - 1) {
					bCanRevealEast = true;
					revealEntitiesAround(pos + 1);
				}

				if(bCanRevealNorth && bCanRevealWest)
					revealEntitiesAround(pos - nCols - 1);

				if(bCanRevealNorth && bCanRevealEast)
					revealEntitiesAround(pos - nCols + 1);

				if(bCanRevealSouth && bCanRevealWest)
					revealEntitiesAround(pos + nCols - 1);

				if(bCanRevealSouth && bCanRevealEast)
					revealEntitiesAround(pos + nCols + 1);
			}
		}
	}
}

// checking if we flagged all the existing mines
// used to see if we won the game
bool Game::allMinesFlagged() {
	for(unsigned int i = 0; i < entities.size(); i ++) {
		if(entities[i].isMine()) {
			if(entities[i].isFlagged())
				continue;
			else
				return false;
		}
	}

	return true;
}

// main loop ----------------------------------------
void Game::mainLoop() {
	sf::RenderWindow window(sf::VideoMode(nWindowWidth, nWindowHeight + nOffsetY), "Minesweeper");
	bool bLeftMouseClicked = false;
	bool bRightMouseClicked = false;
	int nRowClicked = -1;
	int nColClicked = -1;
	int clicked;

	bool bGameOver = allMinesFlagged();
	int nFlags = this->nMines;

	window.setFramerateLimit(60);
	sf_flagsLeft.setString("Flags: " + intToString(nFlags));

    while (window.isOpen()) {
        sf::Event event;
        bLeftMouseClicked = false;
        bRightMouseClicked = false;
        nRowClicked = -1;
        nColClicked = -1;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                    bLeftMouseClicked = true;
                if (event.mouseButton.button == sf::Mouse::Right)
                	bRightMouseClicked = true;

                nRowClicked = (static_cast<int>(event.mouseButton.y) - nOffsetY) / nStdWidth;
        		nColClicked = static_cast<int>(event.mouseButton.x) / nStdWidth;
        		clicked = nRowClicked * nCols + nColClicked;
            }
        }

        if(!bGameOver) {
        	bGameOver = allMinesFlagged();

        	// revealing fields
	        if (bLeftMouseClicked) {
	        	if(!entities[clicked].isMine())
	        		revealEntitiesAround(clicked);
	        	else {
	        		entities[clicked].revealEntity();
	        		bGameOver = true;

	        		sf_flagsLeft.setFillColor(getSzin(Colour::Red));
	        		sf_flagsLeft.setString("You lose!");
	        	}
	        }

	        // setting / taking a flag
	        if (bRightMouseClicked) {
	        	// we can't flag revealed fields
	        	if(!entities[clicked].isRevealed()) {
		        	if(entities[clicked].isFlagged()) {
		        		nFlags ++;
		        		entities[clicked].takeFlag();
		        	}
		        	else if (nFlags > 0) {
		        		nFlags --;
		        		entities[clicked].setFlag();
		        	}

		        	sf_flagsLeft.setString("Flags: " + intToString(nFlags));
	        	}
	        }
    	}
    	else {
			if(allMinesFlagged())
				sf_flagsLeft.setString("You win!");

			// check if player wants another game
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
				this->reInit();
				bGameOver = false;
				nFlags = this->nMines;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
				window.close();
			}
    	}

        window.clear();

        window.draw(sf_flagsLeft);

        if(bGameOver)
        	window.draw(sf_endGameMsg);

        for(unsigned int i = 0; i < entities.size(); i ++)
			entities[i].drawEntity(window);

        window.display();
    }
}