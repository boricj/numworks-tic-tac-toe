#include "app.h"
#include "apps/apps_container.h"
#include "tictactoe_icon.h"
#include "apps/i18n.h"
#include <assert.h>

namespace Tictactoe {

I18n::Message App::Descriptor::name() {
  return I18n::Message::TicTacToeApp;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::TicTacToeAppCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::TictactoeIcon;
}

App::Snapshot::Snapshot()
{
}

App * App::Snapshot::unpack(Container * container) {
  return new App(container, this);
}

App::Descriptor * App::Snapshot::descriptor() {
  static Descriptor descriptor;
  return &descriptor;
}

void App::Snapshot::reset() {
}

App::App(Container * container, Snapshot * snapshot) :
  ::App(container, snapshot, &m_boardController),
  m_board(3, 3, 3),
  m_boardController(this, m_board)
{
}

}
