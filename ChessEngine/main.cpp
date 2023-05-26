#include <iostream>
#include "Game.h"
#include "minimax.h"
#include "tbb/tick_count.h"
#include <fstream>

int main(int argc, char* argv[])
{
	std::ifstream inputFile(argv[1]);

	if (!inputFile.is_open()) {
		std::cout << "Failed to open the file." << std::endl;
		return 1;
	}

	std::ofstream outputFile(argv[2]);

	if (!outputFile.is_open()) {
		std::cout << "Failed to open the file." << std::endl;
		return 1;
	}

	std::string line;
	while (std::getline(inputFile, line)) {
		auto game = Game();
		
		auto parser = fenparserpp::FENParser();
		bool success = parser.parse(line, game);

		if (success)
		{
			outputFile << "Fen: " << line << std::endl;
			std::vector<Position> bestMove = { Position{-1,-1}, Position{-1,-1} };

			std::cout << "Calculating Serial...\n";
			tbb::tick_count startTime = tbb::tick_count::now();
			double eval = minimax_serial(game, 3, bestMove);			
			tbb::tick_count endTime = tbb::tick_count::now();

			std::string output = "Serial verson: \nEvaluation: " + std::to_string(eval) + "\nBest move: " + (bestMove[0].to_string()) + " " + (bestMove[1].to_string()) +
				"\nTime elapsed: " + std::to_string((endTime - startTime).seconds()) + "s\n";

			std::cout << output;
			outputFile << output << std::endl;

			std::cout << "Calculating Parallel...\n";
			startTime = tbb::tick_count::now();
			eval = minimax_parallel(game, 3, 3, bestMove);
			endTime = tbb::tick_count::now();
			
			output = "Parallel verson: \nEvaluation: " + std::to_string(eval) + "\nBest move: " + (bestMove[0].to_string()) + " " + (bestMove[1].to_string()) +
				"\nTime elapsed: " + std::to_string((endTime - startTime).seconds()) + "s\n";

			std::cout << output << std::endl;
			outputFile << output << std::endl;

			game.printBoardGUI(bestMove);

		}
		else std::cout << "Parsing failed\n";
	}

	inputFile.close();
	outputFile.close();
	
}