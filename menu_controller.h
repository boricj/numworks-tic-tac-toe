#ifndef TICTACTOE_MENU_CONTROLLER_H
#define TICTACTOE_MENU_CONTROLLER_H

#include <escher.h>
#include "board.h"
#include "board_controller.h"

namespace Tictactoe {

class MenuController : public ViewController, public SimpleListViewDataSource, public SelectableTableViewDataSource {
public:
  MenuController(Responder * parentResponder);
  View * view() override;
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  int numberOfRows() override;
  KDCoordinate cellHeight() override;
  HighlightCell * reusableCell(int index) override;
  int reusableCellCount() override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  StackViewController * stackController();
private:
  constexpr static int k_totalNumberOfCells = 2;
  MessageTableCell m_cells[k_totalNumberOfCells];
  SelectableTableView m_selectableTableView;
  Board m_board;
  BoardController m_boardController;
};

}

#endif
