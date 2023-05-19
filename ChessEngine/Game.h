#pragma once

#include "fenparserpp.h"
#include "CastleRight.h"
#include "Position.h"
#include "Piece.h"

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
	void putPiece(Position pos, Piece pc);
	void printBoard() const;
	bool isInsideBoard(Position pos) const;
	bool containsPiece(Position pos) const;
	bool containsPiece(Position pos, const Piece& pc) const;
	bool containsEnemyPiece(Position pos, PieceColor color) const;
	bool containsOwnPiece(Position pos, PieceColor color) const;
	Position getKing(PieceColor color) const;
	std::vector<Position> getValidSquares(Position pos) const;
	bool isCheck(PieceColor color) const;
	bool checkDiagonalThreat(Position pos, PieceColor color) const;
	bool checkOrthogonalThreat(Position pos, PieceColor color) const;
	bool checkKnightThreat(Position pos, PieceColor color) const;
	bool checkPawnThreat(Position pos, PieceColor color) const;
	PieceColor getOpposingColor(PieceColor color) const;
	bool isValidMove(Position source, Position target);
	double evaluate() const;
	double evaluateColor(PieceColor color) const;

private:
	Piece board[8][8];
	int halfMoves;
	int fullMoves;
	PieceColor toPlay;
	Position enPassantPos;
	std::unordered_set<CastleRight> castlingRights;
};