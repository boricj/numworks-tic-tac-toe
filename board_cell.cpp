#include "board_cell.h"
#include <assert.h>

namespace Tictactoe {

BoardCell::BoardCell(const Board::CellState & cellState) : m_cellState(cellState)
{
}

void BoardCell::drawRect(KDContext * ctx, KDRect rect) const {
  KDColor color;

  switch (m_cellState) {
    case Board::CellState::Empty:
      color = KDColorWhite;
      break;
    case Board::CellState::Red:
      color = KDColorRed;
      break;
    case Board::CellState::Blue:
      color = KDColorBlue;
      break;
  }

  ctx->fillRect(KDRect(0, 0, bounds().width(), bounds().height()), isHighlighted() ? KDColorBlack : KDColorWhite);
  ctx->fillRect(KDRect(2, 2, bounds().width()-4, bounds().height()-4), color);
}

}
