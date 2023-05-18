#include <iostream>
#include "Game.h"

int main()
{
	auto game = Game();
	auto fen = "8/6b1/4p2r/2k2K2/8/3B4/8/1q6 w - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		/*auto squares = game.getValidSquares(Position{ 3, 2 });
		for (auto square : squares)
			std::cout << square << "\n";*/
		//std::cout << game.getKing(PieceColor::BLACK);
		if (game.isCheck(PieceColor::WHITE))
			std::cout << "Check!\n";
		else
			std::cout << "Not check\n";
	}
	else std::cout << "Parsing failed\n";
}