#ifndef TICTACTOE_MENU_CONTROLLER_H
#define TICTACTOE_MENU_CONTROLLER_H

#include <escher.h>
#include "board.h"
#include "board_controller.h"
#include "../shared/parameter_text_field_delegate.h"

namespace Tictactoe {

class MenuController : public ViewController, public ListViewDataSource, public SelectableTableViewDataSource, public Shared::ParameterTextFieldDelegate {
public:
  MenuController(Responder * parentResponder);
  ~MenuController();
  View * view() override;
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  int numberOfRows() override;
  HighlightCell * reusableCell(int index, int type) override;
  KDCoordinate rowHeight(int j) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;
  int reusableCellCount(int type) override;
  int typeAtLocation(int i, int j) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  bool textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) override;
  StackViewController * stackController();
  void viewWillAppear() override;
private:
  Shared::TextFieldDelegateApp * textFieldDelegateApp() override;
  char m_draftTextBuffer[MessageTableCellWithEditableText::k_bufferLength];
  MessageTableCell m_cellNewGame;
  MessageTableCellWithEditableText m_editableCellWidth;
  MessageTableCellWithEditableText m_editableCellHeight;
  MessageTableCellWithEditableText m_editableCellWinCondition;
  MessageTableCellWithEditableText m_editableCellIALevel;
  MessageTree * m_messageTreeModel;
  SelectableTableView m_selectableTableView;
  Board * m_board;
  BoardController m_boardController;
};

}

#endif
