#include <iostream>
#include "Game.h"
#include "minimax.h"

int main()
{
	auto game = Game();
	auto fen = "2k5/7R/3K4/8/8/8/8/8 b - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		double eval = minimax(game, 6, -1000.0, 1000.0);
		std::cout << eval << "\n";
	}
	else std::cout << "Parsing failed\n";
}