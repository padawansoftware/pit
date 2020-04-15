SRC_DIR = ../../..
COMMON_DIR = $(SRC_DIR)/common
LIB_DIR = $(SRC_DIR)/../lib

SRCS = cmd.c
SRCS += ../core.c
SRCS += $(foreach src, command directory string, $(COMMON_DIR)/$(src).c)

LIBS += array
LIBS += argv

CFLAGS = -I ..
CFLAGS += -I $(SRC_DIR)
CFLAGS += $(foreach lib, $(LIBS), -I $(LIB_DIR)/$(lib))
CFLAGS += -D _GNU_SOURCE

LDFLAGS = $(foreach lib, $(LIBS), -L $(LIB_DIR)/$(lib))
LDLIBS = $(foreach lib, $(LIBS), -l$(lib))

BIN = pit-cmd

INSTALL_DIR = /usr/share/pit

pit-cmd:
	gcc $(SRCS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(BIN)

clean:
	$(RM) $(BIN)
