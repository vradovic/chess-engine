#pragma once

#include <iostream>

struct Position
{
	int rank;
	int file;

	friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};