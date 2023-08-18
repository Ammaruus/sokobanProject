#include "Point.h"
#include "Constant.h"

/*--------------------------------------------------

Classe rectangle.

Permet d’afficher un rectangle de remplissage à l’écran
avec différentes couleurs pour le remplissage et la bordure

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
