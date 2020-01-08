CFLAGS+=	-W -Wall -std=c99 -g -pedantic
CFLAGS+=	-I/usr/local/include
LDFLAGS+=	-L/usr/local/lib
LDFLAGS+=	-lportmidi

#CFLAGS+=	`pkgconf --cflags gtk+-3.0` 

main: ${@}.c
	$(CC) $(CFLAGS) ${@}.c $(LDFLAGS) -o $@

clicktrack: ${@}.c
	$(CC) $(CFLAGS) -o $@ ${@}.c $(LDFLAGS) 

main2: ${@}.c ddice.h ddice.c mymidi.h
	$(CC) $(CFLAGS) -o $@ ${@}.c ddice.c $(LDFLAGS) 

.PHONY: clean 
    
clean:
	rm -f main clicktrack *.core *.BAK
	rm -f main2


