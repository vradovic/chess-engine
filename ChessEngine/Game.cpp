#include "Game.h"

void Game::reset()
{
	castlingRights.clear();
	enPassantPos = Position{ -1,-1 };
	halfMoves = 0;
	fullMoves = 0;

	for (size_t rank = 0; rank < 8; rank++)
	{
		for (size_t file = 0; file < 8; file++)
		{
			board[rank][file] = Piece();
		}
	}
}

void Game::setPiece(const fenparserpp::BoardPos& bpos, fenparserpp::Piece piece, fenparserpp::PieceColor pieceColor)
{
	Position pos = { bpos.getRank(), bpos.getFile() };

	PieceColor pc;
	if (pieceColor == fenparserpp::PieceColor::WHITE)
		pc = PieceColor::WHITE;
	else
		pc = PieceColor::BLACK;

	switch (piece)
	{
	case fenparserpp::Piece::BISHOP:
		putPiece(pos, Piece(PieceKind::BISHOP, pc));
		break;
	case fenparserpp::Piece::KING:
		putPiece(pos, Piece(PieceKind::KING, pc));
		break;
	case fenparserpp::Piece::KNIGHT:
		putPiece(pos, Piece(PieceKind::KNIGHT, pc));
		break;
	case fenparserpp::Piece::PAWN:
		putPiece(pos, Piece(PieceKind::PAWN, pc));
		break;
	case fenparserpp::Piece::QUEEN:
		putPiece(pos, Piece(PieceKind::QUEEN, pc));
		break;
	case fenparserpp::Piece::ROOK:
		putPiece(pos, Piece(PieceKind::ROOK, pc));
		break;
	default:
		putPiece(pos, Piece(PieceKind::NONE, pc));
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
	enPassantPos = Position{ bpos.getRank(), bpos.getFile() };
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

void Game::putPiece(Position pos, Piece pc)
{
	board[pos.rank][pos.file] = pc;
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
