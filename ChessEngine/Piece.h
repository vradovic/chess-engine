#pragma once

#include "PieceColor.h"
#include "PieceKind.h"

class Piece
{
public:
	Piece(PieceKind knd, PieceColor clr) : kind(knd), color(clr) {}
	PieceKind getKind() const { return kind; }
	PieceColor getColor() const { return color; }

private:
	PieceKind kind;
	PieceColor color;
};