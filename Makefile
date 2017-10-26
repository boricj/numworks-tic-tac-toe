snapshots += Tictactoe::App::Snapshot
snapshot_headers += apps/tic_tac_toe/app.h

app_objs += $(addprefix apps/tic_tac_toe/,\
  app.o\
  menu_controller.o\
)

i18n_files += $(addprefix apps/tic_tac_toe/,\
  base.en.i18n\
)

app_images += apps/tic_tac_toe/tictactoe_icon.png
