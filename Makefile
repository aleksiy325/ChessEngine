CXX = gcc
CXXFLAGS = -w -g
HEADERS = -Iengine engine.h


default: compile

compile:
	$(CXX) $(CXXFLAGS) engine.c bitboard.c hash.c board.c $(HEADERS) -o lordloss.exe

