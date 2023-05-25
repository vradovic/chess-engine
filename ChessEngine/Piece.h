#pragma once

#include "PieceColor.h"
#include "PieceKind.h"
#include <iostream>

class Piece
{
public:
	Piece() : kind(PieceKind::NONE), color(PieceColor::WHITE) {}
	Piece(PieceKind knd, PieceColor clr) : kind(knd), color(clr) {}
	PieceKind getKind() const { return kind; }
	PieceColor getColor() const { return color; }
	friend std::ostream& operator<<(std::ostream& os, const Piece& pc);

private:
	PieceKind kind;
	PieceColor color;
};