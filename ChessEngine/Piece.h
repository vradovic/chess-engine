#pragma once

#include "PieceColor.h"

class Piece
{
public:
	Piece(PieceColor clr) : color(clr) {}

private:
	PieceColor color;
};