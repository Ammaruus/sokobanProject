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

#include "Board.h"


using namespace std;

vector<vector<int>> board{
    {1, 0, 0, 1}, 
    {1, 0, 2, 0}, 
    {1, 3, 0, 0},
    {1, 1, 1, 4}};

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