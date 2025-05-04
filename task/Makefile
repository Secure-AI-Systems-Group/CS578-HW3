# preembles and flags
CC=gcc
RM=rm -f

# flags
CFLAGS=-g -std=gnu99 -I../mastik
LDFLAGS=-L../src/ -g
LDLIBS=-lmastik -ldwarf -lelf -lbfd -lm

# targets
TARGETS=ops.so io.so multiply attack
OBJS=ops.o io.o multiply.o attack.o


# commands
.PHONY: all clean

all: ${TARGETS}

ops.so:
	${CC} ${CFLAGS} ops.c -fPIC -shared -o $@

io.so:
	${CC} ${CFLAGS} io.c -fPIC -shared -o $@

multiply:
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $@.c io.so ops.so ${LDLIBS}

attack:
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $@.c ${LDLIBS}
	
clean:
	${RM} ${TARGETS} ${OBJS}
