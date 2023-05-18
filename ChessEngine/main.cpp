#include <iostream>
#include "Game.h"

int main()
{
	auto game = Game();
	auto fen = "8/8/8/8/5r2/3npN2/3P1r2/8 w - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		auto squares = game.getValidSquares(Position{ 2, 4 });
		for (auto square : squares)
			std::cout << square << "\n";
		//std::cout << game.getKing(PieceColor::BLACK);
		/*if (game.isCheck(PieceColor::BLACK))
			std::cout << "Check!\n";
		else
			std::cout << "Not check\n";*/
	}
	else std::cout << "Parsing failed\n";
}