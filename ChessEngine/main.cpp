#include <iostream>
#include "Game.h"
#include "minimax.h"
#include "tbb/tick_count.h"

int main()
{
	auto game = Game();
	auto fen = "8/4pn1p/1K5Q/r5p1/4P3/Pk2Nrn1/b7/4R2N b - - 0 1";

	auto parser = fenparserpp::FENParser();
	bool success = parser.parse(fen, game);

	if (success)
	{
		game.printBoard();
		std::vector<Position> bestMove = { Position{-1,-1}, Position{-1,-1} };

		tbb::tick_count startTime = tbb::tick_count::now();
		//double eval = minimax_serial(game, 3, bestMove);
		double eval = minimax_parallel(game, 4, 4, bestMove);
		tbb::tick_count endTime = tbb::tick_count::now();

		std::cout << "Evaluation: " << eval << "\n";
		std::cout << "Best move: " << bestMove[0] << " " << bestMove[1] << "\n";
		std::cout << "Time elapsed: " << (endTime - startTime).seconds() << "s\n";
	}
	else std::cout << "Parsing failed\n";
}