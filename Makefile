all: exe

exe: main

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%: %.o
	$(CC) $(CFLAGS) -c $< -o $%
