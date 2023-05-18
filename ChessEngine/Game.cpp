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

bool Game::isInsideBoard(Position pos) const
{
	return (pos.rank >= 0 && pos.rank < 8 && pos.file >= 0 && pos.file < 8);
}

bool Game::containsPiece(Position pos) const
{
	Piece pc = board[pos.rank][pos.file];
	return pc.getKind() != PieceKind::NONE;
}

bool Game::containsEnemyPiece(Position pos, PieceColor color) const
{
	Piece pc = board[pos.rank][pos.file];
	return pc.getKind() != PieceKind::NONE && pc.getColor() != color;
}

bool Game::containsOwnPiece(Position pos, PieceColor color) const
{
	Piece pc = board[pos.rank][pos.file];
	return pc.getKind() != PieceKind::NONE && pc.getColor() == color;
}

std::vector<Position> Game::getValidSquares(Position pos) const
{
	std::vector<Position> squares;

	Piece pc = board[pos.rank][pos.file];

	std::vector<std::vector<int>> moves;

	switch (pc.getKind())
	{
	case PieceKind::ROOK:
		moves = { {1,0},{0,1},{-1,0},{0,-1} };
		
		for (auto move : moves)
		{
			Position nextPos = { pos.rank + move[0], pos.file + move[1] };
			while (isInsideBoard(nextPos))
			{
				if (containsOwnPiece(nextPos, pc.getColor())) break;
				squares.push_back(nextPos);
				if (containsEnemyPiece(nextPos, pc.getColor())) break;
				nextPos = { nextPos.rank + move[0], nextPos.file + move[1] };
			}
		}
		break;
	default:
		break;
	}

	return squares;
}
