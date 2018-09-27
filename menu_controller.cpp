#include "menu_controller.h"
#include "../i18n.h"
#include "../shared/poincare_helpers.h"
#include <assert.h>

using namespace Poincare;

namespace Tictactoe {

MenuController::MenuController(Responder * parentResponder) :
  ViewController(parentResponder),
  m_editableCellWidth(&m_selectableTableView, this, m_draftTextBuffer),
  m_editableCellHeight(&m_selectableTableView, this, m_draftTextBuffer),
  m_editableCellWinCondition(&m_selectableTableView, this, m_draftTextBuffer),
  m_editableCellIALevel(&m_selectableTableView, this, m_draftTextBuffer),
  m_selectableTableView(this),
  m_board(new Board(3, 3, 3)),
  m_boardController(&m_selectableTableView, m_board, 6)
{
}

MenuController::~MenuController()
{
  delete m_board;
}

View * MenuController::view() {
  return &m_selectableTableView;
}

void MenuController::didBecomeFirstResponder() {
  m_selectableTableView.selectCellAtLocation(0, 0);
  app()->setFirstResponder(&m_selectableTableView);
}

bool MenuController::handleEvent(Ion::Events::Event event) {
  /*ViewController * vc[2] = {&m_editorController, &m_executorController};*/
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    if (selectedRow() == 0) {
      stackController()->push(&m_boardController);
    }
    return true;
  }
  return false;
}

int MenuController::numberOfRows() {
  return 5;
};

HighlightCell * MenuController::reusableCell(int index, int type) {
  switch (type)
  {
    case 0: return &m_cellNewGame;
    case 2:
    switch (index)
    {
      case 0: return &m_editableCellWidth;
      case 1: return &m_editableCellHeight;
      case 2: return &m_editableCellWinCondition;
      case 3: return &m_editableCellIALevel;
    }
  }
  assert(false);
  return nullptr;
}

int MenuController::reusableCellCount(int type) {
  switch (type)
  {
    case 0: return 1;
    case 2: return 4;
    default: return 0;
  }
}


int MenuController::typeAtLocation(int i, int j) {
  if (j == 1 || j == 2 || j == 3 || j == 4) {
    return 2;
  }
  return 0;
}

KDCoordinate MenuController::rowHeight(int j) {
  return Metric::ParameterCellHeight;
}

KDCoordinate MenuController::cumulatedHeightFromIndex(int j) {
  return rowHeight(0) * j;
}

int MenuController::indexFromCumulatedHeight(KDCoordinate offsetY) {
  KDCoordinate height = rowHeight(0);
  if (height == 0) {
    return 0;
  }
  return (offsetY - 1) / height;
}


void MenuController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  char buffer[3];
  MessageTableCell * myCell = (MessageTableCell *)cell;
  I18n::Message titles[] = {m_board->turnCount() ? I18n::Message::TicTacToeResumeGame : I18n::Message::TicTacToeNewGame, I18n::Message::TicTacToeBoardWidth, I18n::Message::TicTacToeBoardHeight, I18n::Message::TicTacToeConsecutiveStones, I18n::Message::TicTacToeIALevel};
  myCell->setMessage(titles[index]);
    
  switch (index)
  {
    case 1:
      Integer(m_board->width()).serialize(buffer, 3);
      ((MessageTableCellWithEditableText*)myCell)->setAccessoryText(buffer);
      break;
    case 2:
      Integer(m_board->height()).serialize(buffer, 3);
      ((MessageTableCellWithEditableText*)myCell)->setAccessoryText(buffer);
      break;
    case 3:
      Integer(m_board->winCondition()).serialize(buffer, 3);
      ((MessageTableCellWithEditableText*)myCell)->setAccessoryText(buffer);
      break;
    case 4:
      Integer(m_boardController.iaLevel()).serialize(buffer, 3);
      ((MessageTableCellWithEditableText*)myCell)->setAccessoryText(buffer);
      break;
  }
}

bool MenuController::textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) {
  return TextFieldDelegate::textFieldShouldFinishEditing(textField, event);
}

bool MenuController::textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) {
  Context * globalContext = textFieldDelegateApp()->localContext();
  float floatBody = Shared::PoincareHelpers::ApproximateToScalar<float>(text, *globalContext);
  if (std::isnan(floatBody) || std::isinf(floatBody)) {
    floatBody = 3;
  }

  int width = m_board->width();
  int height = m_board->height();
  int win = m_board->winCondition();
  int iaLevel = m_boardController.iaLevel();

  switch(selectedRow())
  {
  case 1:
    width = max(min(std::round(floatBody), 10), 2);
    break;
  case 2:
    height = max(min(std::round(floatBody), 7), 2);
    break;
  case 3:
    win = max(min(std::round(floatBody), 10), 2);
    break;
  case 4:
    iaLevel = max(min(std::round(floatBody), width*height*2), 0);
    break;
  }

  win = win > width ? width : win;
  win = win > height ? height : win;

  uint64_t complexity = 1;
  for (int i = 1; i <= iaLevel; i++)
  {
    complexity *= width * height - i;
    if (complexity > 360360) {
      iaLevel = i-1;
      break;
    }
  }

  delete m_board;
  m_board = new Board(width, height, win);
  m_boardController.setBoard(m_board, iaLevel);

  m_selectableTableView.reloadCellAtLocation(0, selectedRow());
  m_selectableTableView.reloadCellAtLocation(0, 0);
  m_selectableTableView.reloadCellAtLocation(0, 3);
  m_selectableTableView.reloadCellAtLocation(0, 4);
  if (event == Ion::Events::Up || event == Ion::Events::OK) {
    m_selectableTableView.handleEvent(event);
  }
  return true;
}


StackViewController * MenuController::stackController() {
  return static_cast<StackViewController *>(parentResponder());
}

Shared::TextFieldDelegateApp * MenuController::textFieldDelegateApp() {
  return (Shared::TextFieldDelegateApp *)app();
}

void MenuController::viewWillAppear()
{
  m_selectableTableView.reloadCellAtLocation(0, 0);
}

}
