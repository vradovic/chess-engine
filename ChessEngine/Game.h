#pragma once

#include "fenparserpp.h"
#include "Square.h"
#include "CastleRight.h"

class Game : public fenparserpp::BoardListener
{
public:
	// FEN parser methods
	void reset();
	void setPiece(const fenparserpp::BoardPos& bpos, fenparserpp::Piece piece, fenparserpp::PieceColor pieceColor);
	void setCastleRight(fenparserpp::CastleRight right);
	void setEnPassantPos(const fenparserpp::BoardPos& bpos);
	void setHalfMoves(int hmoves);
	void setFullMoves(int fmoves);
	void setToPlay(fenparserpp::PieceColor color);

	Game();
	void printBoard() const;

private:
	Square board[8][8];
	int halfMoves;
	int fullMoves;
	PieceColor toPlay;
	Square* enPassantPos;
	std::unordered_set<CastleRight> castlingRights;
};