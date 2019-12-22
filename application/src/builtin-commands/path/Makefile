SRCS = path.c
SRCS += ../../common/command.c
SRCS += ../../common/directory.c
SRCS += ../../common/string.c
SRCS += ../../../lib/array.c

INCLUDES = -I ../../
INCLUDES += -I ../../../lib/

BIN_DIRECTORY = ../../../bin
BIN = pit-path

INSTALL_DIR = /usr/share/pit

# Debug flag
FLAGS = -g
# Use GNU extension sources flag
FLAGS += -D _GNU_SOURCE

make:
	gcc $(SRCS) $(INCLUDES) -o $(BIN_DIRECTORY)/$(BIN) $(FLAGS)

install:
	if [ ! -d $(INSTALL_DIR) ]; then mkdir $(INSTALL_DIR); fi

	install $(BIN_DIRECTORY)/$(BIN) $(INSTALL_DIR)

clean:
	rm $(BIN_DIRECTORY)/$(BIN)

all: make install clean