#include "board.h"

extern "C" {
#include <assert.h>
}

namespace Tictactoe {
  Board::Board(int m, int n, int k) : m_m(m), m_n(n), m_k(k) {
    assert(m > 0);
    assert(n > 0);
    assert(k > 0);
    
    m_cells = new Board::CellState[width()*height()];
    for (int i = 0; i < width()*height(); i++) {
      m_cells[i] = Board::CellState::Empty;
    }
    m_playerTurn = Board::CellState::Red;
  }

  Board::~Board() {
    delete[] m_cells;
  }

  const Board::CellState & Board::get(int x, int y) const {
    static Board::CellState empty = Board::CellState::Empty;

    if (x < 0 || y < 0 || x >= width() || y >= height()) {
      return empty;
    }

    return m_cells[y*width()+x];
  }

  bool Board::place(int x, int y) {
    if (m_playerTurn == Board::CellState::Empty) {
      return false;
    }
    if (x < 0 || y < 0 || x >= width() || y >= height()) {
      return false;
    }
    if (m_cells[y*width()+x] != Board::CellState::Empty) {
      return false;
    }

    m_cells[y*width()+x] = m_playerTurn;
    if (m_playerTurn == Board::CellState::Blue) {
      m_playerTurn = Board::CellState::Red;
    }
    else if (m_playerTurn == Board::CellState::Red) {
      m_playerTurn = Board::CellState::Blue;
    }
    return true;
  }

  Board::CellState Board::playerTurn() const {
    return m_playerTurn;
  }

}
