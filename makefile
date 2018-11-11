CC=gcc
CFLAGS=-W -Wall -pedantic -ansi
CDFLAGS=
EXEC=linux_vocabulle.run mac_vocabulle.out windows_vocabulle.exe
DIR=Fonctions/
SRC=$(DIR)main.c $(DIR)affichage.c $(DIR)fichiers.c $(DIR)dates.c
OBJ=$(SRC:.c=.o)

all: $(EXEC)

linux_vocabulle.run: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

mac_vocabullei.out: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

windows_vocabulle.exe: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: $(DIR)dates.h $(DIR)affichage.h $(DIR)fichiers.h $(DIR)static.h
affichage.o: $(DIR)affichage.h $(DIR)static.h
dates.o: $(DIR)dates.o $(DIR)static.h
fichiers.o: $(DIR)fichiers.h $(DIR)static.h

%.o: %.c:
	$(CC) -o $@ -c $< $(CFLAGS)



