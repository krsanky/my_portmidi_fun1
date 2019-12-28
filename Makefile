CFLAGS+=	-W -Wall -std=c99 -g -pedantic
#CFLAGS+=	`pkgconf --cflags gtk+-3.0` 
#CFLAGS+=	-rdynamic 

main: ${@}.c
	$(CC) $(CFLAGS) ${@}.c $(LDFLAGS) -o $@

.PHONY: clean 
    
clean:
	rm -f main


