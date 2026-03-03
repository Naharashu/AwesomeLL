CXX = g++

test:
	$(CXX) main.cpp -O2 -o main -Wall -Wextra

clean:
	rm -f main
