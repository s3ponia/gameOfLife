LDFLAGS=$(shell pkg-config --libs ncurses)
CXXFLAGS=$(shell pkg-config --CFLAGS ncurses)
CXX=g++

gameOfLife: src/main.o src/Map.o
	$(CXX) $(CXXFLAGS)  src/main.o src/Map.o $(LDFLAGS) -o gameOfLife

clean:
	rm src/*.o gameOfLife
