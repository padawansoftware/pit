COM_DIR = ../common
LIB_DIR = ../../lib

SRCS = core.c
SRCS += $(COM_DIR)/string.c
SRCS += $(COM_DIR)/directory.c
SRCS += $(LIB_DIR)/array.c

LIBS = -I ../ -I ../../lib

INSTALL_DIR = /usr/share/pit

CFLAGS = -D _GNU_SOURCE #-Wall -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wconversion
BIN_DIRECTORY = ../../bin
BIN = pit

make:
	gcc $(SRCS) $(LIBS) $(CFLAGS) -o $(BIN_DIRECTORY)/$(BIN)

install:
	if [ ! -d $(INSTALL_DIR) ]; then mkdir $(INSTALL_DIR); fi

	install $(BIN_DIRECTORY)/$(BIN) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(BIN)

clean:
	rm $(BIN_DIRECTORY)/$(BIN)

all: make install clean

