#ifndef TICTACTOE_APP_H
#define TICTACTOE_APP_H

#include <escher.h>
#include "menu_controller.h"

namespace Tictactoe {

class App : public Shared::TextFieldDelegateApp {
public:
  class Descriptor : public ::App::Descriptor {
  public:
    I18n::Message name() override;
    I18n::Message upperName() override;
    const Image * icon() override;
  };
  class Snapshot : public ::App::Snapshot {
  public:
    Snapshot();
    App * unpack(Container * container) override;
    void reset() override;
    Descriptor * descriptor() override;
  };
private:
  App(Container * container, Snapshot * snapshot);
  MenuController m_menuController;
  StackViewController m_stackViewController;
};

}

#endif
