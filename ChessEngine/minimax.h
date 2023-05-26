#pragma once

#include "Game.h"

// White is maximizer, black is minimizer
double minimax_serial(Game& game, int depth, std::vector<Position>& bestMove);
double minimax_parallel(Game& game, int depth, int cutoff, std::vector<Position>& bestMove);