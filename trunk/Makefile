CC = g++

CFLAGS = -Wall

MODULES = Estado IA Interface Jogo utils Jogador JogadorHumano JogadorComputador
OBJDIR = obj
OBJNAMES = $(addsuffix .o,$(MODULES)) 
OBJS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

LIBS = -export-dynamic `pkg-config --cflags --libs gtk+-2.0`


titiapus: main.cpp $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(FLAGS) $(LIBS)

$(OBJDIR)/%.o: %.cpp %.h | $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@ $(FLAGS) $(LIBS) 

$(OBJDIR):
	mkdir $(OBJDIR) -p

clean:
	rm -f titiapus
	rm -f *.o
	rm -f -r $(OBJDIR)

