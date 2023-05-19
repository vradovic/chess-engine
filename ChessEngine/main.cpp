#include <iostream>
#include "Game.h"
#include "minimax.h"

int main()
{
	auto game = Game();
	auto fen = "8/3Nb2p/p7/1k2p1p1/4P3/5P2/2K5/8 b - - 1 37";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		double eval = minimax(game, 5, -1000.0, 1000.0);
		std::cout << eval << "\n";
	}
	else std::cout << "Parsing failed\n";
}