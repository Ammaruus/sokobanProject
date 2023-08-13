#ifndef __BOARD_H
#define __BOARD_H

#include "Point.h"
#include "Cell.h"
#include "text.h"

/*--------------------------------------------------

Board class.

One instance of the board class is made by the
MainWindow class.

The fltk system via MainWindow calls:

draw 60 times a second
mouseMove whenever the mouse is moved
mouseClick whenever the mouse is clicked
keyPressed whenever a key is pressed

Any drawing code should be called ONLY in draw
or methods called by draw. If you try to draw
elsewhere it will probably crash.
--------------------------------------------------*/

class Board {

  vector<vector<Cell>> cells;
  vector<Cell *> neighbors(int x, int y); 
  Text textYouWin{"Gagné", {190, 150}, 90, fl_rgb_color(0, 255, 0)};
  Text textYouLose{"Perdu", {190, 150}, 90, fl_rgb_color(255, 0, 0)};
  Text intro {"Sokoban, created by Amine et Ammar", {210, 150}, 20, fl_rgb_color(0,0,0)}; 
  unsigned int counter = 0;
  unsigned int gamesHighScore = 0;
  unsigned int steps = 0;
  unsigned int stepsLimit = 10;

  Cell* playerCell;

  void initialize();


public:
  Board() { initialize();}
  
  void draw();

  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  void updateAllNeighbors();
  void updateCellNeighbors(Cell* cell);
  bool areNeighbors(Cell* c1, Cell* c2);
  
  bool isInBoard(Point newppos);
  void displayintro();

  bool isvalidplayermove(Point destination);
  void playermove(Point destination);

  void move(Point vecteur);

  bool isGameOver(); 
  bool isValidBoxmove(Point newppos, Point vecteur);
  void playerBoxmove(Point newppos, Point vecteur);

  void initHighscore();
  void resetHighscore();
  void setHighscore(unsigned int newHighscore);
  
  bool isStepsLimitPassed() const;
};

#endif //__BOARD_H