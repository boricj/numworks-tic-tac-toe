#include "board_controller.h"

#include <memory>
extern "C" {
#include <assert.h>
}

#include "../apps_container.h"

namespace Tictactoe {

BoardController::BoardController(Responder * parentResponder, Board & board):
  ViewController(parentResponder),
  m_board(board),
  m_cells(new BoardCell*[board.width()*board.height()]),
  m_selectableTableView(this, this, 0, 1, Metric::CommonTopMargin, Metric::CommonRightMargin, Metric::CommonBottomMargin, Metric::CommonLeftMargin, this)
{
  for (int y = 0; y < m_board.height(); y++) {
    for (int x = 0; x < m_board.width(); x++) {
      m_cells[y*m_board.width()+x] = new BoardCell(m_board.get(x, y));
    }
  }
}

BoardController::~BoardController() {
  for (int y = 0; y < m_board.height(); y++) {
    for (int x = 0; x < m_board.width(); x++) {
      delete m_cells[y*m_board.width()+x];
    }
  }
  delete[] m_cells;
}

bool BoardController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    m_board.place(selectedColumn(), selectedRow());
    m_selectableTableView.reloadData();
    return true;
  }
  return false;
}

void BoardController::didBecomeFirstResponder() {
  if (selectedRow() == -1) {
    selectCellAtLocation(0, 0);
  } else {
    selectCellAtLocation(selectedColumn(), selectedRow());
  }
  
  app()->setFirstResponder(&m_selectableTableView);
}

void BoardController::viewWillAppear() {
}

View * BoardController::view() {
  return &m_selectableTableView;
}

int BoardController::numberOfRows() {
  return m_board.height();
}

int BoardController::numberOfColumns() {
  return m_board.width();
}

KDCoordinate BoardController::cellHeight() {
  return 32;
}

KDCoordinate BoardController::cellWidth() {
  return 32;
}

HighlightCell * BoardController::reusableCell(int index) {
  return m_cells[index];
}

int BoardController::reusableCellCount() {
  return m_board.width() * m_board.height();
}

}
