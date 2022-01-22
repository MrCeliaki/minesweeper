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

void printChar( minesweeper::cellStateEnum state )
{
  HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

  char charToPrint = ' ';
  switch ( state )
  {
  case minesweeper::cellStateEnum::mineWhite:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );
    charToPrint = '*';
    break;
  case minesweeper::cellStateEnum::mineRed:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_RED );
    charToPrint = '*';
    break;
  case minesweeper::cellStateEnum::marked:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_YELLOW );
    charToPrint = 'F';
    break;
  case minesweeper::cellStateEnum::unknown:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );
    charToPrint = '_';
    break;
  case minesweeper::cellStateEnum::empty:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );
    charToPrint = '.';
    break;
  case minesweeper::cellStateEnum::oneBlue:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_BLUE );
    charToPrint = '1';
    break;
  case minesweeper::cellStateEnum::twoGreen:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_GREEN );
    charToPrint = '2';
    break;
  case minesweeper::cellStateEnum::threeRed:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_RED );
    charToPrint = '3';
    break;
  case minesweeper::cellStateEnum::fourDarkBlue:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BLUE );
    charToPrint = '4';
    break;
  case minesweeper::cellStateEnum::fiveBrown:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BROWN );
    charToPrint = '5';
    break;
  case minesweeper::cellStateEnum::sixTeal:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_TEAL );
    charToPrint = '6';
    break;
  case minesweeper::cellStateEnum::sevenBlack:
    SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_GREY );
    charToPrint = '7';
    break;
  case minesweeper::cellStateEnum::eightGrey:
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

void displayBoard( minesweeper::ms_game game )
{
  HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
  SetConsoleTextAttribute( hConsole, CONSOLE_COLOR_BRIGHT_WHITE );

  minesweeper::gameBoard board = game.getBoard();

  for ( int col = 1; col <= game.getWidth(); col++ )
  {
    std::cout << col << " |";

    for ( int row = 1; row <= game.getHeight(); row++ )
    {
      if ( row != 1 )
      {
        std::cout << ' ';
      }
      printChar( board[ std::make_pair( col, row ) ] );
    }
    std::cout << "| " << col << std::endl;
  }

}

int main( int argc, char **argv )
{
  /*
  InputParser input( argc, argv );
  if ( input.cmdOptionExists( "-b" ) )
  {
    // Do stuff
  }
  */


  int width = 4;
  int height = 4;
  int numOfMine = 2;

  minesweeper::ms_game game( width, height, numOfMine );

  system( "cls" );
  displayBoard( game );

  bool keepPlaying = true;
  while ( keepPlaying )
  {
    std::string arg;
    int col;
    int row;

    std::cin >> arg >> col >> row;
    std::pair<int, int> coordinate = std::make_pair( col, row );

    switch ( arg[ 0 ] )
    {
    case 'q':
      keepPlaying = false;
      break;
    case 'l':
      if ( game.isValidCoordinate( coordinate ) )
      {
        game.leftClickCell( coordinate );
      }
      break;
    case 'r':
      if ( game.isValidCoordinate( coordinate ) )
      {
        game.rightClickCell( coordinate );
      }
      break;
    default:
      break;
    }

    system( "cls" );
    displayBoard( game );
  }

  return 0;
}