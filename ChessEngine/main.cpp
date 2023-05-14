#include "fenparserpp.h"
#include <iostream>

int main()
{
	auto board = fenparserpp::SimpleBoard();
	auto fen = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, board);

	if (success)
		std::cout << "Parsing succesful\n";
	else
		std::cout << "Parsing failed\n";
}