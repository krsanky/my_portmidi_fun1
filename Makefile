CFLAGS+=	-W -Wall -std=c99 -g -pedantic
CFLAGS+=	-I/usr/local/include
LDFLAGS+=	-L/usr/local/lib
LDFLAGS+=	-lportmidi
LDFLAGS+=	-lncurses

all: main clicktrack ncur purple wizardfight basic_drum_1

main: ${@}.c
	$(CC) $(CFLAGS) ${@}.c $(LDFLAGS) -o $@

clicktrack: ${@}.c
	$(CC) $(CFLAGS) -o $@ ${@}.c $(LDFLAGS) 

basic_drum_1: ${@}.c ddice.h ddice.c mymidi.h
	$(CC) $(CFLAGS) -o $@ ${@}.c ddice.c $(LDFLAGS) 

ncur: $@.c mycur.h mycur.c
	$(CC) $(CFLAGS) $@.c mycur.c $(LDFLAGS) -o $@

wizardfight: $@.c mycur.h mycur.c
	$(CC) $(CFLAGS) $@.c mycur.c $(LDFLAGS) -o $@

purple: $@.c mylib.h mycur.h mycur.c
	$(CC) $(CFLAGS) $@.c mycur.c $(LDFLAGS) -o $@
#	attrib.c
#	colors.c
#	conway.c
#	mylib.h
#	purple.c

.PHONY: clean 
    
clean:
	rm -f main clicktrack *.core *.BAK
	rm -f ncur
	rm -f basic_drum_1
	rm -f wizardfight purple  

