SRCS = $(wildcard src/pit.c src/command/*.c src/common/*.c lib/*.c)
LIBS = -I src/ -I src/command/ -I lib/
INSTALL = /usr/share/pit/
FLAGS =  -Wall -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wconversion

make:
	gcc -g $(SRCS) $(LIBS) -o bin/pit -D _GNU_SOURCE

all: make install

cleanall:
	rm bin/pit

install:
	cp bin/pit $(INSTALL)

uninstall:
	rm $(INSTALL)/pit




