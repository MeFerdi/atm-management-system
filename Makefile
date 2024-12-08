# Define variables
CC = gcc
CFLAGS = -I./src -Wall
OBJECTS = src/main.o src/auth.o src/system.o

# Target to build the ATM executable
atm_system: $(OBJECTS)
	$(CC) -o atm_system $(OBJECTS)

# Rules for building object files
src/main.o: src/main.c src/header.h
	$(CC) $(CFLAGS) -c src/main.c

src/auth.o: src/auth.c src/header.h
	$(CC) $(CFLAGS) -c src/auth.c

src/system.o: src/system.c src/header.h
	$(CC) $(CFLAGS) -c src/system.c

# Clean up object files and executable
clean:
	rm -f $(OBJECTS) atm_system
