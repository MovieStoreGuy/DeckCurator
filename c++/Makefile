# Deck Curator -- Makefile
OS		:= $(shell uname)
CC		:= g++
CFLAGS	:= -Wall -Wextra -std=c++11 -O3 `python-config --cflags`
CLIBS	:= -shared `python-config --ldflag`

ifeq ($(OS),Darwin)
	CLIBS	+= -framework Python
endif

MAIN	:= DeckCurator.so
SRCS	:= $(wildcard src/*.cc)
OBJS	:= $(SRCS:src/%.cc=objs/%.o)

.PHONY:	all clean

all: $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(CLIBS)

objs/%.o: src/%.cc include/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

objs/%.o: src/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN)
