CXX = g++
CXX_FLAGS = -O2 -Wall -Wextra
CXX_OBJ = build/lexer.o build/parser.o build/main.o build/ast.o
HOME_ = $(HOME)

clang: CXX = clang++
clang: main

all: main

main: $(CXX_OBJ)
	$(CXX) $(CXX_OBJ) -o flame

build/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

install:
	mkdir -p $(HOME_)/bin/flame
	cp ./flame $(HOME_)/bin/flame
	ln -s $(HOME_)/bin/flame flame

clean:
	rm -f flame
	rm -f build/*.o
	rm -f temp_flame.cpp
