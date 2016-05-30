This will be a solver library for zero-sum two-player games.

The solving algorithm is divided into 2 stages. The first stage is a game tree search with the minimax algorithm with alpha-beta pruning. The search depth can be specified.

The second stage is entered after the game tree has been searched to the specified depth and the game is still not over. The secong stage is a faster and probably less precise way of evaluating the game state. It can be implemented by a heuristic evaluation function or the Monte Carlo method.

The library is intended to be independent of the game the solving of which it is used for.
