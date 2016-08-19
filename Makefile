CXX = gcc
CXXFLAGS = -w -g
HEADERS = -Iengine engine.h


default: compile

compile:
	$(CXX) $(CXXFLAGS) engine.c bitboard.c $(HEADERS) -o engine.exe

