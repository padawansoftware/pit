SRC_DIR = ..
COMMON_DIR = $(SRC_DIR)/common
LIB_DIR = ../../lib

SRCS = core.c
SRCS += $(foreach src, directory string, $(COMMON_DIR)/$(src).c)

LIBS += array
LIBS += argv

CFLAGS += -I $(SRC_DIR)
CFLAGS += $(foreach lib, $(LIBS), -I $(LIB_DIR)/$(lib))
CFLAGS += -D _GNU_SOURCE

LDFLAGS = $(foreach lib, $(LIBS), -L $(LIB_DIR)/$(lib))
LDLIBS = $(foreach lib, $(LIBS), -l$(lib))

INSTALL_DIR = /usr/share/pit

BIN_DIRECTORY = ../../bin
BIN = pit

pit: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(BIN)

clean:
	$(RM) $(BIN)
