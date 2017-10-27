#ifndef TICTACTOE_BOARD_CONTROLLER_H
#define TICTACTOE_BOARD_CONTROLLER_H

#include <escher.h>
#include "board.h"
#include "board_cell.h"

namespace Tictactoe {

class BoardController : public ViewController, public SimpleTableViewDataSource, public SelectableTableViewDataSource, public SelectableTableViewDelegate {
public:
  BoardController(Responder * parentResponder, Board & board);
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
  /*void willDisplayCellAtLocation(HighlightCell * cell, int i, int j) override;
  void tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY) override;*/
private:
  Board & m_board;
  BoardCell ** m_cells;
  SelectableTableView m_selectableTableView;
};

}

#endif
