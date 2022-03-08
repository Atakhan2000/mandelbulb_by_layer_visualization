all: bulber

Bulber.o: Bulber.cpp
	gcc -O2 -c Bulber.cpp

SdlMain.o: SdlMain.cpp
	gcc -c SdlMain.cpp `sdl-config --cflags --libs`

bulber: Bulber.o SdlMain.o
	g++ -o bulber Bulber.o SdlMain.o -ldl `sdl-config --cflags --libs`

clean:
	rm bulber Bulber.o SdlMain.o

