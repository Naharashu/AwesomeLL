CXX = g++
CXX_FLAGS = -O2 -Wall -Wextra
CXX_OBJ = lexer.o parser.o main.o ast.o
HOME_ = $(HOME)

clang: CXX = clang++
clang: main

all: main

main: $(CXX_OBJ)
	$(CXX) $(CXX_OBJ) -o flame

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install:
	mkdir -p $(HOME_)/bin/flame
	cp ./flame $(HOME_)/bin/flame
	ln -s $(HOME_)/bin/flame flame

clean:
	rm -f flame
	rm -f *.o
	rm -f temp_flame.cpp
