# Deck Curator -- Makefile

CC		:= g++
CFLAGS	:= -Wall -Wextra -std=c++11

MAIN	:= main
SRCS	:= $(wildcard src/*.cc)
OBJS	:= $(SRCS:src/%.cc=objs/%.o)
LIBS	:=

.PHONY:	all clean

all : $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

objs/%.o: src/%.cc include/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

objs/%.o: src/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN)
