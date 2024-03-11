CC = gcc
CFLAGS = -O1 -g -Wall 

CFILES := nonrecurtree.c check.c

check: $(CFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm check
