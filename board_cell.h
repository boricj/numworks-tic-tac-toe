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
  const Board::CellState & m_cellState;
};

}

#endif
