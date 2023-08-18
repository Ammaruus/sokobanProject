#ifndef __BOARD_H
#define __BOARD_H

#include "Point.h"
#include "Cell.h"
#include "Text.h"
#include "Constant.h"

/*--------------------------------------------------

Classe Board


Une instance de la classe de conseil est faite par la
classe MainWindow dans le fichier main.cpp

Le système fltk via les appels MainWindow:

draw 60 fois par seconde
mouseMove  chaque fois que la souris est déplacée
mouseClick chaque fois que la souris est cliquée
keyPressed chaque fois qu’une touche est pressée

--------------------------------------------------*/

class Board {

  vector<vector<Cell>> cells; // representer notre map, une matrice de cellule
  vector<Cell *> neighbors(int x, int y); // stocke tous les voisins d'une cellule
  Text textWin{"Gagné", {190, 150}, 90, fl_rgb_color(0, 255, 0)};
  Text textLose{"Perdu", {190, 150}, 90, fl_rgb_color(255, 0, 0)};
  Text introduction {"Sokoban, crée par Amine et Ammar", {210, 150}, 20, fl_rgb_color(0,0,0)}; 
  Text howToPlay1 {"Fleche pour bouger le personnage", {250, 20}, 15, fl_rgb_color(0,0,0)};
  Text howToPlay2 {"   restart : Espace", {250, 80}, 15, fl_rgb_color(0,0,0)};
  Text howToPlay3 {" quitter : q ", {250, 100}, 15, fl_rgb_color(0,0,0)};

  unsigned int counter = 0; 
  unsigned int gamesHighScore = 0; // enregistre le meilleur score de la partie
  unsigned int steps = 0; // compteurde pas d'un joueur


  Cell* playerCell; // case du joueur


  void initialize();


  

public:
  Board() { initialize();}
  vector<vector<int>> initializeMatrixFromFile(const string &filename);// permet de lire un fichier et le transformer en matrice d'entier
  
  void draw();


  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  // methode pour gerer les voisins d'une cellule
  void updateAllneighbors();
  void updateCellneighbors(Cell* cell);
  bool areneighbors(Cell* c1, Cell* c2);
  
  // methode qui verifie si un point est a l'interieur de la classe Board
  // utiliser pour verifier dans le move si la nouvelle position est bien dans le board
  bool pointInBoard(Point newppos);

  // methodes qui gere le deplacement d'un joueur ainsi que sa validité
  bool validplayerMove(Point destination);
  void playerMove(Point destination);
  void move(Point vecteur);

  // methodes qui gere le deplacement de la boite ainsi que sa validité
  bool isValidBoxmove(Point newppos, Point vecteur);
  void playerBoxmove(Point newppos, Point vecteur);

  bool gameEnd(); 
  
  // Partie Score
  void initHighscore();
  void resetHighscore();
  void setHighscore(unsigned int newHighscore);
  
  bool stepsLimitPassed() const;

  // Partie Portal
  void PortalTravel(Point Portal);
  static bool matchPortals(Cell c1, Cell c2);

};

#endif //__BOARD_H