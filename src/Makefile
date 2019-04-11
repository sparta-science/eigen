# Makefile for building the NIF
#
# Makefile targets:
#
# all/install   build and install the NIF
# clean         clean build products and intermediates

COMPILE_ARCH=$(shell uname -s)
PREFIX ?= ./priv

ERL_INCLUDE_PATH = $(shell erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version), "/include"])])' -s init stop -noshell)

CFLAGS ?= -O2 -Wall -Wextra -Wno-unused-parameter -I$(ERL_INCLUDE_PATH)
CFLAGS += -std=c99 -D_GNU_SOURCE

ifneq ($(OS),Windows_NT)
	CFLAGS += -fPIC -shared

	ifeq ($(COMPILE_ARCH),Darwin)
		LDFLAGS += -dynamiclib -undefined dynamic_lookup
	endif
endif

#LDFLAGS += -static

SRC_DIRECTORY = ./src
SOURCES_DIRECTORIES := $(shell find $(SRC_DIRECTORY) -type d)
OBJECTS_DIRECTORIES := $(subst $(SRC_DIRECTORY),$(OBJ_DIRECTORY),$(SOURCES_DIRECTORIES))

SOURCES := $(wildcard src/*.c)
COMPILE_OBJECTS := $(SOURCES:src/%.c=$(PREFIX)/%.so)

all: header install

install: $(COMPILE_OBJECTS)

$(PREFIX)/%.so: src/%.c
	@echo 'Compiling: '$<
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(COMPILE_OBJECTS): $(PREFIX) $(SOURCES)

$(PREFIX):
	mkdir -p $@

header:
	@echo 'Compile Arch: '$(COMPILE_ARCH)
	@echo 'ERL_INCLUDE_PATH: '$(ERL_INCLUDE_PATH)
	@echo 'CC: '$(CC)
	@echo 'CFLAGS: '$(CFLAGS)
	@echo 'sources: '$(SOURCES)
	@echo

clean:
	rm -rf $(PREFIX)
