#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H

namespace Tictactoe {
  
class Board {
public:
  enum CellState {
    Empty,
    Red,
    Blue
  } ;

  Board(int m, int n, int k);
  Board(const Board & board);
  ~Board();

  const CellState & get(int x, int y) const;
  bool place(int x, int y);
  void cancelPlace(int x, int y, CellState previousPlayer);
  CellState playerTurn() const { return m_playerTurn; }
  int turnCount() const { return m_turnCount; }
  CellState winner() const { return m_winner; }
  int width() const { return m_m; }
  int height() const  { return m_n; }
  int winCondition() const { return m_k; }
private:
  CellState checkWinner() const;
  int m_m, m_n, m_k;
  CellState * m_cells;
  CellState m_playerTurn;
  CellState m_winner;
  int m_turnCount;
};

}

#endif
