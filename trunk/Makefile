CC = g++

CFLAGS = -Wall

OBJS = Estado.o IA.o Interface.o Jogo.o utils.o

LIBS = -export-dynamic `pkg-config --cflags --libs gtk+-2.0`


all: titiapus

titiapus: main.cpp $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(FLAGS) $(LIBS)

Estado.o: Estado.cpp Estado.h
	$(CC) $(FLAGS) $< -c $(FLAGS) $(LIBS)

IA.o: IA.cpp IA.h
	$(CC) $(FLAGS) $< -c $(FLAGS) $(LIBS)

Interface.o: Interface.cpp Interface.h
	$(CC) $(FLAGS) $< -c $(FLAGS) $(LIBS)

Jogo.o: Jogo.cpp Jogo.h
	$(CC) $(FLAGS) $< -c $(FLAGS) $(LIBS)

utils.o: utils.cpp utils.h
	$(CC) $(FLAGS) $< -c $(FLAGS) $(LIBS)

clean:
	rm -f titiapus
	rm -f *.o
