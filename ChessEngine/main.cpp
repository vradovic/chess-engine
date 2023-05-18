#include <iostream>
#include "Game.h"

int main()
{
	auto game = Game();
	auto fen = "4r1k1/8/8/4Q3/8/4K3/8/8 w - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		/*auto squares = game.getValidSquares(Position{ 2, 4 });
		for (auto square : squares)
			std::cout << square << "\n";*/
		//std::cout << game.getKing(PieceColor::BLACK);
		/*if (game.isCheck(PieceColor::BLACK))
			std::cout << "Check!\n";
		else
			std::cout << "Not check\n";*/
		if (game.isValidMove(Position{ 4,4 }, Position{ 4,6 })) std::cout << "valid\n";
	}
	else std::cout << "Parsing failed\n";
}