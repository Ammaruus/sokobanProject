#ifndef POINT_H
#define POINT_H
#include <FL/Fl_Double_Window.H>
#include <string>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <vector>
using namespace std;

struct Point {
  int x;
  int y;
  Point operator+(const Point& v) const {
    Point result;
    result.x = x + v.x;
    result.y = y + v.y;
    return result;
  }
  bool operator==(const Point &v) const {
    return (x == v.x && y == v.y); 
  }
  bool operator!=(const Point &v) const {
    return (x != v.x && y != v.y); 
  }
};

#endif // POINT_H
