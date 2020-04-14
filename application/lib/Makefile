LIBS = $(shell find * -type d)

pack: RULE = pack
pack: make

make:
	@for lib in $(LIBS); do \
		$(MAKE) -C $${lib} $(RULE); \
	done

clean: RULE = clean
clean: make