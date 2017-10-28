#ifndef TICTACTOE_BOARD_CELL_H
#define TICTACTOE_BOARD_CELL_H

#include <escher.h>
#include "board.h"

namespace Tictactoe {

class BoardCell : public HighlightCell {
public:
  BoardCell(const Board::CellState & cellState);
  void drawRect(KDContext * ctx, KDRect rect) const override;
private:
  void drawCross(KDContext * ctx) const;
  void drawCircle(KDContext * ctx) const;
  const Board::CellState & m_cellState;
};

}

#endif
