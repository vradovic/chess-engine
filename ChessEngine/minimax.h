#pragma once

#include "Game.h"

// White is maximizer, black is minimizer
double minimax_serial(Game& game, int depth, double alpha, double beta);
double minimax_parallel(Game& game, int depth, int cutoff, double alpha, double beta);