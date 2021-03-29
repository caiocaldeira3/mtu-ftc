CC := g++
SRCDIR := src
BINDIR := bin

MAIN := program/main.cc

SRCEXT := cc
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

CFLAGS := -std=c++17

INC := -I include/

main:
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(SOURCES) $(SRC) $(MAIN) $^ -o $(BINDIR)/main

all: main

run: main
	$(BINDIR)/main ${ARGS}

run-test:
	$(BINDIR)/main ${ARGS}

clean:
	$(RM) -r bin outputs/

.PHONY: clean coverage