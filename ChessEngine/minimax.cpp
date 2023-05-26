#include "minimax.h"

double minimax_serial(Game& game, int depth, double alpha, double beta)
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

	if (depth == 0)
		return game.evaluate();

	if (turn == PieceColor::WHITE) // maximizer
	{
		double maxEval = -1000.0;
		for (auto move : moves)
		{
			Game newGame(game);
			newGame.setTurn(game.getOpposingColor(turn));
			newGame.makeMove(move[0], move[1]);
			double eval = minimax_serial(newGame, depth - 1, alpha, beta);
			if (eval > maxEval)
			{
				maxEval = eval;
			}
			alpha = alpha > eval ? alpha : eval;
			if (beta <= alpha) break;
		}
		return maxEval;
	}
	else // minimizer
	{
		double minEval = 1000.0;
		for (auto move : moves)
		{
			Game newGame(game);
			newGame.setTurn(game.getOpposingColor(turn));
			newGame.makeMove(move[0], move[1]);
			double eval = minimax_serial(newGame, depth - 1, alpha, beta);
			if (eval < minEval)
			{
				minEval = eval;
			}
			beta = beta < eval ? beta : eval;
			if (beta <= alpha) break;
		}
		return minEval;
	}
}

double minimax_parallel(Game& game, int depth, int cutoff, double alpha, double beta)
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

	if (depth == 0)
	{
		return game.evaluate();
	}

	if (cutoff < 1)
	{
		return minimax_serial(game, depth, alpha, beta);
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
		tasks.run([&, i] {evaluations[i] = minimax_parallel(games[i], depth - 1, cutoff - 1, alpha, beta); });
	}
	tasks.wait();

	if (turn == PieceColor::WHITE)
	{
		double maxEval = -1000.0;
		for (const auto& eval : evaluations)
		{
			if (eval > maxEval)
			{
				maxEval = eval;
			}
		}

		return maxEval;
	}
	else
	{
		double minEval = 1000.0;
		for (const auto& eval : evaluations)
		{
			if (eval < minEval)
			{
				minEval = eval;
			}
		}

		return minEval;
	}
}