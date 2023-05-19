#include <iostream>
#include "Game.h"

int main()
{
	auto game = Game();
	auto fen = "r6k/5ppp/8/8/8/8/5PPP/3Q2K1 w - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		std::cout << game.evaluate();
		
	}
	else std::cout << "Parsing failed\n";
}