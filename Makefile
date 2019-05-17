OBJ = main.o graph.o dfs.o process_tasks.o
LFLAGS = -lSystem -lpthread
CFLAGS = -std=c11 -O2 -Wall
all: exe

exe: mmake

%.o: %.c
	$(CC) $(CFLAGS) -c $<

mmake: $(OBJ)
	$(LD) $(LFLAGS) $? -o $@

clean:
	rm -fv *.o mmake
