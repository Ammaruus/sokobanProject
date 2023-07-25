# Nom du projet
TARGET = Sokoban

# Compilateur C++
CXX = g++

# Options du compilateur
CXXFLAGS = -std=c++2a -Wall

# Répertoire où se trouvent les en-têtes FLTK
FLTK_INCLUDE = /usr/include/FL

# Répertoire où se trouvent les bibliothèques FLTK
FLTK_LIB = /chemin/vers/votre/repertoire/FLTK/lib

# Bibliothèques FLTK à lier
FLTK_LIBS = -lfltk -lfltk_images

# Fichiers sources
SRCS = main.cpp Cell.cpp Point.cpp

# Générer la liste des fichiers objets à partir des fichiers sources
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET) 
	./Sokoban

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -L$(FLTK_LIB) $(FLTK_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -I$(FLTK_INCLUDE)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
