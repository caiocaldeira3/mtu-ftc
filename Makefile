CC := g++
SRCDIR := src
BINDIR := bin

MAIN := program/main.cpp

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

CFLAGS := -g -Wall -O3 -std=c++17
INC := -I include/

main:
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(MAIN) $(SOURCES) $^ -o $(BINDIR)/main

all: main

run: main
	$(BINDIR)/main
	
.PHONY: clean coverage
