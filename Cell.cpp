#include "Cell.h"

Cell::Cell(Point center, int w, int h) : r(center, w, h, FL_BLACK, FL_WHITE) {} 

/*-------------------------------
La methode draw de Cell permet de dessiner tous les objet selon leur type,
on a utilisé un switch pour mieux differencier les differents element (joueur, mur, case, objectif, portal)

-----------------------------------*/

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

  case PLAYER:
    r.setFillColor(FL_DARK_YELLOW);
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
