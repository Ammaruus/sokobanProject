#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <algorithm>
#include <array>
#include <bits/stdc++.h> 
#include <chrono>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <time.h>
#include <vector>

#include "Board.h"


using namespace std;

vector<vector<int>> initializeMatrixFromFile(const string &filename) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return {};
    }

    vector<vector<int>> matrix;
    string line;

    while (getline(inputFile, line)) {
        vector<int> row;
        istringstream iss(line);
        int value;

        while (iss >> value) {
            row.push_back(value);
        }

        matrix.push_back(row);
    }

    return matrix;
}

vector<vector<int>> board = initializeMatrixFromFile("map1.txt");

bool Board::gameEnd(){
  for (auto &v : cells)
    for (auto &c : v) {
      if (c.isObjective && c.getType() != BOX) {
        return false;
      }
    }
  setHighscore(steps);
  return true;
}

bool Board::validplayerMove(Point destination){
    return cells[destination.x][destination.y].getType() != WALL && cells[destination.x][destination.y].getType() != BOX;
} 

bool Board::areneighbors(Cell* c1, Cell* c2){ 
  for (unsigned int i = 0; i < c1->getneighbors().size() ; i++) {
    if (c1->getneighbors()[i] == c2) {
        return true; 
    }
  }
  return false;
}

void Board::move(Point vecteur){
  Point playerCellPos = playerCell->getPosition();
  Point newppos = {playerCellPos.x + vecteur.x, playerCellPos.y + vecteur.y};
  if(pointInBoard(newppos)) {
    if (areneighbors(playerCell,&cells[newppos.x][newppos.y])) {
      if(validplayerMove(newppos)) {
        playerMove(newppos);
      } else if (cells[newppos.x][newppos.y].getType() == BOX) {
        //cout <<"box pos avant le deplacement:" << newppos.x << ' ' << newppos.y << endl;
        if (isValidBoxmove(newppos,vecteur)) { 
        //cout <<"valide !" << endl;
            playerBoxmove(newppos,vecteur); 
            }
       }
    }
  }
}


void Board::playerBoxmove(Point newppos, Point vecteur){
  playerMove(newppos);
  Point boxDest = {newppos.x + vecteur.x , newppos.y + vecteur.y};
  cells[boxDest.x][boxDest.y].setType(BOX);  
}


void Board::playerMove(Point newppos) { 
  Point playerCellPos = playerCell->getPosition();
  if (playerCell->isObjective) {
    playerCell->setType(OBJECTIVE);
  }else {playerCell->setType(PATH);}

  cells[newppos.x][newppos.y].setType(PLAYER);

  //cout << "old : " << playerCellPos.x << ' ' << playerCellPos.y << endl;
  //cout << "new : " << newppos.x << ' ' << newppos.y << endl;
  steps++;
  updateCellneighbors(playerCell); 
  
  playerCell = &cells[newppos.x][newppos.y]; 
  for (int i = 0; i < playerCell->getneighbors().size(); i++) {
    Point pos = playerCell->getneighbors()[i]->getPosition();
    //cout << "positions dispo :" << pos.x << ' ' << pos.y << endl; 
    }
}


bool Board::isValidBoxmove(Point newppos, Point vecteur){
  Point boxDest = {newppos.x + vecteur.x, newppos.y + vecteur.y};

  return  areneighbors(&cells[newppos.x][newppos.y],&cells[boxDest.x][boxDest.y])
   && cells[boxDest.x][boxDest.y].getType() != WALL;
} 

void Board::initialize() {
  
   steps = 0;

  cells.clear(); //quand on recommence une partie, clear la grille
  //cout << "board size : " << board.size() << "cells size : " << cells.size() << endl;

  // cells initilisation
  for (unsigned short x = 0; x < board.size(); x++) {
    //cout << "board size :" << board.size() << endl;
    cells.push_back({});
    for (int y = 0; y < board.size(); y++) {
      cells[x].push_back({{50 * x + 25, 50 * y + 25}, 40, 40});
      cells[x][y].setPosition(
          {static_cast<int>(x), static_cast<int>(y)}); 
      //ici  switch les different type de cellule
      switch (board[y][x]) { 
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
  updateAllneighbors(); 
  cout << "Rempli !" << endl;
}


bool Board::stepsLimitPassed() const{
    return (steps>=stepsLimit);
}

void Board::draw() {
  counter += 1;
  if (counter < 100) {
    introduction.draw(); // dessiner l'ecran d'accueil
  }
  else {
      if (gameEnd()) { // joueura gagné
      textWin.draw();
    } else if (stepsLimitPassed()) { // joueur a perdu
      textLose.draw();
    }
    else{ // dessiner la map de cellule
      for (auto &v : cells)
      for (auto &c : v) {
        c.draw();
      }
   }
      Text textSteps{"Nombre de pas :" + to_string(steps), {100, 300}, 20, FL_BLACK};
      Text textHighScore{"Meilleur score :" + to_string(gamesHighScore), {100, 320}, 20, FL_BLACK};
      Text textStepsLimit{"Limite de pas :" + to_string(stepsLimit), {100, 340}, 20, FL_BLACK};
      textHighScore.draw();
      textSteps.draw();
      textStepsLimit.draw();
      howToPlay1.draw();
      howToPlay2.draw();
      howToPlay3.draw();

    }
  }



void Board::updateAllneighbors() {
  for (unsigned x = 0; x < cells.size(); x++)
    for (unsigned y = 0; y < cells.size(); y++) {
      updateCellneighbors(&cells[x][y]);
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
  case ' ': // restart le jeux
    initialize();
    break;
  case 'q': // sortir du jeux
    exit(0);
    break;
  case FL_Up:
    move({0, -1});
    break;
  case FL_Down:
    move({0, 1}); 
    break;
  case FL_Left:
    move({-1, 0});
    break;
  case FL_Right:
    move({1, 0});
    break;
  default: {
  } // pass
  }
  draw();
}


bool Board::pointInBoard(Point newppos){
 
  if (0 <= newppos.x < cells.size() && 0 <= newppos.y < cells.size()) {
    return true; 
    }
  return false ;
}

void Board::updateCellneighbors(Cell* cell){
  int x = cell->getPosition().x; 
  int y = cell->getPosition().y; 
  //cout << x << y << endl;
  vector<Cell *> neighbors;
      for (auto &shift : vector<Point>({
              {-1, 0}, 
               {1, 0},
               {0, -1},
                {0, 1}})) 
        {
      
        if (!((x == 0 && shift.x == -1) || (y == 0 && shift.y == -1))) {
          unsigned neighborx =
              static_cast<unsigned>(static_cast<int>(x) + shift.x);
          unsigned neighbory =
              static_cast<unsigned>(static_cast<int>(y) + shift.y);
          if (neighborx < cells.size() && neighbory < cells[neighborx].size()) { 
            neighbors.push_back(&cells[neighborx][neighbory]);
          }
        }
        cells[x][y].setneighbors(neighbors); 
      }
}

// initilialiser le HighScore du fichier donnée
void Board::initHighscore() {
  ifstream highScoreFile("highscore.txt");
  if (!highScoreFile) {
    cout << "Unable to open file" << endl;
    exit(1);
  } else {
    highScoreFile.seekg(0, highScoreFile.end);
    int length = highScoreFile.tellg(); 
    char *buffer = new char[length];
    highScoreFile.seekg(0, highScoreFile.beg);
    highScoreFile.read(buffer, length);
    sscanf(buffer, "%d", &gamesHighScore);
    //cout << "high score is " << gamesHighScore << endl;
  }
  highScoreFile.close();
}

//quand y'a un nouveau high score, le changer dansle fichier
void Board::resetHighscore() {
  ofstream highscoreFile("highscore.txt", ofstream::out | ofstream::trunc);
  if (!highscoreFile) {
    cout << "Unable to open file" << endl;
    exit(1);
  } else {
    highscoreFile << 0 << endl;
      gamesHighScore = 0;
    cout << "highscore was reset" << gamesHighScore << endl;
  }
  highscoreFile.close();
}

// mettre le nouveau high score dans le fichier
void Board::setHighscore(unsigned int newHighscore) {
  if (gamesHighScore == 0 || gamesHighScore > newHighscore) {
    ofstream highscoreFile("highscore.txt", ofstream::out | ofstream::trunc);
    highscoreFile << newHighscore << endl;
    gamesHighScore = newHighscore;
    cout << "newhighscore : " << newHighscore << endl;
  }
}


