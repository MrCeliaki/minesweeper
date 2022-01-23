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

TEST( CreateBoards, UnsupportedPreFabBoard1 )
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

TEST( CreateBoards, UnsupportedPreFabBoard2 )
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

TEST( CreateBoards, UnsupportedPreFabBoard3 )
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

TEST( CreateBoards, CreateBoardUsingCustomBoardAndMines )
{
  //  1  1
  //  1  *
  int width = 2;
  int height = 2;
  int boardSize = width * height;
  minesweeper::gameBoard expectedBoard;
  minesweeper::mineField mines;

  // Create board
  expectedBoard.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      expectedBoard.insert( std::make_pair( std::make_pair( col, row ), minesweeper::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( std::make_pair( 2, 2 ) );

  minesweeper::ms_game game( expectedBoard, mines );

  // Check basics
  ASSERT_EQ( game.getBoard(), expectedBoard );
  ASSERT_EQ( game.getNumMines(), mines.size() );
  ASSERT_EQ( game.getWidth(), width );
  ASSERT_EQ( game.getHeight(), height );

  // Check active state
  ASSERT_TRUE( game.isGameActive() );
  game.leftClickCell( std::make_pair( 1, 1 ) );
  game.leftClickCell( std::make_pair( 2, 1 ) );
  game.leftClickCell( std::make_pair( 1, 2 ) );
  ASSERT_TRUE( game.isGameActive() );
  game.leftClickCell( std::make_pair( 2, 2 ) );
  ASSERT_FALSE( game.isGameActive() );
}

TEST( Interface, GetWidth )
{
  int width = 30;
  int height = 16;
  int numOfMine = 99;
  int boardSize = width * height;

  const minesweeper::ms_game game( width, height, numOfMine );
  minesweeper::gameBoard board = game.getBoard();

  ASSERT_EQ( game.getWidth(), width );
}

TEST( Interface, GetHeight )
{
  int width = 30;
  int height = 16;
  int numOfMine = 99;
  int boardSize = width * height;

  const minesweeper::ms_game game( width, height, numOfMine );
  minesweeper::gameBoard board = game.getBoard();

  ASSERT_EQ( game.getHeight(), height );
}

TEST( Interface, GetNumMines )
{
  int width = 30;
  int height = 16;
  int numOfMine = 99;
  int boardSize = width * height;

  const minesweeper::ms_game game( width, height, numOfMine );
  minesweeper::gameBoard board = game.getBoard();

  ASSERT_EQ( game.getNumMines(), numOfMine );
}

TEST( Interface, GetBoard )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;

  const minesweeper::ms_game game( width, height, numOfMine );
  minesweeper::gameBoard board = game.getBoard();

  ASSERT_EQ( board.size(), boardSize );
  for ( auto iter = board.begin(); iter != board.end(); ++iter )
  {
    ASSERT_EQ( iter->second, minesweeper::cellStateEnum::unknown );
  }
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

TEST( Interface, isGameActiveTrue )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;

  minesweeper::ms_game game( width, height, numOfMine );

  ASSERT_TRUE( game.isGameActive() );
}

TEST( Interface, isGameActiveFalse )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;

  minesweeper::ms_game game( width, height, numOfMine );
  minesweeper::gameBoard board = game.getBoard();

  // Click all the cells => Will click on a mine
  for ( auto iter = board.begin(); iter != board.end(); ++iter )
  {
    game.leftClickCell( iter->first );
  }

  ASSERT_FALSE( game.isGameActive() );
}

TEST( Interface, leftClick )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;

  minesweeper::ms_game game( width, height, numOfMine );
  minesweeper::gameBoard board = game.getBoard();

  ASSERT_EQ( board[ std::make_pair( 1, 1 ) ], minesweeper::cellStateEnum::unknown );
  game.leftClickCell( std::make_pair( 1, 1 ) );
  board = game.getBoard();
  ASSERT_NE( board[ std::make_pair( 1, 1 ) ], minesweeper::cellStateEnum::unknown );
}

TEST( Interface, rightClick )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;

  minesweeper::ms_game game( width, height, numOfMine );
  minesweeper::gameBoard board = game.getBoard();

  ASSERT_EQ( board[ std::make_pair( 1, 1 ) ], minesweeper::cellStateEnum::unknown );
  game.rightClickCell( std::make_pair( 1, 1 ) );
  board = game.getBoard();
  ASSERT_EQ( board[ std::make_pair( 1, 1 ) ], minesweeper::cellStateEnum::marked );
}

TEST( Interface, getNumberOfNeighborsBasedOnState_CornerAllMatch )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;
  int expected = 3;

  minesweeper::ms_game game( width, height, numOfMine );
  int actual = game.getNumberOfNeighborsBasedOnState( std::make_pair( 1, 1 ), minesweeper::cellStateEnum::unknown );

  ASSERT_EQ( actual, expected );
}

TEST( Interface, getNumberOfNeighborsBasedOnState_OpenAllMatch )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;
  int boardSize = width * height;
  int expected = 8;

  minesweeper::ms_game game( width, height, numOfMine );
  int actual = game.getNumberOfNeighborsBasedOnState( std::make_pair( 2, 2 ), minesweeper::cellStateEnum::unknown );

  ASSERT_EQ( actual, expected );
}

TEST( Interface, getNeighborCoordinatesBasedOnState )
{
  //  _  _  _
  //  _  1  1
  //  _  1  *
  int width = 3;
  int height = 3;
  int boardSize = width * height;
  minesweeper::gameBoard board;
  minesweeper::mineField mines;
  minesweeper::coordinate midCoord = std::make_pair( 2, 2 );
  minesweeper::coordinate mineCoord = std::make_pair( 3, 3 );

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeper::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord );

  minesweeper::ms_game game( board, mines );

  game.leftClickCell( midCoord );
  ASSERT_EQ( 8, game.getNeighborCoordinatesBasedOnState( midCoord, minesweeper::cellStateEnum::unknown ).size() );
  game.rightClickCell( mineCoord );
  ASSERT_EQ( 1, game.getNeighborCoordinatesBasedOnState( midCoord, minesweeper::cellStateEnum::marked ).size() );
}

TEST( Interface, getNeighborCoordinates )
{
  //  _  _  _
  //  _  1  1
  //  _  1  *
  int width = 3;
  int height = 3;
  int boardSize = width * height;
  minesweeper::gameBoard board;
  minesweeper::mineField mines;
  minesweeper::coordinate midCoord = std::make_pair( 2, 2 );
  minesweeper::coordinate mineCoord = std::make_pair( 3, 3 );
  minesweeper::setOfCoordinates expectedCoords;

  // Create board and generate expected coords
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeper::cellStateEnum::unknown ) );
      expectedCoords.insert( std::make_pair( col, row ) );
    }
  }
  expectedCoords.erase( std::make_pair( 2, 2 ) );

  // Create mines
  mines.clear();
  mines.insert( mineCoord );

  minesweeper::ms_game game( board, mines );

  ASSERT_EQ( game.getNeighborCoordinates( midCoord ), expectedCoords );
}

TEST( Interface, isCellRevealedAndHasNeighboringMines )
{
  //  _  _  _
  //  _  1  1
  //  _  1  *
  int width = 3;
  int height = 3;
  int boardSize = width * height;
  minesweeper::gameBoard board;
  minesweeper::mineField mines;
  minesweeper::coordinate midCoord = std::make_pair( 2, 2 );
  minesweeper::coordinate topLeftCoord = std::make_pair( 1, 1 );
  minesweeper::coordinate mineCoord = std::make_pair( 3, 3 );

  // Create board and generate expected coords
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeper::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord );

  minesweeper::ms_game game( board, mines );

  ASSERT_FALSE( game.isCellRevealedAndHasNeighboringMines( midCoord ) );
  ASSERT_FALSE( game.isCellRevealedAndHasNeighboringMines ( topLeftCoord ));
  game.leftClickCell( topLeftCoord );
  ASSERT_TRUE( game.isCellRevealedAndHasNeighboringMines( midCoord ) );
  ASSERT_FALSE( game.isCellRevealedAndHasNeighboringMines( topLeftCoord ) );
}

TEST( Interface, areTheNumberOfMarkedMinesEqualToCellValue )
{
  //  _  _  1  *  1
  //  _  1  2  3  2
  //  _  1  *  2  *
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeper::gameBoard board;
  minesweeper::mineField mines;
  minesweeper::coordinate mineCoord1 = std::make_pair( 4, 1 );
  minesweeper::coordinate mineCoord2 = std::make_pair( 3, 3 );
  minesweeper::coordinate mineCoord3 = std::make_pair( 5, 3 );

  // Create board and generate expected coords
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeper::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );

  minesweeper::ms_game game( board, mines );

  ASSERT_FALSE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 1, 1 ) ) );
  ASSERT_FALSE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 4, 2 ) ) );
  ASSERT_FALSE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 4, 3 ) ) );
  game.leftClickCell( std::make_pair( 1, 1 ) );
  ASSERT_FALSE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 1, 1 ) ) );

  ASSERT_FALSE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 2, 2 ) ) );
  game.rightClickCell( mineCoord2 );
  ASSERT_TRUE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 2, 2 ) ) );

  ASSERT_FALSE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 3, 2 ) ) );
  game.rightClickCell( mineCoord1 );
  ASSERT_TRUE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 3, 2 ) ) );

  ASSERT_FALSE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 4, 2 ) ) );
  game.rightClickCell( mineCoord3 );
  ASSERT_FALSE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 4, 2 ) ) );
  game.leftClickCell( std::make_pair( 4, 2 ) );
  ASSERT_TRUE( game.areTheNumberOfMarkedMinesEqualToCellValue( std::make_pair( 4, 2 ) ) );
}