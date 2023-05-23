#include <iostream>
#include "Game.h"
#include "minimax.h"

int main()
{
	auto game = Game();
	auto fen = "8/3k4/8/p7/5R1K/8/8/8 w - - 0 1";

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