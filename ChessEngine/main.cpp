#include <iostream>
#include "Game.h"

int main()
{
	auto game = Game();
	auto fen = "8/8/8/B7/2N5/4r3/8/8 w - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		auto squares = game.getValidSquares(Position{ 3, 2 });
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