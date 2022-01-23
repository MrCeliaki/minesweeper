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
  typedef std::set<std::pair<int, int>> setOfCoordinates;
  typedef std::pair<int, int> coordinate;

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
    bool isGameBoardRevealed() const;
    void revealAllMines();
    void revealCell( coordinate );
    bool isMine( coordinate ) const;
    int getNumberOfNeighboringMines( const coordinate );
    setOfCoordinates getNeighborCoordinates( const coordinate );
    void setGameLost( const coordinate );
    void setGameWon();
    void activeCell( coordinate );
    bool isCellRevealedAndHasNeighboringMines( coordinate );
    bool areTheNumberOfMarkedMinesEqualToCellValue( coordinate );
    setOfCoordinates getNeighborCoordinatesBasedOnState( coordinate, cellStateEnum );
    int getNumberOfNeighborsBasedOnState( coordinate, cellStateEnum );

  public:
    ms_game( uint8_t, uint8_t, uint16_t );
    int getWidth() const;
    int getHeight() const;
    int getNumMines() const;
    gameBoard getBoard() const;
    void leftClickCell( coordinate );
    void rightClickCell( coordinate );
    void generateBoard( gameBoard&, const uint8_t, const uint8_t );
    void generateMines( mineField&, const uint8_t, const uint8_t, const uint16_t );
    bool isValidCoordinate( coordinate ) const;
    bool isGameActive() const;

  };
}  // namespace grade_school

#endif // MINESWEEPER_GAME_H
