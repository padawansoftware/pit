SRCS = $(wildcard src/*.c src/command/*.c lib/*.c)
INSTALL = /usr/local/bin/
FLAGS =  -Wall -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wconversion

make:
	gcc -g $(SRCS) -I src/ -I src/command/ -I lib/ -o bin/pit -D _GNU_SOURCE

all: make install

cleanall:
	rm bin/pit

install:
	cp bin/pit $(INSTALL)

uninstall:
	rm $(INSTALL)/pit




