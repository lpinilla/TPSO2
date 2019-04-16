TASTEFUL = tasteful

GCC = gcc

CFLAGS = -Wall -Werror -g -std=gnu99

#------------------
TARGETS = mem_manager_test
SOURCES = ../Tasteful/testing_suite ../x64barebones/Kernel/mem_manager


all: clean $(TARGETS)

$(TARGETS):
	$(GCC) $(CFLAGS) $(SOURCES:=.c) $@.c -o $@.tasty -lrt

clean:
	@rm -f $(TARGETS) $(TARGETS:=.o) $(TARGETS:=.tasty)
	@rm -f $(SOURCES) $(SOURCES:=.o)

test: all $(TARGETS)
	@$(GCC) $(CFLAGS) ../Tasteful/$(TASTEFUL:=.c) -o $(TASTEFUL)
	@./tasteful

.PHONY: all, clean, test