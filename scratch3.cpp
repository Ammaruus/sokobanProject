#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <algorithm>
#include <array>
#include <bits/stdc++.h> //might be deleted
#include <chrono>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <time.h>
#include <vector>

#include "text.hpp"

using namespace std;

const int windowWidth = 500;
const int windowHeight = 500;
const double refreshPerSecond = 60;
const int PATH = 0;
const int WALL = 1;
const int BOX = 2;
const int PLAYER = 3;
const int OBJECTIVE = 4;

//! ATTENTION : séparation affichage et données

struct Point { // TODO ? transformer var globales en classes=>surcharger
               // opérateur + pour fct move
  int x, y;
};

vector<vector<int>> board{
    {1, 0, 0, 1}, 
    {1, 0, 2, 0}, 
    {1, 3, 0, 0},
    {1, 1, 1, 4}};
// TODO remplacer vect par classe for handling file to board conversion (and
//TODO     initialize ?...) ---> pas très urgent

/*--------------------------------------------------

Text class.

Use to display text on the screen. For example:

Text("Hello!", {250, 250}).draw();

will create a text temporary instance with the
string "Hello!" centered at 250, 250 and will
call draw on the temporary.
--------------------------------------------------*/

class Text {
  string s;
  Point center;
  int fontSize;
  Fl_Color color;

public:
  // Constructor
  Text(string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK)
      : s{s}, center{center}, fontSize{fontSize}, color{color} {}

  // Draw
  void draw();

  // Setters and getters
  string getString() { return s; }
  void setString(const string &newString) { s = newString; }
  int getFontSize() { return fontSize; }
  void setFontSize(int newFontSize) { fontSize = newFontSize; }
  Point getCenter() { return center; }
  void setCenter(Point newCenter) { center = newCenter; }
};

void Text::draw() {
  fl_color(color);
  fl_font(FL_HELVETICA, fontSize);
  int width, height;
  fl_measure(s.c_str(), width, height, false);
  fl_draw(s.c_str(), center.x - width / 2,
          center.y - fl_descent() + height / 2);
}

/*--------------------------------------------------

Rectangle class.

Use to display a fillend-in rectangle on the screen
with different colors for the fill and the border

It should have all the features you need and you
should not need to edit it.

--------------------------------------------------*/

class Rectangle {
  Point center;
  int w, h;
  Fl_Color fillColor, frameColor;

public:
  Rectangle(Point center, int w, int h, Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE);
  void draw();
  void setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor() { return fillColor; }
  void setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() { return frameColor; }
  void setWidth(int neww) { w = neww; }
  void setHeight(int newh) { h = newh; }
  int getWidth() { return w; }
  int getHeight() { return h; }
  bool contains(Point p);
  Point getCenter() { return center; }
};

Rectangle::Rectangle(Point center, int w, int h, Fl_Color frameColor,
                     Fl_Color fillColor)
    : center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor} {
}

void Rectangle::draw() {
  fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, fillColor);
  fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h,
              frameColor);
}

void Rectangle::setFillColor(Fl_Color newFillColor) {
  fillColor = newFillColor;
}

void Rectangle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}

bool Rectangle::contains(Point p) {
  return p.x >= center.x - w / 2 && p.x < center.x + w / 2 &&
         p.y >= center.y - h / 2 && p.y < center.y + h / 2;
}

/*--------------------------------------------------

Cell class.

The Board class below will have cells as instance
vraiables and call the methods of Cell
--------------------------------------------------*/

class Cell {
 // TODO supprimer si pas de classe héritée + tard
  Rectangle r;
  Point position;
  vector<Cell *> neighbors;
  
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

};

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
  vector<Cell *> neighbors(int x, int y); //? ?????
  Text textYouWin{"YOU WIN", {190, 150}, 90, fl_rgb_color(255,153,204)};
  Text intro {"SOKOBAN", {150, 150}, 50, fl_rgb_color(255,153,204)}; //! ne fonctionne pas
  unsigned int counter = 0;

  Cell* playerCell;
   
  //! 2 pointeurs vers un même objet = dangereux ? (probablement pas car mem statique)

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
  void playerBoxmove(Point newppos, Point vecteur); //TODO params non nécessaires (voir code flow of move())
};

void Board::displayintro(){
  
  }

bool Board::isGameOver(){
  for (auto &v : cells)
    for (auto &c : v) {
      if (c.isObjective && c.getType() != BOX) {
        return false;
      }
    }
  return true;
}

bool Board::isvalidplayermove(Point destination){
    return cells[destination.x][destination.y].getType() != WALL && cells[destination.x][destination.y].getType() != BOX;
} 

void Board::move(Point vecteur){
  Point playerCellPos = playerCell->getPosition();
  Point newppos = {playerCellPos.x + vecteur.x, playerCellPos.y + vecteur.y};
  if(isInBoard(newppos)) {
    if (areNeighbors(playerCell,&cells[newppos.x][newppos.y])) {
      if(isvalidplayermove(newppos)) { //TODO en faire une méthode (+ clair)
        playermove(newppos);
      }
      else if (cells[newppos.x][newppos.y].getType() == BOX) {
        cout <<"box pos before move:" << newppos.x << ' ' << newppos.y << endl;
        if (isValidBoxmove(newppos,vecteur)) { //TODO transformer param vecteur en position
        cout <<"valide !" << endl;
            playerBoxmove(newppos,vecteur); //TODO same here
            }
       }
    }
  }
}


//! are_Neighbors remplace is_in_board pour le cas de boxmove et playermove ! 
//TODO voir pourquoi isinboard ne fonctionne pas, sinon le supprimer (on peut s'en débrouiller sans mtn)

bool Board::areNeighbors(Cell* c1, Cell* c2){ //vérifie si c2 est dans la liste de neighbors de c1
  for (unsigned int i = 0; i < c1->getNeighbors().size() ; i++) {
    if (c1->getNeighbors()[i] == c2) {
        return true; 
    }
  }
  return false;
}

void Board::playerBoxmove(Point newppos, Point vecteur){
  playermove(newppos); //pass
  Point boxDest = {newppos.x + vecteur.x , newppos.y + vecteur.y};
  cells[boxDest.x][boxDest.y].setType(BOX);
}

bool Board::isValidBoxmove(Point newppos, Point vecteur){
  Point boxDest = {newppos.x + vecteur.x, newppos.y + vecteur.y};
 // cout <<"player pos" << playerCell->getPosition().x << ' ' <<playerCell->getPosition().y << endl; 
  //cout<< "box dest : " << boxDest.x << " , " << boxDest.y << endl;;
  //bool q1 = isInBoard(boxDest);
  //bool q2 = cells[boxDest.x][boxDest.y].getType() == PATH;
  //int typee= cells[boxDest.x][boxDest.y].getType();
  
  //cout << "in board: " << q1 << "valide : " << typee << endl;
  return  areNeighbors(&cells[newppos.x][newppos.y],&cells[boxDest.x][boxDest.y])
   && cells[boxDest.x][boxDest.y].getType() != WALL; //TODO répétition de code avec playermove
} 

void Board::initialize() {
  // This is called by the constructor but also by keyPressed to
  // reset whenver spacebar is called. (prof)

  // Until the last step when we needed to reset, this would be the constructor

  displayintro();
  cells.clear(); // Needed to remove the cells if we are starting again
  cout << "board size : " << board.size() << "cells size : " << cells.size()
       << endl;

  // cells initiation
  for (unsigned short x = 0; x < board.size(); x++) {
    cout << "cells size in prog.: " << cells.size() << endl;
    cells.push_back({});
    for (int y = 0; y < board.size(); y++) {
      cells[x].push_back({{50 * x + 25, 50 * y + 25}, 40, 40});
      cout << "working..." << x << ' ' << y << endl;
      cells[x][y].setPosition(
          {static_cast<int>(x), static_cast<int>(y)}); // coord matrice jamais -
      switch (board[y][x]) { //! PROBLEME : EST A L'ENVERS SI ON INVERSE X ET Y
      case PATH:
        cells[x][y].setType(PATH);
        break;

      case WALL:
        cells[x][y].setType(WALL);
        break;

      case BOX:
        cells[x][y].setType(BOX);
        break;

      case PLAYER:
        cells[x][y].setType(PLAYER);
        playerCell = &cells[x][y];
        break;
      case OBJECTIVE:
        cells[x][y].setType(OBJECTIVE);
        cells[x][y].isObjective = True;
        break;
      }
    }
  }
  updateAllNeighbors(); //TODO devrait être named 'createAllNeighbors'
  cout << "done !" << endl;
}

void Board::draw() { //TODO peut etre mettre displayboard dedans <<<
  counter += 1;
  if (counter < 80) {
    intro.draw();
  }
  else {
      if (isGameOver()) {
      textYouWin.draw();
    }
    else{
      for (auto &v : cells)
      for (auto &c : v) {
        c.draw();
      }
    }
  }
}



void Board::updateAllNeighbors() {
  // This computes the (pointers to) neighbors of each cell
  for (unsigned x = 0; x < cells.size(); x++)
    for (unsigned y = 0; y < cells.size(); y++) {
      updateCellNeighbors(&cells[x][y]);
    }
}



void Board::mouseMove(Point mouseLoc) {
  for (auto &v : cells)
    for (auto &c : v)
      c.mouseMove(mouseLoc);
}

void Board::mouseClick(Point mouseLoc) {
  // We only respond to mouse clicks if the game is not over/won (PROF demineur (not relevant ))

  for (auto &v : cells)
    for (auto &c : v)
      c.mouseClick(mouseLoc);
}

void Board::keyPressed(
    int keyCode) { // TODO possibly make an event or a FTLK specialized class

  switch (keyCode) {
  case ' ':
    initialize();
    break;
  case 'q':
    exit(0);
    break;
  case 'o':
    move({0, -1});
    break;
  case 'l':
    move({0, 1}); //! PROBLEME: up and down are be inverted (j'ai inversé les 2 vecteurs pr l'instant)
    break;
  case 'k':
    move({-1, 0});
    break;
  case 'm':
    move({1, 0});
    break;
  default: {
  } // pass
  }
  draw();
}



void Board::playermove(Point newppos) { //! param = nouvelle position (plus un vecteur)
  Point playerCellPos = playerCell->getPosition(); //TODO est répété dans move (mauvaise pratique)
  if (playerCell->isObjective) {
    playerCell->setType(OBJECTIVE);
  }
  else {playerCell->setType(PATH);}

  cells[newppos.x][newppos.y].setType(PLAYER);

  cout << "old : " << playerCellPos.x << ' ' << playerCellPos.y << endl;
  cout << "new : " << newppos.x << ' ' << newppos.y << endl;
  updateCellNeighbors(playerCell); //TODO regulièrement check if it's updating the right cell
  
  playerCell = &cells[newppos.x][newppos.y]; //TODO plus propre d'en faire une méthode setter
  //TODO                                    (pour une future classe TELEPORT qui manipulera aussi playerCell)
   // only error checking below (à ne pas changer car very useful)
  for (int i = 0; i < playerCell->getNeighbors().size();
       i++) {
    Point pos =
        playerCell->getNeighbors()[i]->getPosition();
    cout << "positions dispo :" << pos.x << ' ' << pos.y
         << endl; // working good
         }
  
}



bool Board::isInBoard(Point newppos){
 
  if (0 <= newppos.x < cells.size() && 0 <= newppos.y < cells.size()) {
    return true; //juste return ça
    }
  return false ;
}

void Board::updateCellNeighbors(Cell* cell){
  int x = cell->getPosition().x; //! might be USELESS ! check update on 16-11
  int y = cell->getPosition().y; 
  vector<Cell *> neighbors;
      for (auto &shift : vector<Point>({
               {-1, 0}, // The 4 neighbors relative to the cell
               {0, 1},
               {1, 0},
               {0, -1},
           })) {
        // check lower bounds
        if (!((x == 0 && shift.x == -1) || (y == 0 && shift.y == -1))) {
          unsigned neighborx =
              static_cast<unsigned>(static_cast<int>(x) + shift.x);
          unsigned neighbory =
              static_cast<unsigned>(static_cast<int>(y) + shift.y);
          // check upper bounds
          if (neighborx < cells.size() && neighbory < cells[neighborx].size()) { 
            neighbors.push_back(&cells[neighborx][neighbory]);
          }
        }
        cells[x][y].setNeighbors(
            neighbors); // TODO semi-question : ordre affichage cell (might not
                        //TODO                                            matter)
      }

}

// TODO make movement method (voir readme , partie OBJECTIF (tout en bas)

/*--------------------------------------------------

MainWindow class.

Do not edit!!!!

--------------------------------------------------*/

class MainWindow : public Fl_Window {
  Board board;
  

public:

  MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 3") {
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
  }

  void draw() override {
    Fl_Window::draw();
    board.draw();
  }
  
  int handle(int event) override {
    switch (event) {
    case FL_MOVE:
      board.mouseMove(Point{Fl::event_x(), Fl::event_y()});
      return 1;
    case FL_PUSH:
      board.mouseClick(Point{Fl::event_x(), Fl::event_y()});
      return 1;
    case FL_KEYDOWN:
      board.keyPressed(Fl::event_key());
      return 1;
    default:
      return 0;
    }
    return 0;
  }
  static void Timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
  }
};

/*--------------------------------------------------

main

Do not edit

--------------------------------------------------*/

int main(int argc, char *argv[]) {
  srand(static_cast<unsigned>(time(nullptr)));
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
  
}
