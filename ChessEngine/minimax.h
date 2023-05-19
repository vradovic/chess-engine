#pragma once

#include "Game.h"

// White is maximizer, black is minimizer
double minimax(Game& game, int depth, double alpha, double beta);