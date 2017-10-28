#include "board_cell.h"
#include <assert.h>

#include <cmath>

namespace Tictactoe {

BoardCell::BoardCell(const Board::CellState & cellState) : m_cellState(cellState)
{
}

void BoardCell::drawRect(KDContext * ctx, KDRect rect) const {
  KDColor color, outerColor;

  switch (m_cellState) {
    case Board::CellState::Empty:
      color = KDColorWhite;
      break;
    case Board::CellState::Red:
      color = KDColorRed;
      break;
    case Board::CellState::Blue:
      color = KDColorBlue;
      break;
  }

  outerColor = isHighlighted() ? Palette::GreyDark : Palette::GreyBright;

  /* Draw border */
  ctx->fillRect(KDRect(0, 0, bounds().width(), 2), outerColor);
  ctx->fillRect(KDRect(0, bounds().height()-2, bounds().width(), 2), outerColor);
  ctx->fillRect(KDRect(0,0, 2, bounds().height()), outerColor);
  ctx->fillRect(KDRect(bounds().width()-2, 0, 2, bounds().height()), outerColor);

  
  ctx->fillRect(KDRect(2, 2, bounds().width()-4, bounds().height()-4), KDColorWhite);
  if (m_cellState == Board::CellState::Red) {
    drawCross(ctx);
  }
  else if (m_cellState == Board::CellState::Blue) {
    drawCircle(ctx);
  }
  //ctx->fillRect(KDRect(bounds().width()/4, bounds().height()/4, bounds().width()/2, bounds().height()/2), color);
}

void BoardCell::drawCross(KDContext * ctx) const {
  const uint8_t stampMask[3*3] = {
    0x7A, 0x0C, 0x7A,
    0x0C, 0x00, 0x0C,
    0x7A, 0x0C, 0x7A
  };
  KDPoint startPoints[] =
  {
    KDPoint(bounds().width()/4, bounds().height()/4),
    KDPoint(3*bounds().width()/4, bounds().height()/4),
  } ;
  KDPoint incs[] =
  {
    KDPoint(1, 1),
    KDPoint(-1, 1)
  } ;
  KDColor workingBuffer[3*3];

  /* Draw each line */
  for (int i = 0; i < 2; i++) {
    KDPoint stampLocation = startPoints[i];

    /* Stamp the line */
    for (int j = 0; j < bounds().width()/2+1; j++) {
      KDRect stampRect(stampLocation.x()-1, stampLocation.y()-1, 3, 3);
      ctx->blendRectWithMask(stampRect, KDColorRed, stampMask, workingBuffer);

      stampLocation = stampLocation.translatedBy(incs[i]);
    }
  }
}


void BoardCell::drawCircle(KDContext * ctx) const {
  constexpr int stampSize = 4;
  const uint8_t stampMask[stampSize+1][stampSize+1] = {
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0x7A, 0x0C, 0x7A, 0xFF},
    {0xFF, 0x0C, 0x00, 0x0C, 0xFF},
    {0xFF, 0x7A, 0x0C, 0x7A, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  };

  uint8_t shiftedMask[stampSize][stampSize];
  KDColor workingBuffer[stampSize*stampSize];

  for (float i = 0; i < 2*M_PI; i += (2*M_PI)/bounds().width()) {
    float pxf = bounds().width()/2 + sin(i)*bounds().width()/4 - 1;
    float pyf = bounds().height()/2 + cos(i)*bounds().height()/4 - 1;
    float dx = pxf - std::floor(pxf);
    float dy = pyf - std::floor(pyf);

    for (int i=0; i<stampSize; i++) {
      for (int j=0; j<stampSize; j++) {
        shiftedMask[i][j] = dx * (stampMask[i][j]*dy+stampMask[i+1][j]*(1.0f-dy))
          + (1.0f-dx) * (stampMask[i][j+1]*dy + stampMask[i+1][j+1]*(1.0f-dy));
      }
    }

    KDRect stampRect(pxf, pyf, 4, 4);
    ctx->blendRectWithMask(stampRect, KDColorBlue, (const uint8_t *)shiftedMask, workingBuffer);
  }
}

}
