#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <time.h>
#include <vector>

#include "Board.h"

using namespace std;



/*--------------------------------------------------

MainWindow class.

Do not edit!!!!

--------------------------------------------------*/

class MainWindow : public Fl_Window {
  Board board; ///instancier un objet board
  
public:

  MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Sokoban") {
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
