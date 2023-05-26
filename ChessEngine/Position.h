#pragma once

#include <iostream>

struct Position
{
	int rank;
	int file;

	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};