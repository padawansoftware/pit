make:
	$(MAKE) -C src/core
	$(MAKE) -C src/builtin-commands

all: make install clean

clean:
	$(MAKE) clean -C src/core
	$(MAKE) clean -C src/builtin-commands

install:
	$(MAKE) install -C src/core
	$(MAKE) install -C src/builtin-commands

uninstall:
	$(MAKE) uninstall -C src/core
	$(MAKE) uninstall -C src/builtin-commands
