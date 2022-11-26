#include "Entity.h"
#include "Colours.h"
#include "helper_functions.h"
#include <iostream>

Entity::Entity(int _width, int _height, int _x, int _y, Colour _colour, sf::Font &_font) : nWidth(_width), nHeight(_height), sf_colour(_colour) {
	this->bRevealed = false;
	this->bFlagged = false;
	this->nMinesAround = 0;

	this->sf_rect.setSize(sf::Vector2f(nWidth, nWidth));
	this->sf_rect.setPosition(_x, _y);
	this->sf_rect.setFillColor(getSzin(_colour));
	this->sf_rect.setOutlineColor(getSzin(Colour::Black));
	this->sf_rect.setOutlineThickness(1.f);

	this->sf_mineNumber.setFont(_font);
	this->sf_mineNumber.setString(" ");
	this->sf_mineNumber.setPosition(_x + 6, _y - 3);
	this->sf_mineNumber.setCharacterSize(24);
	this->sf_mineNumber.setFillColor(getSzin(Colour::White));
}

void Entity::setIsMine(bool _isMine) {
	this->bIsMine = _isMine;
}

bool Entity::isMine() {
	return this->bIsMine;
}

int Entity::getMinesAround() {
	return this->nMinesAround;
}

void Entity::setFlag() {
	this->bFlagged = true;
	this->sf_rect.setFillColor(getSzin(Colour::DarkGreen));
}

void Entity::takeFlag() {
	this->bFlagged = false;
	this->sf_rect.setFillColor(getSzin(this->sf_colour));
}

bool Entity::isFlagged() {
	return this->bFlagged;
}

void Entity::increaseMinesAround() {
	this->nMinesAround ++;
	this->sf_mineNumber.setString(intToString(this->nMinesAround));
}

void Entity::revealEntity() {
	this->bRevealed = true;
}

bool Entity::isRevealed() {
	return this->bRevealed;
}

sf::RectangleShape Entity::getRect() {
	return this->sf_rect;
}

void Entity::drawEntity(sf::RenderWindow &window) {
	if(!bRevealed) 
		window.draw(this->sf_rect);
	else {
		if(!bIsMine)
			window.draw(this->sf_mineNumber);
		else {
			this->sf_rect.setFillColor(getSzin(Colour::Red));
			window.draw(this->sf_rect);
		}
	}
}