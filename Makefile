CC = gcc
CFLAGS = -Wall -Werror -g
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
DOCGEN = doxygen
SOURCES = $(wildcard src/*.c)
OBJETS = $(SOURCES:src/%.c=%.o)
MODE = GUI

vpath %.c src
vpath %.h include
vpath %.o obj

main : $(OBJETS)
	@echo "\n==== Linking ===="
	mkdir -p bin/
	mkdir -p lib/
	ar -crv lib/libjeu.a obj/grille.o obj/jeu.o
	ranlib lib/libjeu.a
	$(CC) -D$(MODE) $(CFLAGS) -o bin/$@ obj/main.o obj/io.o $(LDFLAGS) -ljeu -L lib/

%.o : %.c
	mkdir -p obj/
	$(CC) -D$(MODE) $(CFLAGS) -c -o obj/$@ $< -I include $(CPPFLAGS)

doc :
	$(DOCGEN)

dist:
	mkdir -p dist/
	tar -J -cf dist/SushkoAnna-GoL-v0.2.tar.xz grilles/ include/ src/ Makefile Doxyfile

clean:
	rm -f obj/*
	rm -f bin/*
	rm -f lib/*
	rm -rf dist doc
