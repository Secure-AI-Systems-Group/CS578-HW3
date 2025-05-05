# preembles and flags
CC=gcc
RM=rm -f

# flags
CFLAGS=-g -std=gnu99 -I../mastik
LDFLAGS=-L../src/ -L. -g
LDLIBS=-lmastik -ldwarf -lelf -lbfd -lm -lops

# shared library 
LIB_OUT=libops.so
LIBSRCS=ops.c io.c
LIBOBJS=ops.o io.o

# victim and attack programs
VIC_OUT=multiply
VICOBJS=multiply.o
ATT_OUT=attack
ATTOBJS=attack.o


# commands
.PHONY: all clean

all: ${LIB_OUT} ${VIC_OUT} ${ATT_OUT}

${LIB_OUT}: ${LIBOBJS}
	${CC} -fPIC -shared -o $@ $^

${VIC_OUT}: ${VICOBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LDLIBS}

${ATT_OUT}: ${ATTOBJS}
	${CC} ${LDFLAGS} -o $@ $@.c ${CFLAGS} ${LDLIBS}
	
clean:
	${RM} ${LIB_OUT} ${LIBOBJS} ${VIC_OUT} ${VICOBJS} ${ATT_OUT} ${ATTOBJS}
