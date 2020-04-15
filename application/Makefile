make:
	$(MAKE) $(target) -C lib
	$(MAKE) $(target) -C src/core
	$(MAKE) $(target) -C src/builtin-commands

clean: target = clean
clean: make

install: target = install
install: make

uninstall: target = uninstall
uninstall: make

all: make install clean
