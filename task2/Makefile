# preembles and flags
CC=gcc
RM=rm -f

# flags
CFLAGS=-g -std=gnu99 -I../Mastik/src
LDFLAGS=-L../src/ -g
LDLIBS=-lmastik -ldwarf -lelf -lbfd -lm

# targets
TARGETS=ops.so multiply attack
OBJS=ops.o multiply.o attack.o


# commands
.PHONY: all clean

all: ${TARGETS}

ops.so:
	${CC} ${CFLAGS} ops.c -fPIC -shared -o $@

multiply:
	${CC} -o $@ $@.c ops.so 

attack:
	${CC} ${LDFLAGS} -o $@ $@.c ${LDLIBS}
	
clean:
	${RM} ${TARGETS} ${OBJS}
	${RM} *.csv *.txt
