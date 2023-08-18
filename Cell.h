#ifndef __CELL_H
#define __CELL_H

#include "Point.h"
#include "Rectangle.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <vector>
/*--------------------------------------------------

Classe Cell

represente une cellule sur la map dessinée a l'ecran
--------------------------------------------------*/

class Cell {
  Rectangle r;
  Point position;
  vector<Cell *> neighbors;
  bool portal = false;
  int portalId = -1;
  int type; // permet de differencier le type des celle

public:
  // Constructor
  Cell(Point center, int w, int h);

  // Methode qui dessine et s'occupe des mouvement
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);

  // Getter et setter pour la position d'une case
  void setPosition(Point newPosition) { position = newPosition; }
  Point getPosition() { return position; }
  bool isObjective = False; 
  //permet d'initiliser les voisin d'une celulle apres la creation de cell-ci
  void setneighbors(const vector<Cell *> newneighbors) {
    neighbors = newneighbors;
  }
  //permet d'accéder aux voisins de chaque cellule
  const vector<Cell *> getneighbors() { 
    return neighbors;
  }
  // guetter et setter pour definir le type d'une celulle(joueur, mur, boite, cible, portal)
  void setType(int newType) { type = newType; }
  int getType() { return type; }
  
};

#endif //__CELL_H