
LDFLAGS +=-lfltk
ALL_FILES= main.cpp Board.cpp Cell.cpp Rectangle.cpp Text.cpp
CXXFLAGS += $(shell fltk-config --cxxflags)
LDFLAGS  += $(shell fltk-config --ldflags)
CXXFLAGS += --std='c++17' -Wall -Wextra -pedantic
LDFLAGS  += -lfltk
CXX = g++
all:
	g++ $(CXXFLAGS) $(ALL_FILES) -o Sokoban $(LDFLAGS)
clean:
	rm -f Sokoban