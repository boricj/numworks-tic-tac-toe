#ifndef TICTACTOE_BOARD_CONTROLLER_H
#define TICTACTOE_BOARD_CONTROLLER_H

#include <escher.h>
#include "board.h"
#include "board_cell.h"

namespace Tictactoe {

class BoardController : public ViewController, public SimpleTableViewDataSource, public SelectableTableViewDataSource, public SelectableTableViewDelegate {
public:
  BoardController(Responder * parentResponder, Board * board, int iaLevel);
  ~BoardController();

  View * view() override;

  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  void viewWillAppear() override;

  virtual int numberOfRows() override;
  virtual int numberOfColumns() override;
  virtual KDCoordinate cellHeight() override;
  virtual KDCoordinate cellWidth() override;
  virtual HighlightCell * reusableCell(int index) override;
  virtual int reusableCellCount() override;
  void setBoard(Board * board, int iaLevel);
  int iaLevel() const { return m_iaLevel; }
private:
  Board * m_board;
  BoardCell ** m_cells;
  SelectableTableView m_selectableTableView;
  int m_width;
  int m_height;
  int m_iaLevel;
};

}

#endif
