#include <iostream>
#include "Game.h"
#include "minimax.h"
#include "tbb/tick_count.h"

int main()
{
	auto game = Game();
	auto fen = "5rk1/1p6/p3p2p/1b1pPnq1/1Q4p1/1P4P1/P1r2PBP/2NRR1K1 w - - 3 25";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		std::vector<Position> bestMove = { Position{-1,-1}, Position{-1,-1} };

		tbb::tick_count startTime = tbb::tick_count::now();
		double eval = minimax(game, 4, -1000.0, 1000.0, bestMove);
		tbb::tick_count endTime = tbb::tick_count::now();

		std::cout << "Evaluation: " << eval << "\n";
		std::cout << "Best move: " << bestMove[0] << " " << bestMove[1] << "\n";
		std::cout << "Time elapsed: " << (endTime - startTime).seconds() << "s\n";
	}
	else std::cout << "Parsing failed\n";
}