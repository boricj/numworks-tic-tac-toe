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
  ~Board();

  const CellState & get(int x, int y) const;
  bool place(int x, int y);
  CellState playerTurn() const;
  int turnCount() const;
  CellState winner() const;
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
