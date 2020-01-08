CFLAGS+=	-W -Wall -std=c99 -g -pedantic
CFLAGS+=	-I/usr/local/include
LDFLAGS+=	-L/usr/local/lib
LDFLAGS+=	-lportmidi
LDFLAGS+=	-lncurses

#CFLAGS+=	`pkgconf --cflags gtk+-3.0` 

all: main main2 clicktrack ncur

main: ${@}.c
	$(CC) $(CFLAGS) ${@}.c $(LDFLAGS) -o $@

clicktrack: ${@}.c
	$(CC) $(CFLAGS) -o $@ ${@}.c $(LDFLAGS) 

main2: ${@}.c ddice.h ddice.c mymidi.h
	$(CC) $(CFLAGS) -o $@ ${@}.c ddice.c $(LDFLAGS) 

ncur: $@.c
	$(CC) $(CFLAGS) $@.c $(LDFLAGS) -o $@

.PHONY: clean 
    
clean:
	rm -f main clicktrack *.core *.BAK
	rm -f main2 ncur


