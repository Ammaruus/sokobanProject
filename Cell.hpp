#ifndef CELL_H
#define CELL_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "Point.hpp"

class Rectangle {
    Point center;
    int w, h;
    Fl_Color fillColor, frameColor;

public:
    Rectangle(Point center, int w, int h,
              Fl_Color frameColor = FL_BLACK,
              Fl_Color fillColor = FL_WHITE);

    void draw();
    void setFillColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFrameColor);
    bool contains(Point p);
};

class Cell {
    Rectangle r;
    bool on = false;

public:
    Cell(Point center, int w, int h);
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void setFillColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFrameColor);
    bool contains(Point p);
    // Méthode pour convertir une cellule en mur
    void setWall();

    // Méthode pour convertir une cellule en personnage (en jaune)
    void setPlayer();

    // Méthode pour convertir une cellule en boîte (en rouge)
    void setBox();

    void setTarget();

};

#endif // CELL_H
