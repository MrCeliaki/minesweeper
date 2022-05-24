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

  using gameBoard = std::map<std::pair<int, int>, cellStateEnum>;
  using mineField = std::set<std::pair<int, int>>;
  using setOfBoardCoordinates = std::set<std::pair<int, int>>;
  using boardCoordinate = std::pair<int, int> ;

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
    void revealCell( boardCoordinate );
    bool isMine( boardCoordinate ) const;
    int getNumberOfNeighboringMines( const boardCoordinate );
    void setGameLost( const boardCoordinate );
    void setGameWon();
    void activeCell( boardCoordinate );
    void generateBoard( const uint8_t, const uint8_t );
    void generateMines( const uint8_t, const uint8_t, const uint16_t );

  public:
    ms_game( uint8_t, uint8_t, uint16_t );
    ms_game( gameBoard, mineField );
    int getWidth() const;
    int getHeight() const;
    int getNumMines() const;
    gameBoard getBoard() const;
    void leftClickCell( boardCoordinate );
    void rightClickCell( boardCoordinate );
    bool isValidCoordinate( boardCoordinate ) const;
    bool isGameActive() const;
    int getNumberOfNeighborsBasedOnState( boardCoordinate, cellStateEnum );
    setOfBoardCoordinates getNeighborCoordinatesBasedOnState( boardCoordinate, cellStateEnum );
    setOfBoardCoordinates getNeighborCoordinates( const boardCoordinate );
    bool isCellRevealedAndHasNeighboringMines( boardCoordinate );
    bool areTheNumberOfMarkedMinesEqualToCellValue( boardCoordinate );
    setOfBoardCoordinates getCoordinatesBasedOnState( cellStateEnum );
    int convertStateEnumToNumberOfMines( cellStateEnum );
  };
}  // namespace minesweeperGame

#endif // MINESWEEPER_GAME_H
