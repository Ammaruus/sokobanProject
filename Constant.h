#ifndef Constant_hpp
#define Constant_hpp

/* constante utilisé pour gérer les différents paramètres de la partie */

const int windowWidth = 500;
const int windowHeight = 500;
const double refreshPerSecond = 60;
const int PATH = 0; // represente le une case qui peut etre un chemi
const int WALL = 1; // represente une case ou y'a un mur
const int BOX = 2; // represente une case ou y'aune boite
const int PLAYER = 3; // represente une case ou y'a le joueur
const int OBJECTIVE = 4; // represente une case ou y'a la case cible
//const int PORTAL = 5; // represente une case ou y'a un portal
const unsigned int stepsLimit = 20; // limite de pas a ne pas de passer parle joueur


#endif /* Constant_h */