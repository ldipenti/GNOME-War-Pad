OBJS		=	gtksdl.o
OPTIMIZATION	=	-O2
#DEBUG		=	-g -ggdb

LIB		=	`pkg-config --libs gtk+-2.0` `sdl-config --libs`

CFLAGS=-c -Wall $(DEBUG) $(OPTIMIZATION) `pkg-config --cflags gtk+-2.0` `sdl-config --cflags`
LDFLAGS=-Wall $(DEBUG)  $(LIB)

CC = gcc
RM = rm -f

#all: $(OBJS)
#
#	$(CC) $(OBJS) $(LDFLAGS) -o $(EXECNAME)

gtksdl.o : gtksdl.c gtksdl.h

	$(CC) $< $(CFLAGS)

clean:
	$(RM) $(OBJS) core $(EXECNAME) $(SESSION)

depend:
	echo "No dependences"
