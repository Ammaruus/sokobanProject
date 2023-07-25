
// These should include everything you might use
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include "Constant.hpp"
#include "Point.hpp"

#include "Cell.hpp"

using namespace std;




class Canvas {
  vector<Cell> cells;
 public:
  //Canvas();
  Canvas(const std::vector<std::vector<char>>& map);
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int /*keyCode*/) {
    exit(0);
  }
};

/*
Canvas::Canvas() {
  for (int i = 0; i < 100; i++)
    cells.push_back(Cell{Point{50*(i%10)+25, 50*(i/10)+25}, 50, 50});
// You could also write:
//  cells.push_back({Point{50*(i%10)+25, 50*(i/10)+25}, 40, 40});
//  cells.push_back({{50*(i%10)+25,50*(i/10)+25},40,40});
}*/
Canvas::Canvas(const std::vector<std::vector<char>>& map) {
    int cellSize = 50; // Taille de chaque cellule
    int numRows = map.size();
    int numCols = map[0].size();

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            char c = map[i][j];
            Point center(cellSize * j + cellSize / 2, cellSize * i + cellSize / 2);

            switch (c) {
                case '#': // Mur
                    cells.push_back(Cell(center, cellSize, cellSize));
                    cells.back().setWall();
                    break;
                case 'B': // Boite
                    cells.push_back(Cell(center, cellSize, cellSize));
                    cells.back().setBox();
                    break;
                case 'P': // Personnage
                    cells.push_back(Cell(center, cellSize, cellSize));
                    cells.back().setPlayer();
                    break;
                case 'X': // Objectif
                    cells.push_back(Cell(center, cellSize, cellSize));
                    cells.back().setTarget();
                    break;
                case ' ': // Case vide
                    cells.push_back(Cell(center, cellSize, cellSize));
                    break;
                // Ajoutez des cas pour les autres caractères (personnage, boîte, cible) si nécessaire
                default:
                    break;
            }
        }
    }
}

void Canvas::draw() {
  for (auto &c:cells) c.draw();
}
void Canvas::mouseMove(Point mouseLoc) {
  for (auto &c:cells) c.mouseMove(mouseLoc);
}
void Canvas::mouseClick(Point mouseLoc) {
  for (auto &c:cells) c.mouseClick(mouseLoc);
}

/* ------ DO NOT EDIT BELOW HERE (FOR NOW) ------ */
class MainWindow : public Fl_Window {
  std::vector<std::vector<char>> map = {
        {'#', '#', '#', '#', '#'},
        {'#', 'P', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#'},
        {'#', '#', ' ', '#', '#'},
        {'#', 'B', ' ', ' ', '#'},
        {'#', ' ', '#', 'X', '#'},
        {'#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#'},
        
    };

  Canvas canvas; 

 public:
  MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Sokoban"), canvas(map) {
    Fl::add_timeout(1.0/refreshPerSecond, Timer_CB, this);
    resizable(this);
  }
  void draw() override {
    Fl_Window::draw();
    canvas.draw();
  }
  int handle(int event) override {
    switch (event) {
      case FL_MOVE:
        canvas.mouseMove(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_PUSH:
        canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_KEYDOWN:
        canvas.keyPressed(Fl::event_key());
        return 1;
    }
    return 0;
  }
  static void Timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow*>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0/refreshPerSecond, Timer_CB, userdata);
  }
};

int main(int argc, char *argv[]) {
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
}