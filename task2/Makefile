# preembles and flags
CC=gcc
RM=rm -f

# flags
CFLAGS=-g -std=gnu99 -I../Mastik/src
LDFLAGS=-L../Mastik/src/ -g
LDLIBS=-lmastik -ldwarf -lelf -lbfd -lm

# targets
TARGETS=ops.so multiply attack
OBJS=ops.o multiply.o attack.o


# commands
.PHONY: all clean

all: ${TARGETS}

ops.so:
	${CC} ${CFLAGS} -fPIC -shared -o $@ $@.c

multiply:
	${CC} ${CFLAGS} -o $@ $@.c ${LDLIBS}

attack:
	${CC} ${LDFLAGS} -o $@ $@.o ${LDLIBS}
	
clean:
	${RM} ${TARGETS} ${OBJS}
	${RM} *.csv *.txt
