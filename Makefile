CC = gcc
CFLAGS = -Wall -Werror -g
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
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
	$(CC) $(CFLAGS) -o bin/$@ $(OBJETS_CHEM) $(LDFLAGS)

%.o : %.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -c -o obj/$@ $< -I include $(CPPFLAGS)

doc :
	$(DOCGEN)

dist:
	mkdir -p dist/
	tar -J -cf dist/SushkoAnna-GoL-v0.2.tar.xz grilles/ include/ src/ Makefile Doxyfile

clean:
	rm -f obj/*
	rm -f bin/*
	rm -rf dist doc
