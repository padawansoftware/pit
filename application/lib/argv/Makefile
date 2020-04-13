SOURCE = argv.c
OBJ = argv.o

LIB = libargv.a
INCLUDE = argv.h

CFLAGS += -I ../array

pack: $(OBJ)
	ar rcs $(LIB) $(OBJ)

install: pack
	install $(INCLUDE) $(INCLUDE_INSTALL_DIR)
	install $(LIB) $(LIB_INSTALL_DIR)

clean:
	$(RM) $(OBJ)
	$(RM) $(LIB)