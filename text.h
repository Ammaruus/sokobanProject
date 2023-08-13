#ifndef __TEXT_H
#define __TEXT_H


#include "Point.h"
#include <string>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>

class Text {
  string s;
  Point center;
  int fontSize;
  Fl_Color color;

public:
  // Constructor
  Text(string s, Point center, int fontSize = 5, Fl_Color color = FL_BLACK)
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
  void setColor(Fl_Color newColor){ color = newColor;}
};

#endif // __TEXT_H