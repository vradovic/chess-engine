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

	switch (piece)
	{
	case fenparserpp::Piece::BISHOP:
		board[rank][file].setPiece(Piece(PieceKind::BISHOP, pc));
		board[rank][file].setOccupied(true);
		break;
	case fenparserpp::Piece::KING:
		board[rank][file].setPiece(Piece(PieceKind::KING, pc));
		board[rank][file].setOccupied(true);
		break;
	case fenparserpp::Piece::KNIGHT:
		board[rank][file].setPiece(Piece(PieceKind::KNIGHT, pc));
		board[rank][file].setOccupied(true);
		break;
	case fenparserpp::Piece::PAWN:
		board[rank][file].setPiece(Piece(PieceKind::PAWN, pc));
		board[rank][file].setOccupied(true);
		break;
	case fenparserpp::Piece::QUEEN:
		board[rank][file].setPiece(Piece(PieceKind::QUEEN, pc));
		board[rank][file].setOccupied(true);
		break;
	case fenparserpp::Piece::ROOK:
		board[rank][file].setPiece(Piece(PieceKind::ROOK, pc));
		board[rank][file].setOccupied(true);
		break;
	default:
		board[rank][file].setPiece(Piece(PieceKind::NONE, pc));
		board[rank][file].setOccupied(false);
		break;
	}

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

void Game::printBoard() const
{
	for (int i = 7; i > -1; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << board[i][j] << " ";
		}
		std::cout << "\n";
	}
}
