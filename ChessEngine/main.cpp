#include <iostream>
#include "Game.h"
#include "minimax.h"

int main()
{
	auto game = Game();
	auto fen = "8/7P/8/5K2/8/8/1rk5/8 w - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		double eval = minimax(game, 4, -1000.0, 1000.0);
		std::cout << eval << "\n";
	}
	else std::cout << "Parsing failed\n";
}