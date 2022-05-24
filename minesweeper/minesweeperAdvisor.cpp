#include "minesweeperAdvisor.h"


// getRightClicksSuggestionsBasedOnState very similar to getLeftClicksSuggestionsBasedOnState.
// getRightClickSuggestions very similar to getLeftClickSuggestions are similar. 
// Investigte if these could be combined. 

namespace minesweeperSolver
{
  clickSuggestions getRightClicksSuggestionsBasedOnState( minesweeperGame::ms_game inputGame,
    minesweeperGame::cellStateEnum inputState )
  {// Rework needed - combine with Left version
    clickSuggestions suggestions;

    minesweeperGame::setOfCoordinates stateCoordinates =
      inputGame.getCoordinatesBasedOnState( inputState );

    for ( const auto stateCoordinate : stateCoordinates )
    {
      if (
        // Cell revealed
        inputGame.isCellRevealedAndHasNeighboringMines( stateCoordinate ) &&

        // Cell has unknown neighbors
        inputGame.getNumberOfNeighborsBasedOnState( stateCoordinate,
          minesweeperGame::cellStateEnum::unknown ) > 0 &&

        // The number of unknowns + marked equal the number of neighboring mines
        inputGame.getNumberOfNeighborsBasedOnState( stateCoordinate,
          minesweeperGame::cellStateEnum::unknown ) +
        inputGame.getNumberOfNeighborsBasedOnState( stateCoordinate,
          minesweeperGame::cellStateEnum::marked )
        == inputGame.convertStateEnumToNumberOfMines( inputState ) )
      {
        minesweeperGame::setOfCoordinates coordinates =
          inputGame.getNeighborCoordinatesBasedOnState( stateCoordinate,
            minesweeperGame::cellStateEnum::unknown );

        for ( const auto neighborCoordinate : coordinates )
        {
          suggestions.insert( std::make_pair( neighborCoordinate, 'r' ) ); // To do: Remove magic numbers
        }
      }
    }

    return suggestions;
  }

  clickSuggestions getRightClickSuggestions( minesweeperGame::ms_game inputGame )
  {// Rework needed
    clickSuggestions suggestions;

    if ( suggestions.empty() )
    {
      suggestions = getRightClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::oneBlue );
    }
    if ( suggestions.empty() )
    {
      suggestions = getRightClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::twoGreen );
    }
    if ( suggestions.empty() )
    {
      suggestions = getRightClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::threeRed );
    }
    if ( suggestions.empty() )
    {
      suggestions = getRightClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::fourDarkBlue );
    }
    if ( suggestions.empty() )
    {
      suggestions = getRightClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::fiveBrown );
    }
    if ( suggestions.empty() )
    {
      suggestions = getRightClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::sixTeal );
    }
    if ( suggestions.empty() )
    {
      suggestions = getRightClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::sevenBlack );
    }
    if ( suggestions.empty() )
    {
      suggestions = getRightClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::eightGrey );
    }

    return suggestions;
  }

  clickSuggestions getLeftClicksSuggestionsBasedOnState( minesweeperGame::ms_game inputGame,
    minesweeperGame::cellStateEnum inputState )
  {// Rework needed - combine with Right version
    clickSuggestions suggestions;

    minesweeperGame::setOfCoordinates stateCoordinates =
      inputGame.getCoordinatesBasedOnState( inputState );

    for ( const auto stateCoordinate : stateCoordinates )
    {
      if (
        // Cell revealed
        inputGame.isCellRevealedAndHasNeighboringMines( stateCoordinate ) &&

        // Cell has one or more unknown neighbors
        inputGame.getNumberOfNeighborsBasedOnState( stateCoordinate,
          minesweeperGame::cellStateEnum::unknown ) > 0 &&

        // The number of cell neighboring equals to marked neighboring mines
        inputGame.getNumberOfNeighborsBasedOnState( stateCoordinate,
          minesweeperGame::cellStateEnum::marked )
        == inputGame.convertStateEnumToNumberOfMines( inputState ) )
      {
        minesweeperGame::setOfCoordinates coordinates =
          inputGame.getNeighborCoordinatesBasedOnState( stateCoordinate,
            minesweeperGame::cellStateEnum::unknown );

        for ( const auto neighborCoordinate : coordinates )
        {
          suggestions.insert( std::make_pair( neighborCoordinate, 'l' ) ); // To do: Remove magic numbers
        }
      }
    }

    return suggestions;
  }

  clickSuggestions getLeftClickSuggestions( minesweeperGame::ms_game inputGame )
  {// Rework needed
    clickSuggestions suggestions;

    if ( suggestions.empty() )
    {
      suggestions = getLeftClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::oneBlue );
    }
    if ( suggestions.empty() )
    {
      suggestions = getLeftClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::twoGreen );
    }
    if ( suggestions.empty() )
    {
      suggestions = getLeftClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::threeRed );
    }
    if ( suggestions.empty() )
    {
      suggestions = getLeftClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::fourDarkBlue );
    }
    if ( suggestions.empty() )
    {
      suggestions = getLeftClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::fiveBrown );
    }
    if ( suggestions.empty() )
    {
      suggestions = getLeftClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::sixTeal );
    }
    if ( suggestions.empty() )
    {
      suggestions = getLeftClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::sevenBlack );
    }
    if ( suggestions.empty() )
    {
      suggestions = getLeftClicksSuggestionsBasedOnState( inputGame,
        minesweeperGame::cellStateEnum::eightGrey );
    }

    return suggestions;
  }

  clickSuggestions getLeftClickGambleSuggestions( minesweeperGame::ms_game inputGame )
  {// Rework needed - should also use risk analysis instead of "random"
    clickSuggestions suggestions;

    minesweeperGame::setOfCoordinates coordinates =
      inputGame.getCoordinatesBasedOnState( minesweeperGame::cellStateEnum::unknown );

    for ( const auto coordinate : coordinates )
    {
      suggestions.insert( std::make_pair( coordinate, 'l' ) ); // To do: Remove magic numbers
    }

    return suggestions;
  }

}  // namespace minesweeperSolver
