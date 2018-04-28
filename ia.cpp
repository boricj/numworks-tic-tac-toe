#include "ia.h"

#include <limits.h>
#include <stdlib.h>

namespace Tictactoe {
  int playIA(const Board & board, Board::CellState iaColor, int difficulty, int & playX, int & playY) {
    if (board.winner() != Board::CellState::Empty)
    {
      int score = 1 + board.width() * board.height() - board.turnCount();
      if (board.winner() != iaColor) {
        score *= -1;
      }
      return score;
    }

    if (difficulty == 0 || board.playerTurn() == Board::CellState::Empty) {
      return 0;
    }

    Board myBoard(board);
    int bestScore = board.playerTurn() == iaColor ? -1000000 : 1000000;
    int bestX = -1, bestY = -1;

    for (int y = 0; y < board.height(); y++) {
      for (int x = 0; x < board.width(); x++) {
        if (myBoard.place(x, y)) {
          int curX, curY;
          int score = playIA(myBoard, iaColor, difficulty-1, curX, curY);

          if ((board.playerTurn() == iaColor && score > bestScore) ||
              (board.playerTurn() != iaColor && score < bestScore)) {
            bestX = x;
            bestY = y;
            bestScore = score;
          }
          myBoard.cancelPlace(x, y, board.playerTurn());
        }
      }
    }

    playX = bestX;
    playY = bestY;
    return bestScore;
  }
}
