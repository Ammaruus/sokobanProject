#include "Point.h"
#include "Constant.h"

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

   vector<Point> stripeInitPos {{center.x-w/2, center.y - h /2 + 2},
                              {center.x-w/2, center.y - h /4},
                              {center.x-w/2, center.y},
                              {center.x-w/2, center.y + h /4},
                              {center.x-w/2, center.y + h/2 - 2}};
  vector<Point> stripeFinalPos {{center.x+w/2, center.y - h /2 + 2},
                              {center.x+w/2, center.y - h /4},
                              {center.x+w/2, center.y},
                              {center.x+w/2, center.y + h /4},
                              {center.x+w/2, center.y + h /2 - 2}};

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
  void drawstripes();
};