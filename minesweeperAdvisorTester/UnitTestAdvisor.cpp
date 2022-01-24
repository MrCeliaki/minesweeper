#include "pch.h"
#include "../minesweeper/minesweeperGame.cpp"
#include "../minesweeper/minesweeperAdvisor.cpp"

TEST( GameSanityChecks, CheckHeight )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;

  minesweeperGame::ms_game game( width, height, numOfMine );

  EXPECT_EQ( height, game.getHeight() );
}

TEST( GameSanityChecks, CheckWidth )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;

  minesweeperGame::ms_game game( width, height, numOfMine );

  EXPECT_EQ( width, game.getWidth() );
}

TEST( GameSanityChecks, CheckNumMines )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;

  minesweeperGame::ms_game game( width, height, numOfMine );

  EXPECT_EQ( numOfMine, game.getNumMines() );
}

TEST( GameSanityChecks, CheckBoard )
{
  int width = 9;
  int height = 9;
  int numOfMine = 10;

  minesweeperGame::ms_game game( width, height, numOfMine );

  EXPECT_EQ( height*width, game.getBoard().size() );
}

TEST( Interface, getRightClickSuggestion_1 )
{
  //  _  _  _  _  _
  //  _  1  1  2  1
  //  _  1  *  2  *
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 5, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );

  // Create expected suggestions
  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClickSuggestions( game ).empty() );
  game.leftClickCell( std::make_pair( 1, 1 ) );
  ASSERT_EQ( minesweeperSolver::getRightClickSuggestions( game ).size(), 1 );
  ASSERT_EQ( minesweeperSolver::getRightClickSuggestions( game ), expectedSuggestions );
  game.leftClickCell( std::make_pair( 4, 3 ) );
  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );
  ASSERT_EQ( minesweeperSolver::getRightClickSuggestions( game ).size(), 2 );
  ASSERT_EQ( minesweeperSolver::getRightClickSuggestions( game ), expectedSuggestions );
}

TEST( Interface, getRightClickSuggestion_2 )
{
  //  _  1  1  1  _
  //  _  2  *  2  _
  //  _  2  *  2  _
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 3, 2 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );

  // Create expected suggestions
  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClickSuggestions( game ).empty() );
  game.leftClickCell( std::make_pair( 1, 1 ) );
  ASSERT_EQ( minesweeperSolver::getRightClickSuggestions( game ).size(), 2 );
  ASSERT_EQ( minesweeperSolver::getRightClickSuggestions( game ), expectedSuggestions );
  game.leftClickCell( std::make_pair( 1, 5 ) );
  ASSERT_EQ( minesweeperSolver::getRightClickSuggestions( game ).size(), 2 );
  ASSERT_EQ( minesweeperSolver::getRightClickSuggestions( game ), expectedSuggestions );
}

TEST( Interface, getRightClicksSuggestionsBasedOnState_NoMarked_3 )
{
  //  1  2  1  1  _
  //  *  3  *  2  _
  //  1  3  *  2  _
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 1, 2 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 2 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 3, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );

  // Create expected suggestions
  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord3, 'r' ) );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::threeRed ).empty() );
  game.leftClickCell( std::make_pair( 1, 1 ) );
  game.leftClickCell( std::make_pair( 1, 3 ) );
  game.leftClickCell( std::make_pair( 2, 1 ) );
  game.leftClickCell( std::make_pair( 2, 2 ) );
  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::threeRed ).empty() );
  game.leftClickCell( std::make_pair( 2, 3 ) );
  ASSERT_FALSE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::threeRed ).empty() );

  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::threeRed ), expectedSuggestions );
}

TEST( Interface, getRightClicksSuggestionsBasedOnState_NoMarked_4 )
{
  //  1  2  1  1  _
  //  *  4  *  2  _
  //  *  4  *  2  _
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 1, 2 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 2 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord4 = std::make_pair( 1, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );
  mines.insert( mineCoord4 );

  // Create expected suggestions
  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord3, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord4, 'r' ) );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::fourDarkBlue ).empty() );

  game.leftClickCell( std::make_pair( 2, 3 ) );
  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::fourDarkBlue ).empty() );

  game.leftClickCell( std::make_pair( 2, 2 ) );
  ASSERT_FALSE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::fourDarkBlue ).empty() );

  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::fourDarkBlue ), expectedSuggestions );
}

TEST( Interface, getRightClicksSuggestionsBasedOnState_NoMarked_5 )
{
  //  2  *  2  1  _
  //  *  5  *  2  _
  //  *  4  *  2  _
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 1, 2 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 2 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord4 = std::make_pair( 1, 3 );
  minesweeperGame::coordinate mineCoord5 = std::make_pair( 2, 1 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );
  mines.insert( mineCoord4 );
  mines.insert( mineCoord5 );

  // Create expected suggestions
  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord3, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord4, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord5, 'r' ) );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::fiveBrown ).empty() );

  game.leftClickCell( std::make_pair( 2, 2 ) );
  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::fiveBrown ).empty() );

  game.leftClickCell( std::make_pair( 1, 1 ) );
  game.leftClickCell( std::make_pair( 3, 1 ) );
  game.leftClickCell( std::make_pair( 2, 3 ) );
  ASSERT_FALSE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::fiveBrown ).empty() );

  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::fiveBrown ), expectedSuggestions );
}

TEST( Interface, getRightClicksSuggestionsBasedOnState_NoMarked_6 )
{
  //  *  *  2  1  _
  //  *  6  *  2  _
  //  *  4  *  2  _
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 1, 2 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 2 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord4 = std::make_pair( 1, 3 );
  minesweeperGame::coordinate mineCoord5 = std::make_pair( 2, 1 );
  minesweeperGame::coordinate mineCoord6 = std::make_pair( 1, 1 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );
  mines.insert( mineCoord4 );
  mines.insert( mineCoord5 );
  mines.insert( mineCoord6 );

  // Create expected suggestions
  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord3, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord4, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord5, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord6, 'r' ) );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::sixTeal ).empty() );

  game.leftClickCell( std::make_pair( 2, 2 ) );
  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::sixTeal ).empty() );

  game.leftClickCell( std::make_pair( 3, 1 ) );
  game.leftClickCell( std::make_pair( 2, 3 ) );
  ASSERT_FALSE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::sixTeal ).empty() );

  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::sixTeal ), expectedSuggestions );
}

TEST( Interface, getRightClicksSuggestionsBasedOnState_NoMarked_7 )
{
  //  *  *  2  1  _
  //  *  7  *  2  _
  //  *  *  *  2  _
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 1, 2 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 2 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord4 = std::make_pair( 1, 3 );
  minesweeperGame::coordinate mineCoord5 = std::make_pair( 2, 1 );
  minesweeperGame::coordinate mineCoord6 = std::make_pair( 1, 1 );
  minesweeperGame::coordinate mineCoord7 = std::make_pair( 2, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );
  mines.insert( mineCoord4 );
  mines.insert( mineCoord5 );
  mines.insert( mineCoord6 );
  mines.insert( mineCoord7 );

  // Create expected suggestions
  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord3, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord4, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord5, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord6, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord7, 'r' ) );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::sevenBlack ).empty() );

  game.leftClickCell( std::make_pair( 2, 2 ) );
  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::sevenBlack ).empty() );

  game.leftClickCell( std::make_pair( 3, 1 ) );
  ASSERT_FALSE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::sevenBlack ).empty() );

  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::sevenBlack ), expectedSuggestions );
}

TEST( Interface, getRightClicksSuggestionsBasedOnState_NoMarked_8 )
{
  //  *  *  *  2  _
  //  *  8  *  2  _
  //  *  *  *  2  _
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 1, 2 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 2 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord4 = std::make_pair( 1, 3 );
  minesweeperGame::coordinate mineCoord5 = std::make_pair( 2, 1 );
  minesweeperGame::coordinate mineCoord6 = std::make_pair( 1, 1 );
  minesweeperGame::coordinate mineCoord7 = std::make_pair( 2, 3 );
  minesweeperGame::coordinate mineCoord8 = std::make_pair( 3, 1 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );
  mines.insert( mineCoord4 );
  mines.insert( mineCoord5 );
  mines.insert( mineCoord6 );
  mines.insert( mineCoord7 );
  mines.insert( mineCoord8 );

  // Create expected suggestions
  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord3, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord4, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord5, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord6, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord7, 'r' ) );
  expectedSuggestions.insert( std::make_pair( mineCoord8, 'r' ) );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ).empty() );

  game.leftClickCell( std::make_pair( 2, 2 ) );
  ASSERT_FALSE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ).empty() );

  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );
}

TEST( Interface, getRightClicksSuggestionsBasedOnState_Marked )
{
  //  *  *  *  2  _
  //  *  8  *  2  _
  //  *  *  *  2  _
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 1, 2 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 2 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord4 = std::make_pair( 1, 3 );
  minesweeperGame::coordinate mineCoord5 = std::make_pair( 2, 1 );
  minesweeperGame::coordinate mineCoord6 = std::make_pair( 1, 1 );
  minesweeperGame::coordinate mineCoord7 = std::make_pair( 2, 3 );
  minesweeperGame::coordinate mineCoord8 = std::make_pair( 3, 1 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );
  mines.insert( mineCoord4 );
  mines.insert( mineCoord5 );
  mines.insert( mineCoord6 );
  mines.insert( mineCoord7 );
  mines.insert( mineCoord8 );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ).empty() );
  game.leftClickCell( std::make_pair( 2, 2 ) );
  game.rightClickCell( std::make_pair( 1, 1 ) );
  game.rightClickCell( std::make_pair( 1, 2 ) );
  game.rightClickCell( std::make_pair( 1, 3 ) );
  game.rightClickCell( std::make_pair( 2, 1 ) );
  game.rightClickCell( std::make_pair( 2, 3 ) );
  game.rightClickCell( std::make_pair( 3, 1 ) );
  game.rightClickCell( std::make_pair( 3, 2 ) );
  game.rightClickCell( std::make_pair( 3, 3 ) );
  ASSERT_TRUE( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ).empty() );

  expectedSuggestions.insert( std::make_pair( mineCoord1, 'r' ) );
  game.rightClickCell( std::make_pair( 1, 2 ) );
  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );

  expectedSuggestions.insert( std::make_pair( mineCoord2, 'r' ) );
  game.rightClickCell( std::make_pair( 3, 2 ) );
  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );

  expectedSuggestions.insert( std::make_pair( mineCoord3, 'r' ) );
  game.rightClickCell( std::make_pair( 3, 3 ) );
  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );

  expectedSuggestions.insert( std::make_pair( mineCoord4, 'r' ) );
  game.rightClickCell( std::make_pair( 1, 3 ) );
  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );

  expectedSuggestions.insert( std::make_pair( mineCoord5, 'r' ) );
  game.rightClickCell( std::make_pair( 2, 1 ) );
  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );

  expectedSuggestions.insert( std::make_pair( mineCoord6, 'r' ) );
  game.rightClickCell( std::make_pair( 1, 1 ) );
  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );

  expectedSuggestions.insert( std::make_pair( mineCoord7, 'r' ) );
  game.rightClickCell( std::make_pair( 2, 3 ) );
  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );

  expectedSuggestions.insert( std::make_pair( mineCoord8, 'r' ) );
  game.rightClickCell( std::make_pair( 3, 1 ) );
  ASSERT_EQ( minesweeperSolver::getRightClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::eightGrey ), expectedSuggestions );

}

TEST( Interface, getLeftClickSuggestion_1 )
{
  //  _  _  1  *  1
  //  _  1  2  3  2
  //  _  1  *  2  *
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 4, 1 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 5, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );

  minesweeperGame::ms_game game( board, mines );
  ASSERT_TRUE( minesweeperSolver::getLeftClickSuggestions( game ).empty() );

  game.leftClickCell( std::make_pair( 1, 1 ) );
  ASSERT_TRUE( minesweeperSolver::getLeftClickSuggestions( game ).empty() );

  game.rightClickCell( mineCoord1 );
  game.rightClickCell( mineCoord2 );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 4, 2 ), 'l' ) );
  ASSERT_EQ( minesweeperSolver::getLeftClickSuggestions( game ), expectedSuggestions );
}

TEST( Interface, getLeftClicksSuggestionsBasedOnState_1 )
{
  //  _  _  1  *  1
  //  _  1  2  3  2
  //  _  1  *  2  *
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 4, 1 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 5, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );

  minesweeperGame::ms_game game( board, mines );
  ASSERT_TRUE( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::oneBlue ).empty() );

  game.leftClickCell( std::make_pair( 1, 1 ) );
  ASSERT_TRUE( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::oneBlue ).empty() );

  game.rightClickCell( mineCoord1 );
  game.rightClickCell( mineCoord2 );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 4, 2 ), 'l' ) );
  //expectedSuggestions.insert( std::make_pair( std::make_pair( 4, 3 ), 'l' ) );
  ASSERT_EQ( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::oneBlue ), expectedSuggestions );
}

TEST( Interface, getLeftClicksSuggestionsBasedOnState_2 )
{
  //  _  _  1  *  1
  //  _  1  2  3  2
  //  _  1  *  2  *
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 4, 1 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 5, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );

  minesweeperGame::ms_game game( board, mines );
  ASSERT_TRUE( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::twoGreen ).empty() );

  game.leftClickCell( std::make_pair( 1, 1 ) );
  ASSERT_TRUE( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::twoGreen ).empty() );

  game.rightClickCell( mineCoord1 );
  game.rightClickCell( mineCoord2 );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 4, 2 ), 'l' ) );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 4, 3 ), 'l' ) );
  ASSERT_EQ( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::twoGreen ), expectedSuggestions );
}

TEST( Interface, getLeftClicksSuggestionsBasedOnState_3 )
{
  //  _  _  1  *  1
  //  _  1  2  3  2
  //  _  1  *  2  *
  int width = 5;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 4, 1 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 3 );
  minesweeperGame::coordinate mineCoord3 = std::make_pair( 5, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );
  mines.insert( mineCoord3 );

  minesweeperGame::ms_game game( board, mines );
  ASSERT_TRUE( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::threeRed ).empty() );

  game.leftClickCell( std::make_pair( 4, 2 ) );
  ASSERT_TRUE( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::threeRed ).empty() );

  game.rightClickCell( mineCoord1 );
  game.rightClickCell( mineCoord2 );
  ASSERT_TRUE( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::threeRed ).empty() );

  game.rightClickCell( mineCoord3 );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 3, 1 ), 'l' ) );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 5, 1 ), 'l' ) );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 3, 2 ), 'l' ) );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 5, 2 ), 'l' ) );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 4, 3 ), 'l' ) );
  ASSERT_EQ( minesweeperSolver::getLeftClicksSuggestionsBasedOnState( game, minesweeperGame::cellStateEnum::threeRed ), expectedSuggestions );
}

TEST( Interface, getLeftClickGambleSuggestions )
{
  //  _  1  *
  //  _  2  2
  //  _  1  *
  int width = 3;
  int height = 3;
  int boardSize = width * height;
  minesweeperGame::gameBoard board;
  minesweeperGame::mineField mines;
  minesweeperGame::coordinate mineCoord1 = std::make_pair( 3, 1 );
  minesweeperGame::coordinate mineCoord2 = std::make_pair( 3, 3 );
  minesweeperSolver::clickSuggestions expectedSuggestions;
  minesweeperSolver::clickSuggestions expectedSuggestionsAll;

  // Create board
  board.clear();
  for ( int row = 1; row <= height; row++ )
  {
    for ( int col = 1; col <= width; col++ )
    {
      board.insert( std::make_pair( std::make_pair( col, row ), minesweeperGame::cellStateEnum::unknown ) );
      expectedSuggestionsAll.insert( std::make_pair( std::make_pair( col, row ), 'l' ) );
    }
  }

  // Create mines
  mines.clear();
  mines.insert( mineCoord1 );
  mines.insert( mineCoord2 );

  minesweeperGame::ms_game game( board, mines );

  ASSERT_TRUE( minesweeperSolver::getRightClickSuggestions( game ).empty() );
  ASSERT_TRUE( minesweeperSolver::getLeftClickSuggestions( game ).empty() );
  ASSERT_EQ( minesweeperSolver::getLeftClickGambleSuggestions( game ), expectedSuggestionsAll );

  game.leftClickCell( std::make_pair( 1, 1 ) );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 3, 1 ), 'l' ) );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 3, 2 ), 'l' ) );
  expectedSuggestions.insert( std::make_pair( std::make_pair( 3, 3 ), 'l' ) );
  ASSERT_EQ( minesweeperSolver::getLeftClickGambleSuggestions( game ), expectedSuggestions );
}