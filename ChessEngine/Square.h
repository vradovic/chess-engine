#pragma once

#include "Piece.h"
#include <iostream>

class Square
{
public:
	Square() : piece(Piece(PieceKind::NONE, PieceColor::WHITE)), occupied(false) {}
	Piece getPiece() const { return piece; }
	void setPiece(Piece piece) { this->piece = piece; }
	bool isOccupied() const { return occupied; }
	void setOccupied(bool occupied) { this->occupied = occupied; }
	friend std::ostream& operator<<(std::ostream& os, const Square& sq);

private:
	Piece piece;
	bool occupied;
};