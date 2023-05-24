#include "minimax.h"

double minimax(Game& game, int depth, double alpha, double beta, std::vector<Position>& bestMove)
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
			std::vector<Position> nextBestMove = { Position{-1,-1},Position{-1,-1} };
			newGame.setTurn(game.getOpposingColor(turn));
			newGame.makeMove(move[0], move[1]);
			double eval = minimax(newGame, depth - 1, alpha, beta, nextBestMove);
			if (eval > maxEval)
			{
				maxEval = eval;
				bestMove = { move[0], move[1] };
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
			std::vector<Position> nextBestMove = { Position{-1,-1},Position{-1,-1} };
			newGame.setTurn(game.getOpposingColor(turn));
			newGame.makeMove(move[0], move[1]);
			double eval = minimax(newGame, depth - 1, alpha, beta, nextBestMove);
			if (eval < minEval)
			{
				minEval = eval;
				bestMove = { move[0], move[1] };
			}
			beta = beta < eval ? beta : eval;
			if (beta <= alpha) break;
		}
		return minEval;
	}
}
