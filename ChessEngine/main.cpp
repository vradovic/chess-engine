#include <iostream>
#include "Game.h"
#include "minimax.h"
#include "tbb/tick_count.h"
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		std::cerr << "chessengine: missing arguments\n";
		std::cerr << "usage: chessengine <input_file> <output_file> <depth> <cutoff>" << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1]);

	if (!inputFile.is_open()) {
		std::cerr << "chessengine: failed to open input file" << std::endl;
		return 1;
	}

	std::ofstream outputFile(argv[2]);

	if (!outputFile.is_open()) {
		std::cerr << "chessengine: failed to open output file" << std::endl;
		return 1;
	}

	int depth = 0, cutoff = 0;

	try
	{
		depth = std::stoi(argv[3]);
		cutoff = std::stoi(argv[4]);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "chessengine: depth or cutoff not integers: " << e.what() << std::endl;
		return 1;
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "chessengine: depth or cutoff out of range: " << e.what() << std::endl;
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
			std::vector<Position> serialBestMove = { Position{-1,-1}, Position{-1,-1} };
			std::vector<Position> parallelBestMove = { Position{-1,-1}, Position{-1,-1} };

			std::cout << "Calculating Serial...\n";
			tbb::tick_count startTime = tbb::tick_count::now();
			double eval = minimax_serial(game, depth, serialBestMove);			
			tbb::tick_count endTime = tbb::tick_count::now();

			std::string output = "Serial verson: \nEvaluation: " + std::to_string(eval) + "\nBest move: " + (serialBestMove[0].to_string()) + " " + (serialBestMove[1].to_string()) +
				"\nTime elapsed: " + std::to_string((endTime - startTime).seconds()) + "s\n";

			std::cout << output;
			outputFile << output << std::endl;

			std::cout << "Calculating Parallel...\n";
			startTime = tbb::tick_count::now();
			eval = minimax_parallel(game, depth, cutoff, parallelBestMove);
			endTime = tbb::tick_count::now();
			
			output = "Parallel verson: \nEvaluation: " + std::to_string(eval) + "\nBest move: " + (parallelBestMove[0].to_string()) + " " + (parallelBestMove[1].to_string()) +
				"\nTime elapsed: " + std::to_string((endTime - startTime).seconds()) + "s\n";

			std::cout << output << std::endl;
			outputFile << output << std::endl;

			if (serialBestMove[0].rank == parallelBestMove[0].rank &&
				serialBestMove[0].file == parallelBestMove[0].file &&
				serialBestMove[1].rank == parallelBestMove[1].rank &&
				serialBestMove[1].file == parallelBestMove[1].file)
			{
				std::cout << "Found the same moves.\n";
			}
			else
			{
				std::cout << "The moves are not the same!\n";
			}

			game.printBoardGUI(parallelBestMove);

		}
		else std::cout << "Parsing failed for FEN: " << line << "\n";
	}

	inputFile.close();
	outputFile.close();
	
}