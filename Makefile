# See LICENSE file for copyright and license details.

include config.mk

SRC = threadpass.c
OBJ = $(SRC:.c=.o)

LIB = libthreadpass.a
INC = threadpass.h

all: $(LIB) test

$(LIB): $(OBJ)
	$(AR) -rcs $@ $(OBJ)

test: test.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ test.o -fsanitize=thread -lpthread $(LIB)

.c.o:
	$(CC) $(CFLAGS) -c $<

install: $(LIB) $(INC)
	@echo @ install libthreadpass to $(DESTDIR)$(PREFIX)
	@mkdir -p $(DESTDIR)$(PREFIX)/lib
	@cp $(LIB) $(DESTDIR)$(PREFIX)/lib/$(LIB)
	@mkdir -p $(DESTDIR)$(PREFIX)/include
	@cp $(INC) $(DESTDIR)$(PREFIX)/include/$(INC)
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	@cp libthreadpass.3 $(DESTDIR)$(PREFIX)/share/man/man3/libthreadpass.3

uninstall:
	@echo @ uninstall libthreadpass from $(DESTDIR)$(PREFIX)
	@rm -f $(DESTDIR)$(PREFIX)/lib/$(LIB)
	@rm -f $(DESTDIR)$(PREFIX)/include/$(INC)
	@rm -f $(DESTDIR)$(PREFIX)/share/man/man3/libthreadpass.3

clean:
	rm -f $(LIB) test test.o $(OBJ)
