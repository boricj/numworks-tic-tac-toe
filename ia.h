#ifndef TICTACTOE_IA_H
#define TICTACTOE_IA_H

#include "board.h"

namespace Tictactoe {

int playIA(const Board & board, Board::CellState iaColor, int difficulty, int & playX, int & playY);

}

#endif
