#if !defined(MINESWEEPER_SOLVER_H)
#define MINESWEEPER_SOLVER_H
#include "minesweeperGame.h"
#include <cstdint>
#include <map>
#include <set>

namespace minesweeperSolver
{
  using clickSuggestions = std::map<std::pair<int, int>, char>;

  clickSuggestions getRightClicksSuggestionsBasedOnState( minesweeperGame::ms_game, minesweeperGame::cellStateEnum );
  clickSuggestions getRightClickSuggestions( minesweeperGame::ms_game );

  clickSuggestions getLeftClicksSuggestionsBasedOnState( minesweeperGame::ms_game, minesweeperGame::cellStateEnum );
  clickSuggestions getLeftClickSuggestions( minesweeperGame::ms_game );

  clickSuggestions getLeftClickGambleSuggestions( minesweeperGame::ms_game );

}  // namespace minesweeperSolver

#endif // MINESWEEPER_SOLVER_H