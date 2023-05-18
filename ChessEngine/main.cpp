#include <iostream>
#include "Game.h"

int main()
{
	auto game = Game();
	auto fen = "8/8/2n5/8/2R2Q2/8/8/8 w - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		auto squares = game.getValidSquares(Position{ 3, 2 });
		for (auto square : squares)
			std::cout << square << "\n";
	}
	else std::cout << "Parsing failed\n";
}