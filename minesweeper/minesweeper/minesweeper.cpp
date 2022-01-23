#include <iostream>
#include <vector>
#include <algorithm>
#include "minesweeperGame.h"
#include <string>
#include <Windows.h>

#define CONSOLE_COLOR_BRIGHT_GREEN 10
#define CONSOLE_COLOR_BRIGHT_WHITE 15
#define CONSOLE_COLOR_BRIGHT_YELLOW 14
#define CONSOLE_COLOR_BRIGHT_BLUE 9
#define CONSOLE_COLOR_BRIGHT_RED 12
#define CONSOLE_COLOR_GREY 8
#define CONSOLE_COLOR_BLUE 1
#define CONSOLE_COLOR_BROWN 4
#define CONSOLE_COLOR_TEAL 3
#define CONSOLE_COLOR_LIGHT_GREY 7

// https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
class InputParser
{
public:
  InputParser( int &argc, char **argv )
  {
    for ( int i = 1; i < argc; ++i )
      this->tokens.push_back( std::string( argv[ i ] ) );
  }
  bool cmdOptionExists( const std::string &option ) const
  {
    return std::find( this->tokens.begin(), this->tokens.end(), option )
      != this->tokens.end();
  }
private:
  std::vector <std::string> tokens;
};

void printCell( minesweeperGame::cellStateEnum state )
{
  HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

  char charToPrint = ' ';
  switch ( state )
  {
  case minesweeperGame::cellStateEnum::mineWhite:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );
    charToPrint = '*';
    break;
  case minesweeperGame::cellStateEnum::mineRed:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_RED );
    charToPrint = '*';
    break;
  case minesweeperGame::cellStateEnum::marked:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_YELLOW );
    charToPrint = 'F';
    break;
  case minesweeperGame::cellStateEnum::unknown:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );
    charToPrint = 254;
    break;
  case minesweeperGame::cellStateEnum::empty:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );
    charToPrint = ' ';
    break;
  case minesweeperGame::cellStateEnum::oneBlue:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_BLUE );
    charToPrint = '1';
    break;
  case minesweeperGame::cellStateEnum::twoGreen:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_GREEN );
    charToPrint = '2';
    break;
  case minesweeperGame::cellStateEnum::threeRed:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_RED );
    charToPrint = '3';
    break;
  case minesweeperGame::cellStateEnum::fourDarkBlue:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BLUE );
    charToPrint = '4';
    break;
  case minesweeperGame::cellStateEnum::fiveBrown:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BROWN );
    charToPrint = '5';
    break;
  case minesweeperGame::cellStateEnum::sixTeal:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_TEAL );
    charToPrint = '6';
    break;
  case minesweeperGame::cellStateEnum::sevenBlack:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_GREY );
    charToPrint = '7';
    break;
  case minesweeperGame::cellStateEnum::eightGrey:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_LIGHT_GREY );
    charToPrint = '8';
    break;
  default:
    throw std::exception( "getCharFromCellState: Dead Programs Tell No Lies" );
    break;
  }

  std::cout << charToPrint;
  SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );
}

void displayBoard( minesweeperGame::ms_game game )
{
  minesweeperGame::gameBoard board = game.getBoard();

  // Print col number above the board
  std::cout << "   ";
  for ( int col = 1; col <= game.getWidth(); col++ )
  {
    if ( col < 10 )
    {
      std::cout << " " << col << " ";
    }
    else
    {
      std::cout << col << " ";
    }
  }
  std::cout << std::endl;

  // Print row number on each side of the board
  // Print the board
  for ( int row = 1; row <= game.getHeight(); row++ )
  {
    if ( row < 10 )
    {
      std::cout << " " << row << "  ";
    }
    else
    {
      std::cout << row << "  ";
    }

    for ( int col = 1; col <= game.getWidth(); col++ )
    {
      if ( col != 1 )
      {
        std::cout << "  ";
      }
      printCell( board[ std::make_pair( col, row ) ] );
    }
    std::cout << "  " << row << std::endl;
  }

  // Print col number below the board
  std::cout << "   ";
  for ( int col = 1; col <= game.getWidth(); col++ )
  {
    if ( col < 10 )
    {
      std::cout << " " << col << " ";
    }
    else
    {
      std::cout << col << " ";
    }
  }

}

int main( int argc, char **argv )
{
  int width = 0;
  int height = 0;
  int numOfMine = 0;

  InputParser input( argc, argv );

  // Help
  if ( input.cmdOptionExists( "-h" ) )
  {
    //TO DO: Print help text
    throw std::exception( "Not Yet Implemented" );
    return 0;
  }

  // Board selection
  if ( input.cmdOptionExists( "-b" ) )
  {
    width = 9;
    height = 9;
    numOfMine = 10;
  }
  else if ( input.cmdOptionExists( "-i" ) )
  {
    width = 16;
    height = 16;
    numOfMine = 40;
  }
  else if ( input.cmdOptionExists( "-e" ) )
  {
    width = 30;
    height = 16;
    numOfMine = 99;
  }
  else if ( input.cmdOptionExists( "-t" ) )
  {
    width = 4;
    height = 4;
    numOfMine = 2;
  }
  else
  {
    std::cout << "Board argument missing." << std::endl;
    return 0;
  }

  bool autoSolverActive = false;

  // Manual or Auto-solver selection
  if ( input.cmdOptionExists( "-m" ) )
  {
    autoSolverActive = false;
  }
  else if ( input.cmdOptionExists( "-a" ) )
  {
    throw std::exception( "Not Yet Implemented" );
    autoSolverActive = true;
  }
  else
  {
    std::cout << "Solver argument missing." << std::endl;
    return 0;
  }

  minesweeperGame::ms_game game( width, height, numOfMine );

  HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
  SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );
  system( "cls" );
  displayBoard( game );

  bool keepPlaying = true;
  while ( keepPlaying )
  {
    std::string arg;
    int col;
    int row;

    if ( autoSolverActive )
    {
      throw std::exception( "Not Yet Implemented" );
    }
    else
    {
      std::cout << std::endl;
      std::cin >> arg >> col >> row;
    }
    std::pair<int, int> clickCoordinate = std::make_pair( col, row );

    switch ( arg[ 0 ] )
    {
    case 'q':
      keepPlaying = false;
      break;
    case 'l':
      if ( game.isValidCoordinate( clickCoordinate ) )
      {
        game.leftClickCell( clickCoordinate );
      }
      break;
    case 'r':
      if ( game.isValidCoordinate( clickCoordinate ) )
      {
        game.rightClickCell( clickCoordinate );
      }
      break;
    default:
      break;
    }

    system( "cls" );
    displayBoard( game );

    if ( !game.isGameActive() )
    {
      keepPlaying = false;
    }

  }

  return 0;
}