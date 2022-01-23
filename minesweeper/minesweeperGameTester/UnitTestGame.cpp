#include "pch.h"
#include "../minesweeper/minesweeperGame.cpp"

TEST( CreateBoards, BeginnerBoard )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;

  const minesweeper::ms_game game( width, height, numOfMine );

  SUCCEED();
}

TEST( CreateBoards, IntermidiateBoard )
{
  int width = 16;
  int height = 16;
  int numOfMine = 40;

  const minesweeper::ms_game game( width, height, numOfMine );

  SUCCEED();
}

TEST( CreateBoards, ExpertBoard )
{
  int width = 30;
  int height = 16;
  int numOfMine = 99;
  int boardSize = width * height;

  const minesweeper::ms_game game( width, height, numOfMine );

  SUCCEED();
}

TEST( CreateBoards, UnsupportedBoard1 )
{
  try
  {
    const minesweeper::ms_game game( 0, 0, 0 );
    FAIL();
  }
  catch ( const std::invalid_argument& )
  {
    SUCCEED();
  }
  catch ( const std::exception& )
  {
    FAIL();
  }
}

TEST( CreateBoards, UnsupportedBoard2 )
{
  try
  {
    const minesweeper::ms_game game( -1, 0, 99 );
    FAIL();
  }
  catch ( const std::invalid_argument& )
  {
    SUCCEED();
  }
  catch ( const std::exception& )
  {
    FAIL();
  }
}

TEST( CreateBoards, UnsupportedBoard3 )
{
  try
  {
    const minesweeper::ms_game game( 9, 8, 10 );
    FAIL();
  }
  catch ( const std::invalid_argument& )
  {
    SUCCEED();
  }
  catch ( const std::exception& )
  {
    FAIL();
  }
}

TEST( BoardStats, BeginnerBoard )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;

  const minesweeper::ms_game game( width, height, numOfMine );
  minesweeper::gameBoard board = game.getBoard();

  ASSERT_EQ( game.getWidth(), width );
  ASSERT_EQ( game.getHeight(), height );
  ASSERT_EQ( game.getNumMines(), numOfMine );
  ASSERT_EQ( board.size(), boardSize );
}

TEST( Interface, ValidCoordinateTrue )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;

  minesweeper::ms_game game( width, height, numOfMine );

  ASSERT_TRUE( game.isValidCoordinate( std::make_pair( 1, 1 ) ) );
  ASSERT_TRUE( game.isValidCoordinate( std::make_pair( 9, 9 ) ) );
}

TEST( Interface, ValidCoordinateFalse )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;

  minesweeper::ms_game game( width, height, numOfMine );

  ASSERT_FALSE( game.isValidCoordinate( std::make_pair( -1, 0 ) ) );
  ASSERT_FALSE( game.isValidCoordinate( std::make_pair( 10, 9 ) ) );
}
