#include "Square.h"

std::ostream& operator<<(std::ostream& os, const Square& sq)
{
	char kind;
	switch (sq.getPiece().getKind())
	{
	case PieceKind::PAWN:
		kind = 'P';
		break;
	case PieceKind::ROOK:
		kind = 'R';
		break;
	case PieceKind::KNIGHT:
		kind = 'N';
		break;
	case PieceKind::BISHOP:
		kind = 'B';
		break;
	case PieceKind::QUEEN:
		kind = 'Q';
		break;
	case PieceKind::KING:
		kind = 'K';
		break;
	default:
		kind = '-';
	}

	if (sq.getPiece().getColor() == PieceColor::BLACK && kind != '-')
		kind = tolower(kind);

	os << kind;
	return os;
}
