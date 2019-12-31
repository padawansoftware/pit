SRCS = cmd.c
SRCS += ../core.c
SRCS += ../../../common/command.c
SRCS += ../../../common/directory.c
SRCS += ../../../common/string.c

INCLUDES = -I ..
INCLUDES += -I ../../../

LIBS = -larray

BIN_DIRECTORY = ../../../../bin
BIN = pit-cmd

INSTALL_DIR = /usr/share/pit

# Debug flag
FLAGS = -g
# Use GNU extension sources flag
FLAGS += -D _GNU_SOURCE

make:
	gcc $(SRCS) $(INCLUDES) $(LIBS) -o $(BIN_DIRECTORY)/$(BIN) $(FLAGS)

install:
	if [ ! -d $(INSTALL_DIR) ]; then mkdir $(INSTALL_DIR); fi

	install $(BIN_DIRECTORY)/$(BIN) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(BIN)

clean:
	rm $(BIN_DIRECTORY)/$(BIN)

all: make install clean