CXX = g++

test:
	$(CXX) main.cpp lexer.cpp parser.cpp -pipe -g -O2 -o main -Wall -Wextra

clean:
	rm -f main
