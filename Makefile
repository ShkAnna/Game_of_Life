CC = gcc
CFLAGS = -Wall
DOCGEN = doxygen
SOURCES = $(wildcard src/*.c)
OBJETS = $(SOURCES:src/%.c=%.o)
OBJETS_CHEM = $(SOURCES:src/%.c=obj/%.o)

vpath %.c src
vpath %.h include
vpath %.o obj
 
main : $(OBJETS)
	@echo "\n==== Linking ===="
	mkdir -p bin/
	$(CC) $(CFLAGS) -o bin/$@ $(OBJETS_CHEM)

%.o : %.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -c -o obj/$@ $< -I include

doc :
	$(DOCGEN)

dist: 
	tar -J -cf project_sushko_td3.tar.xz grilles/ include/ src/ Makefile Doxyfile

clean: 
	rm obj/*
	rm bin/*


