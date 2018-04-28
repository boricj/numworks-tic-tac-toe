#include "board_controller.h"

extern "C" {
#include <assert.h>
}

#include "ia.h"
#include "../apps_container.h"

namespace Tictactoe {

BoardController::BoardController(Responder * parentResponder, Board * board, int iaLevel):
  ViewController(parentResponder),
  m_board(nullptr),
  m_cells(nullptr),
  m_selectableTableView(this, this, this, this)
{
  setBoard(board, iaLevel);
}

BoardController::~BoardController() {
  setBoard(nullptr, 0);
}

bool BoardController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    if (m_board->place(selectedColumn(), selectedRow()))
    {
      if (m_board->playerTurn() != Board::CellState::Empty && m_iaLevel)
      {
        int x, y;
        playIA(*m_board, Board::CellState::Blue, m_iaLevel, x, y);
        m_board->place(x, y);
        reusableCell(y * m_width + x)->reloadCell();
      }
      if (m_board->playerTurn() == Board::CellState::Empty)
      {
        I18n::Message msg;
        switch (m_board->winner())
        {
          case Board::CellState::Red:
            msg = I18n::Message::TicTacToeRedWins;
            break;
          case Board::CellState::Blue:
            msg = I18n::Message::TicTacToeBlueWins;
            break;
          default:
            msg = I18n::Message::TicTacToeStalemate;
            break;
        }
        app()->displayWarning(msg);
        return true;
      }
    }
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
  return m_board->height();
}

int BoardController::numberOfColumns() {
  return m_board->width();
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
  return m_board->width() * m_board->height();
}

void BoardController::setBoard(Board * board, int iaLevel) {
  if (m_cells) {
    for (int i = 0; i < m_height * m_width; i++) {
      delete m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;
  }
  m_board = board;
  m_iaLevel = iaLevel;
  if (board)
  {
    m_cells = new BoardCell*[m_board->width()*m_board->height()];
    
    for (int y = 0; y < m_board->height(); y++) {
      for (int x = 0; x < m_board->width(); x++) {
        m_cells[y*m_board->width()+x] = new BoardCell(m_board->get(x, y));
      }
    }

    m_width = m_board->width();
    m_height = m_board->height();

    m_selectableTableView.reloadData(false);
    m_selectableTableView.setMargins(0);
    m_selectableTableView.setShowsIndicators(false);
  }
}

}
