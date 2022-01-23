#include "minesweeperGame.h"
#include <stdexcept>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

namespace minesweeperGame
{
  ms_game::ms_game()
  {
  }

  ms_game::ms_game( gameBoard inputBoard, mineField inputMines )
  {
    board = inputBoard;
    mines = inputMines;
    gameState = gameStateEnum::playing;
  }

  ms_game::ms_game( uint8_t inputWidth, uint8_t inputHeight, uint16_t inputMines )
  {
    if ( validBoard( inputWidth, inputHeight, inputMines ) )
    {
      generateBoard( inputWidth, inputHeight );
      generateMines( inputWidth, inputHeight, inputMines );
      gameState = gameStateEnum::playing;
    }
    else
    {
      throw std::invalid_argument( "Invalid board size and/or number of mines" );
    }
  }

  void ms_game::generateBoard( const uint8_t inputWidth, const uint8_t inputHeight )
  {
    board.clear();

    for ( int row = 1; row <= inputHeight; row++ )
    {
      for ( int col = 1; col <= inputWidth; col++ )
      {
        board.insert( std::make_pair( std::make_pair( col, row ), cellStateEnum::unknown ) );
      }
    }
  }

  void ms_game::generateMines( const uint8_t inputWidth, const uint8_t inputHeight, const uint16_t inputNumMines )
  {
    if ( inputWidth * inputHeight < inputNumMines )
    {
      throw std::exception( "placeMines 1: Dead Programs Tell No Lies" );
    }

    mines.clear();
    srand( time( NULL ) );

    for ( size_t i = 0; i < inputNumMines; i++ )
    {
      while ( true )
      {
        int col = ( rand() % getWidth() ) + 1;
        int row = ( rand() % getHeight() ) + 1;

        if ( mines.find( std::make_pair( col, row ) ) == mines.end() )
        {
          mines.insert( std::make_pair( col, row ) );
          break;
        }
      }
    }
  }

  void ms_game::leftClickCell( coordinate inputCoordinate )
  {// Rework needed
    if ( ( gameState != gameStateEnum::playing ) ||
      ( !isValidCoordinate( inputCoordinate ) ) )
    {
      return;
    }

    if ( isMine( inputCoordinate ) )
    {
      setGameLost( inputCoordinate );
      return;
    }
    else if ( board[ inputCoordinate ] == cellStateEnum::unknown )
    {
      activeCell( inputCoordinate );
    }
    else if ( ( board[ inputCoordinate ] == cellStateEnum::empty ) ||
      ( board[ inputCoordinate ] == cellStateEnum::marked ) )
    {
      // Ignore
      return;
    }
    else if ( isCellRevealedAndHasNeighboringMines( inputCoordinate ) &&
      areTheNumberOfMarkedMinesEqualToCellValue( inputCoordinate ) )
    {
      setOfCoordinates unknownNeighborsCoordinates = getNeighborCoordinatesBasedOnState( inputCoordinate, cellStateEnum::unknown );
      for ( auto iter = unknownNeighborsCoordinates.begin(); iter != unknownNeighborsCoordinates.end(); ++iter )
      {
        activeCell( *iter );
      }
    }
    else
    {

    }

    if ( isGameBoardRevealed() )
    {
      setGameWon();
    }
  }

  void ms_game::rightClickCell( coordinate inputCoordinate )
  {
    if ( ( gameState != gameStateEnum::playing ) ||
      ( !isValidCoordinate( inputCoordinate ) ) )
    {
      return;
    }

    if ( board[ inputCoordinate ] == cellStateEnum::marked )
    {
      board[ inputCoordinate ] = cellStateEnum::unknown;
    }
    else if ( board[ inputCoordinate ] == cellStateEnum::unknown )
    {
      board[ inputCoordinate ] = cellStateEnum::marked;
    }

    if ( isGameBoardRevealed() )
    {
      setGameWon();
    }

  }

  void ms_game::activeCell( coordinate inputCoordinate )
  {// Rework needed and rename?
    setOfCoordinates coordinateHistory;
    std::queue<coordinate> jobQueue;
    coordinateHistory.insert( inputCoordinate );
    jobQueue.push( inputCoordinate );

    while ( !jobQueue.empty() )
    {
      revealCell( jobQueue.front() );

      if ( !isGameActive() )
      {
        return;
      }

      if ( board[ jobQueue.front() ] == cellStateEnum::empty )
      {
        setOfCoordinates neighbors = getNeighborCoordinates( jobQueue.front() );

        for ( auto iter = neighbors.begin(); iter != neighbors.end(); ++iter )
        {
          if ( coordinateHistory.find( *iter ) == coordinateHistory.end() )
          {
            coordinateHistory.insert( *iter );
            jobQueue.push( *iter );
          }
        }
      }

      jobQueue.pop();
    }
  }

  void ms_game::revealCell( coordinate inputCoordinate )
  {// Rework needed and rename?
    if ( ( !isValidCoordinate( inputCoordinate ) ) )
    {
      throw std::exception( "revealCell: Dead Programs Tell No Lies" );
    }

    if ( isMine( inputCoordinate ) )
    {
      setGameLost( inputCoordinate );
      return;
    }

    int numOfMines = getNumberOfNeighboringMines( inputCoordinate );

    switch ( numOfMines )
    {
    case 0:
      board[ inputCoordinate ] = cellStateEnum::empty;
      break;
    case 1:
      board[ inputCoordinate ] = cellStateEnum::oneBlue;
      break;
    case 2:
      board[ inputCoordinate ] = cellStateEnum::twoGreen;
      break;
    case 3:
      board[ inputCoordinate ] = cellStateEnum::threeRed;
      break;
    case 4:
      board[ inputCoordinate ] = cellStateEnum::fourDarkBlue;
      break;
    case 5:
      board[ inputCoordinate ] = cellStateEnum::fiveBrown;
      break;
    case 6:
      board[ inputCoordinate ] = cellStateEnum::sixTeal;
      break;
    case 7:
      board[ inputCoordinate ] = cellStateEnum::sevenBlack;
      break;
    case 8:
      board[ inputCoordinate ] = cellStateEnum::eightGrey;
      break;
    default:
      throw std::exception( "revealCell: Dead Programs Tell No Lies" );
      break;
    }
  }

  setOfCoordinates ms_game::getNeighborCoordinates( const coordinate inputCoordinate )
  {
    setOfCoordinates neighbors;

    for ( int col = -1; col <= 1; col++ )
    {
      for ( int row = -1; row <= 1; row++ )
      {
        coordinate neighborCoordinate = std::make_pair( inputCoordinate.first + col, inputCoordinate.second + row );

        if ( isValidCoordinate( neighborCoordinate ) &&
          inputCoordinate != neighborCoordinate )
        {
          neighbors.insert( neighborCoordinate );
        }
      }
    }

    return neighbors;
  }

  int ms_game::getNumberOfNeighboringMines( const coordinate inputCoordinate )
  {
    if ( !isValidCoordinate( inputCoordinate ) )
    {
      throw std::exception( "numberOfNeighbouringMines: Dead Programs Tell No Lies" );
    }

    setOfCoordinates neighbors = getNeighborCoordinates( inputCoordinate );

    int neighbouringMines = 0;
    for ( auto iter = neighbors.begin(); iter != neighbors.end(); ++iter )
    {
      if ( isMine( *iter ) )
      {
        neighbouringMines++;
      }
    }

    return neighbouringMines;
  }

  bool ms_game::isMine( coordinate inputCoordinate ) const
  {
    return mines.find( inputCoordinate ) != mines.end();
  }

  bool ms_game::isValidCoordinate( coordinate inputCoordinate ) const
  {
    return inputCoordinate.first >= 1 && inputCoordinate.first <= getWidth() &&
      inputCoordinate.second >= 1 && inputCoordinate.second <= getHeight();
  }

  void ms_game::revealAllMines()
  {
    for ( auto iter = mines.begin(); iter != mines.end(); ++iter )
    {
      if ( board[ *iter ] != cellStateEnum::marked)
      {
        board[ *iter ] = cellStateEnum::mineWhite;
      }
    }
  }

  bool ms_game::isGameBoardRevealed() const
  {// Rename this function
    for ( auto iter = board.begin(); iter != board.end(); ++iter )
    {
      if ( ( iter->second == cellStateEnum::marked &&
        mines.find( iter->first ) == mines.end() ) ||
        ( iter->second == cellStateEnum::unknown ) )
      {
        return false;
      }
    }

    return true;
  }

  bool ms_game::validBoard( uint8_t width, uint8_t height, uint16_t mines ) const
  {
    // To do: Remove magic numbers
    return ( ( width == 9 && height == 9 && mines == 10 ) || // Beginner board
      ( width == 16 && height == 16 && mines == 40 ) || // Intermidiate board
      ( width == 30 && height == 16 && mines == 99 ) || // Expert board
      ( width == 4 && height == 4 && mines == 2 ) ); // Test board - to be removed
  }

  int ms_game::getWidth() const
  {
    return ( board.rbegin() )->first.first;
  }

  int ms_game::getHeight() const
  {
    return ( board.rbegin() )->first.second;
  }

  int ms_game::getNumMines() const
  {
    return mines.size();
  }

  gameBoard ms_game::getBoard() const
  {
    return board;
  }

  bool ms_game::isGameActive() const
  {
    return gameState == gameStateEnum::playing;
  }

  void ms_game::setGameLost( const coordinate inputCoordinate )
  {
    if ( !isValidCoordinate( inputCoordinate ) ||
      !isMine( inputCoordinate ) )
    {
      throw std::exception( "setGameLost: Dead Programs Tell No Lies" );
    }

    gameState = gameStateEnum::lost;
    revealAllMines();
    board[ inputCoordinate ] = cellStateEnum::mineRed;
  }

  void ms_game::setGameWon()
  {
    gameState = gameStateEnum::won;
    revealAllMines();
  }

  bool ms_game::isCellRevealedAndHasNeighboringMines( coordinate inputCoordinate )
  {//Change name
    return ( ( board[ inputCoordinate ] == cellStateEnum::oneBlue ) ||
      ( board[ inputCoordinate ] == cellStateEnum::twoGreen ) ||
      ( board[ inputCoordinate ] == cellStateEnum::threeRed ) ||
      ( board[ inputCoordinate ] == cellStateEnum::fourDarkBlue ) ||
      ( board[ inputCoordinate ] == cellStateEnum::fiveBrown ) ||
      ( board[ inputCoordinate ] == cellStateEnum::sixTeal ) ||
      ( board[ inputCoordinate ] == cellStateEnum::sevenBlack ) ||
      ( board[ inputCoordinate ] == cellStateEnum::eightGrey ) );
  }

  bool ms_game::areTheNumberOfMarkedMinesEqualToCellValue( coordinate inputCoordinate )
  {//Change name and reworked needed
    if ( !isCellRevealedAndHasNeighboringMines( inputCoordinate ) ||
      !isValidCoordinate( inputCoordinate ) )
    {
      return false;
    }

    int numberOfMarkedNeighbors = getNumberOfNeighborsBasedOnState( inputCoordinate, cellStateEnum::marked );

    if ( ( numberOfMarkedNeighbors == convertStateEnumToNumberOfMines( cellStateEnum::oneBlue )
      && board[ inputCoordinate ] == cellStateEnum::oneBlue ) ||
      ( numberOfMarkedNeighbors == convertStateEnumToNumberOfMines( cellStateEnum::twoGreen ) 
        && board[ inputCoordinate ] == cellStateEnum::twoGreen ) ||
      ( numberOfMarkedNeighbors == convertStateEnumToNumberOfMines( cellStateEnum::threeRed ) 
        && board[ inputCoordinate ] == cellStateEnum::threeRed ) ||
      ( numberOfMarkedNeighbors == convertStateEnumToNumberOfMines( cellStateEnum::fourDarkBlue ) 
        && board[ inputCoordinate ] == cellStateEnum::fourDarkBlue ) ||
      ( numberOfMarkedNeighbors == convertStateEnumToNumberOfMines( cellStateEnum::fiveBrown ) 
        && board[ inputCoordinate ] == cellStateEnum::fiveBrown ) ||
      ( numberOfMarkedNeighbors == convertStateEnumToNumberOfMines( cellStateEnum::sixTeal ) 
        && board[ inputCoordinate ] == cellStateEnum::sixTeal ) ||
      ( numberOfMarkedNeighbors == convertStateEnumToNumberOfMines( cellStateEnum::sevenBlack ) 
        && board[ inputCoordinate ] == cellStateEnum::sevenBlack ) ||
      ( numberOfMarkedNeighbors == convertStateEnumToNumberOfMines( cellStateEnum::eightGrey ) 
        && board[ inputCoordinate ] == cellStateEnum::eightGrey ) )
    {
      return true;
    }
    else
    {
      return false;
    }

  }

  setOfCoordinates ms_game::getNeighborCoordinatesBasedOnState( coordinate inputCoordinate, cellStateEnum inputCellState )
  {
    setOfCoordinates allNeighborsCoordinates = getNeighborCoordinates( inputCoordinate );
    setOfCoordinates neighborsWithStateCoordinates;

    for ( auto iter = allNeighborsCoordinates.begin(); iter != allNeighborsCoordinates.end(); ++iter )
    {
      if ( board[ *iter ] == inputCellState )
      {
        neighborsWithStateCoordinates.insert( *iter );
      }
    }

    return neighborsWithStateCoordinates;
  }

  int ms_game::getNumberOfNeighborsBasedOnState( coordinate inputCoordinate, cellStateEnum inputCellState )
  {
    return getNeighborCoordinatesBasedOnState( inputCoordinate, inputCellState ).size();
  }

  setOfCoordinates ms_game::getCoordinatesBasedOnState( cellStateEnum inputCellState )
  {
    setOfCoordinates stateCoordinates;
    for ( auto iter = board.begin(); iter != board.end(); ++iter )
    {
      if ( iter->second == inputCellState )
      {
        stateCoordinates.insert( iter->first );
      }
    }

    return stateCoordinates;
  }

  int ms_game::convertStateEnumToNumberOfMines( cellStateEnum inputState )
  {
    int numberOfMines = 0;

    switch ( inputState )
    {
      break;
    case minesweeperGame::oneBlue:
      numberOfMines = 1;
      break;
    case minesweeperGame::twoGreen:
      numberOfMines = 2;
      break;
    case minesweeperGame::threeRed:
      numberOfMines = 3;
      break;
    case minesweeperGame::fourDarkBlue:
      numberOfMines = 4;
      break;
    case minesweeperGame::fiveBrown:
      numberOfMines = 5;
      break;
    case minesweeperGame::sixTeal:
      numberOfMines = 6;
      break;
    case minesweeperGame::sevenBlack:
      numberOfMines = 7;
      break;
    case minesweeperGame::eightGrey:
      numberOfMines = 8;
      break;
    case minesweeperGame::mineWhite:
    case minesweeperGame::mineRed:
    case minesweeperGame::marked:
    case minesweeperGame::unknown:
    case minesweeperGame::empty:
    default:
      break;
    }
    return numberOfMines;
  }

}  // namespace minesweeperGame
