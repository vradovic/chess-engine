#include "Position.h"
#include <string>

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
	int rank = pos.rank + 1;
	int file = pos.file + 'a';
	char fileChar = file;
	os << fileChar << rank;
	return os;
}


std::string Position::to_string() const {
	int rankValue = rank + 1;
	int fileValue = file + 'a';
	char fileChar = fileValue;
	return std::string(1, fileChar) + std::to_string(rankValue);
}