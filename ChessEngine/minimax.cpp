#include "minimax.h"

double minimax(Game& game, int depth, double alpha, double beta)
{
	PieceColor turn = game.getTurn();
	std::vector<std::vector<Position>> moves = game.getPlayerValidMoves(turn);

	if (depth == 0 || moves.empty())
		return game.evaluate();

	if (turn == PieceColor::WHITE) // maximizer
	{
		double maxEval = -1000.0;
		for (auto move : moves)
		{
			Game newGame(game);
			newGame.setTurn(game.getOpposingColor(turn));
			newGame.makeMove(move[0], move[1]);
			double eval = minimax(newGame, depth - 1, alpha, beta);
			maxEval = eval > maxEval ? eval : maxEval;
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
			double eval = minimax(newGame, depth - 1, alpha, beta);
			minEval = eval < minEval ? eval : minEval;
			beta = beta < eval ? beta : eval;
			if (beta <= alpha) break;
		}
		return minEval;
	}
}
