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
  Board* board = nullptr;
  bool inMenu = true;  // Nous commençons dans l'état du menu

public:
  MainWindow() : Fl_Window(500, 500, "Sokoban") {
    Fl::add_timeout(1.0 / 60, Timer_CB, this);  // En supposant un taux de rafraîchissement de 60 Hz pour plus de simplicité
    resizable(this);
  }

  ~MainWindow() {  // Destructeur
    delete board;  // Nettoyer la mémoire lorsque MainWindow est détruit
  }

  void draw() override {
    Fl_Window::draw();
    
    if (inMenu) {
      // Définit la couleur du texte et dessine le menu
      fl_color(FL_BLACK);  
      fl_draw("Appuyez sur 'a' pour le niveau 1", 140, 250);
      fl_draw("Appuyez sur 'b' pour le niveau 2", 140, 270);
    } else {
      board->draw();
    }
  }
  
  int handle(int event) override {
    switch (event) {
      case FL_MOVE:
        if (!inMenu && board) {
          board->mouseMove(Point{Fl::event_x(), Fl::event_y()});
        }
        return 1;
      case FL_PUSH:
        if (!inMenu && board) {
          board->mouseClick(Point{Fl::event_x(), Fl::event_y()});
        }
        return 1;
      case FL_KEYDOWN:
        if (inMenu) {
          // Nous gérons les sélections de menu ici
          switch (Fl::event_key()) {
            case 'a':
              delete board;  // Nettoyer tout tableau précédemment alloué
              board = new Board("map1.txt");
              inMenu = false;
              break;
            case 'b':
              delete board;  // Nettoyer tout tableau précédemment alloué
              board = new Board("map2.txt");
              inMenu = false;
              break;
          }
        } else if (board) {
          board->keyPressed(Fl::event_key());
        }
        return 1;
      default:
        return 0;
    }
    return 0;
  }
  static void Timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / 60, Timer_CB, userdata);  
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
