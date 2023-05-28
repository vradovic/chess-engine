#include "minimax.h"

double minimax_serial(Game& game, int depth, std::vector<Position>& bestMove)
{
	PieceColor turn = game.getTurn();
	std::vector<std::vector<Position>> moves = game.getPlayerValidMoves(turn);

	if (moves.empty()) // checkmate
	{
		if (turn == PieceColor::WHITE)
		{
			return -100.0;
		}
		else
		{
			return 100.0;
		}
	}

	if (depth <= 0)
		return game.evaluate();

	if (turn == PieceColor::WHITE) // maximizer
	{
		double maxEval = -1000.0;
		for (auto move : moves)
		{
			Game newGame(game);
			std::vector<Position> nextBestMove = { Position{-1,-1},Position{-1,-1} };
			newGame.setTurn(game.getOpposingColor(turn));
			newGame.makeMove(move[0], move[1]);
			double eval = minimax_serial(newGame, depth - 1, nextBestMove);
			if (eval > maxEval)
			{
				maxEval = eval;
				bestMove = { move[0], move[1] };
			}
		}
		return maxEval;
	}
	else // minimizer
	{
		double minEval = 1000.0;
		for (auto move : moves)
		{
			Game newGame(game);
			std::vector<Position> nextBestMove = { Position{-1,-1},Position{-1,-1} };
			newGame.setTurn(game.getOpposingColor(turn));
			newGame.makeMove(move[0], move[1]);
			double eval = minimax_serial(newGame, depth - 1, nextBestMove);
			if (eval < minEval)
			{
				minEval = eval;
				bestMove = { move[0], move[1] };
			}
		}
		return minEval;
	}
}

double minimax_parallel(Game& game, int depth, int cutoff, std::vector<Position>& bestMove)
{
	PieceColor turn = game.getTurn();
	std::vector<std::vector<Position>> moves = game.getPlayerValidMoves(turn);
	std::vector<Position> nextBestMove = { Position{-1,-1},Position{-1,-1} };

	if (moves.empty()) // checkmate
	{
		if (turn == PieceColor::WHITE)
		{
			return -100.0;
		}
		else
		{
			return 100.0;
		}
	}

	if (depth <= 0)
	{
		return game.evaluate();
	}

	if (cutoff < 1)
	{
		return minimax_serial(game, depth, nextBestMove);
	}

	std::vector<Game> games;

	for (const auto& move : moves)
	{
		Game newGame(game);
		newGame.makeMove(move[0], move[1]);
		newGame.setTurn(game.getOpposingColor(turn));
		games.push_back(newGame);
	}

	std::vector<double> evaluations(moves.size(), 0.0);
	tbb::task_group tasks;

	for (int i = 0; i < games.size(); i++)
	{
		tasks.run([&, i] {evaluations[i] = minimax_parallel(games[i], depth - 1, cutoff - 1, nextBestMove); });
	}
	tasks.wait();

	if (turn == PieceColor::WHITE)
	{
		double maxEval = -1000.0;
		for (int i = 0; i < moves.size(); i++)
		{
			if (evaluations[i] > maxEval)
			{
				maxEval = evaluations[i];
				bestMove = { moves[i][0], moves[i][1] };
			}
		}

		return maxEval;
	}
	else
	{
		double minEval = 1000.0;
		for (int i = 0; i < moves.size(); i++)
		{
			if (evaluations[i] < minEval)
			{
				minEval = evaluations[i];
				bestMove = { moves[i][0], moves[i][1] };
			}
		}

		return minEval;
	}
}