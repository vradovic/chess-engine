#include "Game.h"

void Game::reset()
{
	castlingRights.clear();
	enPassantPos = nullptr;
	halfMoves = 0;
	fullMoves = 0;

	for (size_t rank = 0; rank < 8; rank++)
	{
		for (size_t file = 0; file < 8; file++)
		{
			board[rank][file] = Square();
		}
	}
}

void Game::setPiece(const fenparserpp::BoardPos& bpos, fenparserpp::Piece piece, fenparserpp::PieceColor pieceColor)
{
	int rank = bpos.getRank();
	int file = bpos.getFile();

	PieceColor pc;
	if (pieceColor == fenparserpp::PieceColor::WHITE)
		pc = PieceColor::WHITE;
	else
		pc = PieceColor::BLACK;

	// TODO: different pieces

	board[rank][file].setPiece(new Piece(pc));
	board[rank][file].setIsOccupied(true);
}

void Game::setCastleRight(fenparserpp::CastleRight right)
{
	CastleRight cr;

	switch (right)
	{
	case fenparserpp::CastleRight::BLACK_KINGSIDE_CASTLE:
		cr = CastleRight::BLACK_KINGSIDE_CASTLE;
		break;
	case fenparserpp::CastleRight::BLACK_QUEENSIDE_CASTLE:
		cr = CastleRight::BLACK_QUEENSIDE_CASTLE;
		break;
	case fenparserpp::CastleRight::WHITE_KINGSIDE_CASTLE:
		cr = CastleRight::WHITE_KINGSIDE_CASTLE;
		break;
	case fenparserpp::CastleRight::WHITE_QUEENSIDE_CASTLE:
		cr = CastleRight::WHITE_QUEENSIDE_CASTLE;
		break;
	}

	castlingRights.insert(cr);
}

void Game::setEnPassantPos(const fenparserpp::BoardPos& bpos)
{
	int rank = bpos.getRank();
	int file = bpos.getFile();

	enPassantPos = &board[rank][file];
}

void Game::setHalfMoves(int hmoves)
{
	halfMoves = hmoves;
}

void Game::setFullMoves(int fmoves)
{
	fullMoves = fmoves;
}

void Game::setToPlay(fenparserpp::PieceColor color)
{
	if (color == fenparserpp::PieceColor::BLACK)
		toPlay = PieceColor::BLACK;
	else
		toPlay = PieceColor::WHITE;
}

Game::Game()
{
	reset();
}
