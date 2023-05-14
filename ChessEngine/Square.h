#pragma once

#include "Piece.h"

class Square
{
public:
	Square() : piece(nullptr), isOccupied(false) {}
	void setPiece(Piece* piece);
	void setIsOccupied(bool isOccupied);

private:
	Piece* piece;
	bool isOccupied;
};