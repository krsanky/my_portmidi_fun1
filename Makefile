CFLAGS+=	-W -Wall -std=c99 -g -pedantic
CFLAGS+=	-I/usr/local/include
LDFLAGS+=	-L/usr/local/lib
LDFLAGS+=	-lportmidi

#CFLAGS+=	`pkgconf --cflags gtk+-3.0` 

main: ${@}.c
	$(CC) $(CFLAGS) ${@}.c $(LDFLAGS) -o $@

.PHONY: clean 
    
clean:
	rm -f main

