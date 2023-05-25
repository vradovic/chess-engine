#include "Position.h"

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
	int rank = pos.rank + 1;
	int file = pos.file + 'a';
	char fileChar = file;
	os << fileChar << rank;
	return os;
}
