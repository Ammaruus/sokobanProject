#include "Cell.h"

Cell::Cell(Point center, int w, int h) : r(center, w, h, FL_BLACK, FL_WHITE) {} //? à déterminer

void Cell::draw() {
  switch (type) {
  case PATH:
    r.setFillColor(FL_WHITE);
    r.draw();
    break;

  case WALL:
    r.setFillColor(fl_rgb_color(94, 94, 94));
    r.draw();
    break;

  case BOX:
    r.setFillColor(fl_rgb_color(115, 74, 18));
    r.draw();
    break;

  case PORTAL:

    r.setFillColor(fl_rgb_color(0,204,0));
    r.setFrameColor(FL_WHITE);
    r.draw();
    r.drawstripes();

  case PLAYER:
  if (isPortal()){
    r.setFillColor(fl_rgb_color(0,204,0));
  }else {
    r.setFillColor(FL_DARK_YELLOW);
  }
    r.draw();
    break;
  case OBJECTIVE:
    r.setFillColor(	fl_rgb_color(210,180,140));
    r.draw();
    break;
  }
}

void Cell::mouseMove(Point mouseLoc) {}

void Cell::mouseClick(Point mouseLoc) {}
