#if !defined(MINESWEEPER_GAME_H)
#define MINESWEEPER_GAME_H
#include <cstdint>
#include <map>
#include <set>

namespace minesweeperGame
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
    bool isGameBoardRevealed() const;
    void revealAllMines();
    void revealCell( coordinate );
    bool isMine( coordinate ) const;
    int getNumberOfNeighboringMines( const coordinate );
    void setGameLost( const coordinate );
    void setGameWon();
    void activeCell( coordinate );
    void generateBoard( const uint8_t, const uint8_t );
    void generateMines( const uint8_t, const uint8_t, const uint16_t );

  public:
    ms_game( uint8_t, uint8_t, uint16_t );
    ms_game( gameBoard, mineField );
    int getWidth() const;
    int getHeight() const;
    int getNumMines() const;
    gameBoard getBoard() const;
    void leftClickCell( coordinate );
    void rightClickCell( coordinate );
    bool isValidCoordinate( coordinate ) const;
    bool isGameActive() const;
    int getNumberOfNeighborsBasedOnState( coordinate, cellStateEnum );
    setOfCoordinates getNeighborCoordinatesBasedOnState( coordinate, cellStateEnum );
    setOfCoordinates getNeighborCoordinates( const coordinate );
    bool isCellRevealedAndHasNeighboringMines( coordinate );
    bool areTheNumberOfMarkedMinesEqualToCellValue( coordinate );
    setOfCoordinates getCoordinatesBasedOnState( cellStateEnum );
    int convertStateEnumToNumberOfMines( cellStateEnum );
  };
}  // namespace minesweeperGame

#endif // MINESWEEPER_GAME_H
