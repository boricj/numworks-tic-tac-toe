#include "board.h"

extern "C" {
#include <assert.h>
}

namespace Tictactoe {
  Board::Board(int m, int n, int k) : m_m(m), m_n(n), m_k(k), m_turnCount(0) {
    assert(m > 0);
    assert(n > 0);
    assert(k > 0);

    m_cells = new Board::CellState[width()*height()];
    for (int i = 0; i < width()*height(); i++) {
      m_cells[i] = Board::CellState::Empty;
    }
    m_playerTurn = Board::CellState::Red;
    m_winner = Board::CellState::Empty;
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

    m_winner = checkWinner();
    if (m_winner != Board::CellState::Empty || (++m_turnCount == width() * height())) {
      m_playerTurn = Board::CellState::Empty;
    }

    return true;
  }

  Board::CellState Board::playerTurn() const {
    return m_playerTurn;
  }

  int Board::turnCount() const
  {
    return m_turnCount;
  }

  Board::CellState Board::winner() const {
    return m_winner;
  }

  Board::CellState Board::checkWinner() const {
    /* Check horizontal */
    for (int y = 0; y < height(); y++) {
      int consecutiveRed = 0;
      int consecutiveBlue = 0;

      for (int x = 0; x < width(); x++) {
        switch (get(x, y)) {
          case Board::CellState::Empty:
            consecutiveRed = consecutiveBlue = 0;
            break;
          case Board::CellState::Red:
            consecutiveRed++;
            break;
          case Board::CellState::Blue:
            consecutiveBlue++;
            break;
        }

        if (consecutiveRed == m_k) {
          return Board::CellState::Red;
        }
        else if (consecutiveBlue == m_k) {
          return Board::CellState::Blue;
        }
      }
    }

    /* Check vertical */
    for (int x = 0; x < width(); x++) {
      int consecutiveRed = 0;
      int consecutiveBlue = 0;

      for (int y = 0; y < height(); y++) {
        switch (get(x, y)) {
          case Board::CellState::Empty:
            consecutiveRed = consecutiveBlue = 0;
            break;
          case Board::CellState::Red:
            consecutiveRed++;
            break;
          case Board::CellState::Blue:
            consecutiveBlue++;
            break;
        }

        if (consecutiveRed == m_k) {
          return Board::CellState::Red;
        }
        else if (consecutiveBlue == m_k) {
          return Board::CellState::Blue;
        }
      }
    }

    /* Check diagonals */
    for (int i = 0; i < width() - m_k + 1; i++) {
      int consecutiveRed = 0;
      int consecutiveBlue = 0;

      for (int j = 0; j < height(); j++) {
        switch (get(i+j, j)) {
          case Board::CellState::Empty:
            consecutiveRed = consecutiveBlue = 0;
            break;
          case Board::CellState::Red:
            consecutiveRed++;
            break;
          case Board::CellState::Blue:
            consecutiveBlue++;
            break;
        }

        if (consecutiveRed == m_k) {
          return Board::CellState::Red;
        }
        else if (consecutiveBlue == m_k) {
          return Board::CellState::Blue;
        }
      }
    }

    /* Check other diagonals */
    for (int i = 0; i < width() - m_k + 1; i++) {
      int consecutiveRed = 0;
      int consecutiveBlue = 0;

      for (int j = 0; j < height(); j++) {
        switch (get(i+j, height()-j-1)) {
          case Board::CellState::Empty:
            consecutiveRed = consecutiveBlue = 0;
            break;
          case Board::CellState::Red:
            consecutiveRed++;
            break;
          case Board::CellState::Blue:
            consecutiveBlue++;
            break;
        }

        if (consecutiveRed == m_k) {
          return Board::CellState::Red;
        }
        else if (consecutiveBlue == m_k) {
          return Board::CellState::Blue;
        }
      }
    }

    return Board::CellState::Empty;
  }

}
