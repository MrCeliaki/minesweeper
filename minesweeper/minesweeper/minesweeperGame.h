#if !defined(MINESWEEPER_GAME_H)
#define MINESWEEPER_GAME_H
#include <stdint.h>
#include <map>
#include <set>


namespace minesweeper
{
  enum gameStateEnum
  {
    playing,
    lost,
    won
  };

  enum cellStateEnum
  {
    mineWhite,
    mineRed,
    marked,
    unknown,
    empty,
    oneBlue,
    twoGreen,
    threeRed,
    fourDarkBlue,
    fiveBrown,
    sixTeal,
    sevenBlack,
    eightGrey
  };

  typedef std::map<std::pair<int, int>, cellStateEnum> gameBoard;
  typedef std::set<std::pair<int, int>> mineField;

  class ms_game
  {
  private:
    ms_game();
    gameBoard board;
    mineField mines;
    gameStateEnum gameState;
    bool validBoard( uint8_t, uint8_t, uint16_t ) const;
    int width;
    int height;
    int numMines;
    bool gameBoardRevealed() const;
    void revealAllMines();
    void revealCell( std::pair<int, int> );
    bool isMine( std::pair<int, int> ) const;
    int numberOfNeighboringMines( const std::pair<int, int> );
    std::set<std::pair<int, int>> getNeighborCoordinates( const std::pair<int, int> );

  public:
    ms_game( uint8_t, uint8_t, uint16_t );
    int getWidth() const;
    int getHeight() const;
    int getNumMines() const;
    gameBoard getBoard() const;
    void leftClickCell( std::pair<int, int> );
    void rightClickCell( std::pair<int, int> );
    void generateBoard( gameBoard&, const uint8_t, const uint8_t );
    void generateMines( mineField&, const uint8_t, const uint8_t, const uint16_t );
    bool isValidCoordinate( std::pair<int, int> );

  };
}  // namespace grade_school

#endif // MINESWEEPER_GAME_H
