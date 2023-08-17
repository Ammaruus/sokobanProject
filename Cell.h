#ifndef __CELL_H
#define __CELL_H

#include "Point.h"
#include "Rectangle.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <vector>
/*--------------------------------------------------

Cell class.

The Board class below will have cells as instance
vrariables and call the methods of Cell
--------------------------------------------------*/

class Cell {
 // TODO supprimer si pas de classe héritée + tard
  Rectangle r;
  Point position;
  vector<Cell *> neighbors;
  bool portal = false;
  int portalId = -1;
  int type;

public:
  // Constructor
  Cell(Point center, int w, int h);

  // Methods that draw and handle events
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);

  // Used to initalize neighbors after all cells are created
  void setPosition(Point newPosition) { position = newPosition; }
  Point getPosition() { return position; }
  bool isObjective = False; //TODO mettre en attribut ( dans protected ) et faire getter/setter
  void setNeighbors(const vector<Cell *> newNeighbors) {
    neighbors = newNeighbors;
  }
  const vector<Cell *> getNeighbors() { //permet d'accéder aux voisins de chaque cell (à appeler QUE après
  //                                      que Board::initialize() soit exécuté)
    return neighbors;
  }
  void setType(int newType) { type = newType; }
  int getType() { return type; }
  void setPortal(bool newSet){ portal = newSet;}
  bool isPortal() {return portal;}
  void setPortalID(int newPortalId){portalId = newPortalId;}
  int getPortalID(){return portalId;}

};

#endif //__CELL_H