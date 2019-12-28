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


#Information for inst:portmidi-217p0
#
#Files:
#/usr/local/include/portmidi.h
#/usr/local/include/porttime.h
#/usr/local/lib/libportmidi.so.0.0
#/usr/local/lib/libportmidi_s.a
#/usr/local/lib/pkgconfig/portmidi.pc
#
#
