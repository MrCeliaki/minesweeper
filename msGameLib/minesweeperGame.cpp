#include "minesweeperGame.h"
#include <stdexcept>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
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

  void ms_game::leftClickCell( boardCoordinate inputCoordinate )
  {
    if ( ( gameState != gameStateEnum::playing ) ||
      ( !isValidCoordinate( inputCoordinate ) ) )
    {
      return;
    }

    // Clicked mine
    if ( isMine( inputCoordinate ) )
    {
      setGameLost( inputCoordinate );
      return;
    }

    // Clicked unknown
    else if ( board[ inputCoordinate ] == cellStateEnum::unknown )
    {
      activeCell( inputCoordinate );
    }

    // Ignore
    else if ( ( board[ inputCoordinate ] == cellStateEnum::empty ) ||
      ( board[ inputCoordinate ] == cellStateEnum::marked ) )
    {
      return;
    }

    // Multiclick
    else if ( isCellRevealedAndHasNeighboringMines( inputCoordinate ) &&
      areTheNumberOfMarkedMinesEqualToCellValue( inputCoordinate ) )
    {
      setOfBoardCoordinates unknownNeighborsCoordinates = getNeighborCoordinatesBasedOnState( inputCoordinate, cellStateEnum::unknown );

      for ( const auto coordinate : unknownNeighborsCoordinates )
      {
        activeCell( coordinate );
      }
    }

    if ( isGameBoardRevealed() )
    {
      setGameWon();
    }
  }

  void ms_game::rightClickCell( boardCoordinate inputCoordinate )
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

  void ms_game::activeCell( boardCoordinate inputCoordinate )
  {// Rework needed and rename?
    setOfBoardCoordinates coordinateHistory;
    std::queue<boardCoordinate> jobQueue;
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
        setOfBoardCoordinates neighbors = getNeighborCoordinates( jobQueue.front() );

        for ( const auto coordinate : neighbors )
        {
          if ( coordinateHistory.find( coordinate ) == coordinateHistory.end() )
          {
            coordinateHistory.insert( coordinate );
            jobQueue.push( coordinate );
          }
        }
      }

      jobQueue.pop();
    }
  }

  void ms_game::revealCell( boardCoordinate inputCoordinate )
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

  setOfBoardCoordinates ms_game::getNeighborCoordinates( const boardCoordinate inputCoordinate )
  {
    setOfBoardCoordinates neighbors;

    for ( int col = -1; col <= 1; col++ )
    {
      for ( int row = -1; row <= 1; row++ )
      {
        boardCoordinate neighborCoordinate = std::make_pair( inputCoordinate.first + col, inputCoordinate.second + row );

        if ( isValidCoordinate( neighborCoordinate ) &&
          inputCoordinate != neighborCoordinate )
        {
          neighbors.insert( neighborCoordinate );
        }
      }
    }

    return neighbors;
  }

  int ms_game::getNumberOfNeighboringMines( const boardCoordinate inputCoordinate )
  {
    if ( !isValidCoordinate( inputCoordinate ) )
    {
      throw std::exception( "numberOfNeighbouringMines: Dead Programs Tell No Lies" );
    }

    setOfBoardCoordinates neighbors = getNeighborCoordinates( inputCoordinate );

    int neighbouringMines = 0;
    for ( const auto coordinate : neighbors )
    {
      if ( isMine( coordinate ) )
      {
        neighbouringMines++;
      }
    }

    return neighbouringMines;
  }

  bool ms_game::isMine( boardCoordinate inputCoordinate ) const
  {
    return mines.find( inputCoordinate ) != mines.end();
  }

  bool ms_game::isValidCoordinate( boardCoordinate inputCoordinate ) const
  {
    return inputCoordinate.first >= 1 && inputCoordinate.first <= getWidth() &&
      inputCoordinate.second >= 1 && inputCoordinate.second <= getHeight();
  }

  void ms_game::revealAllMines()
  {
    for ( const auto coordinate : mines )
    {
      if ( board[ coordinate ] != cellStateEnum::marked)
      {
        board[ coordinate ] = cellStateEnum::mineWhite;
      }
    }
  }

  bool ms_game::isGameBoardRevealed() const
  {// Rename this function
    for ( const auto square : board )
    {
      if ( ( square.second == cellStateEnum::marked &&
        mines.find( square.first ) == mines.end() ) ||
        ( square.second == cellStateEnum::unknown ) )
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

  void ms_game::setGameLost( const boardCoordinate inputCoordinate )
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

  bool ms_game::isCellRevealedAndHasNeighboringMines( boardCoordinate inputCoordinate )
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

  bool ms_game::areTheNumberOfMarkedMinesEqualToCellValue( boardCoordinate inputCoordinate )
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

  setOfBoardCoordinates ms_game::getNeighborCoordinatesBasedOnState( boardCoordinate inputCoordinate, cellStateEnum inputCellState )
  {
    setOfBoardCoordinates allNeighborsCoordinates = getNeighborCoordinates( inputCoordinate );
    setOfBoardCoordinates neighborsWithStateCoordinates;

    for ( const auto coordinate : allNeighborsCoordinates )
    {
      if ( board[ coordinate ] == inputCellState )
      {
        neighborsWithStateCoordinates.insert( coordinate );
      }
    }

    return neighborsWithStateCoordinates;
  }

  int ms_game::getNumberOfNeighborsBasedOnState( boardCoordinate inputCoordinate, cellStateEnum inputCellState )
  {
    return getNeighborCoordinatesBasedOnState( inputCoordinate, inputCellState ).size();
  }

  setOfBoardCoordinates ms_game::getCoordinatesBasedOnState( cellStateEnum inputCellState )
  {
    setOfBoardCoordinates stateCoordinates;
    for ( const auto square : board )
    {
      if ( square.second == inputCellState )
      {
        stateCoordinates.insert( square.first );
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
    case cellStateEnum::oneBlue:
      numberOfMines = 1;
      break;
    case cellStateEnum::twoGreen:
      numberOfMines = 2;
      break;
    case cellStateEnum::threeRed:
      numberOfMines = 3;
      break;
    case cellStateEnum::fourDarkBlue:
      numberOfMines = 4;
      break;
    case cellStateEnum::fiveBrown:
      numberOfMines = 5;
      break;
    case cellStateEnum::sixTeal:
      numberOfMines = 6;
      break;
    case cellStateEnum::sevenBlack:
      numberOfMines = 7;
      break;
    case cellStateEnum::eightGrey:
      numberOfMines = 8;
      break;
    case cellStateEnum::mineWhite:
    case cellStateEnum::mineRed:
    case cellStateEnum::marked:
    case cellStateEnum::unknown:
    case cellStateEnum::empty:
    default:
      break;
    }
    return numberOfMines;
  }

}  // namespace minesweeperGame
