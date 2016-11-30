all: bin

CC	= g++
CFLAGS	= -W -Wall -Wextra -pedantic  -g -Igrapic -I/usr/include/SDL2
LDFLAGS = -L/usr/lib -lSDL2 -lSDL2_ttf -lSDL2_image
GRAPIC	= grapic/Grapic.cpp grapic/Grapic_func.cpp
EXEC	= bin/simplexus
OBJ	= obj

bin: $(EXEC)

bin/simplexus: $(OBJ)/main_pavage.o $(OBJ)/mathutil.o $(OBJ)/graphicutil.o $(GRAPIC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ)/main_pavage.o: src/main_pavage.cpp src/point.hpp src/fileutil.hpp src/pavage.hpp
	$(CC) $(CFLAGS) -o $@ -c src/main_pavage.cpp -std=c++11 -g

$(OBJ)/mathutil.o: src/mathutil.hpp src/mathutil.cpp
	$(CC) $(CFLAGS) -o $@ -c src/mathutil.cpp -std=c++11 -g

$(OBJ)/graphicutil.o: src/graphicutil.hpp src/graphicutil.cpp
	$(CC) $(CFLAGS) -o $@ -c src/graphicutil.cpp  -std=c++11 -g

clean:
	rm -rf $(EXEC)
	rm -f $(OBJ)/*.o
	rm -f src/*~

doc: doc/* src/* FORCE
	cd doc ; doxygen Documentation_Pavage

FORCE:
