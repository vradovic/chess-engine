#include <iostream>
#include "Game.h"
#include "minimax.h"
#include "tbb/tick_count.h"

int main()
{
	auto game = Game();
	auto fen = "2r3k1/4p1bp/1pr1p1P1/p7/1qb2B2/6N1/1P3RPP/3QR2K b - - 0 29";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		std::vector<Position> bestMove = { Position{-1,-1}, Position{-1,-1} };

		tbb::tick_count startTime = tbb::tick_count::now();
		//double eval = minimax_serial(game, 3, bestMove);
		double eval = minimax_parallel(game, 3, 3, bestMove);
		tbb::tick_count endTime = tbb::tick_count::now();

		std::cout << "Evaluation: " << eval << "\n";
		std::cout << "Best move: " << bestMove[0] << " " << bestMove[1] << "\n";
		std::cout << "Time elapsed: " << (endTime - startTime).seconds() << "s\n";
	}
	else std::cout << "Parsing failed\n";
}