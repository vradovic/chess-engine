#include <iostream>
#include "Game.h"
#include "minimax.h"

int main()
{
	auto game = Game();
	auto fen = "2rq1r1k/3b1pb1/3p2P1/pp1n4/3pP1p1/PB3P2/1PPQ4/2KR4 w - - 0 20";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		std::vector<Position> bestMove = { Position{-1,-1}, Position{-1,-1} };
		double eval = minimax(game, 4, -1000.0, 1000.0, bestMove);
		std::cout << "Evaluation: " << eval << "\n";
		std::cout << "Best move: " << bestMove[0] << " " << bestMove[1] << "\n";
	}
	else std::cout << "Parsing failed\n";
}