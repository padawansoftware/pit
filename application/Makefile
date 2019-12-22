SRCS = $(wildcard src/pit.c src/command/*.c src/common/*.c lib/*.c)
LIBS = -I src/ -I src/command/ -I lib/
INSTALL = /usr/share/pit/
FLAGS =  -Wall -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wconversion

make:
	gcc -g $(SRCS) $(LIBS) -o bin/pit -D _GNU_SOURCE
	$(MAKE) -C src/builtin-commands

all: make install clean

clean:
	rm bin/pit
	$(MAKE) clean -C src/builtin-commands

install:
	cp bin/pit $(INSTALL)
	$(MAKE) install -C src/builtin-commands

uninstall:
	rm $(INSTALL)/pit

