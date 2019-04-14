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
CFLAGS += -std=c++17 -D_GNU_SOURCE

ifneq ($(OS),Windows_NT)
	CFLAGS += -fPIC -shared

endif

ifeq ($(COMPILE_ARCH),Darwin)
	CFLAGS += -I/usr/local/opt/eigen/include/eigen3
	LDFLAGS += -dynamiclib -undefined dynamic_lookup
endif

#LDFLAGS += -static

SRC_DIRECTORY = ./src
SOURCES_DIRECTORIES := $(shell find $(SRC_DIRECTORY) -type d)
OBJECTS_DIRECTORIES := $(subst $(SRC_DIRECTORY),$(OBJ_DIRECTORY),$(SOURCES_DIRECTORIES))

SOURCES := $(shell find src -type f -name '*.cpp')
COMPILE_OBJECTS := $(SOURCES:src/%.cpp=$(PREFIX)/%.o)
LINK_OBJECTS := $(SOURCES:src/%.cpp=%.o)
NIF := $(PREFIX)/eigen_nif.so

all: header install

install: nif

$(PREFIX)/%.o: src/%.cpp
	@echo 'Compiling: '$<
	@mkdir -p "$(@D)"
	@$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(COMPILE_OBJECTS): $(PREFIX) $(SOURCES)

nif: $(COMPILE_OBJECTS)
	@echo 'Compiling nif: '$(NIF)
	@$(CC) $(CFLAGS) -o $(NIF) $(COMPILE_OBJECTS) $(LDFLAGS)

$(PREFIX):
	@mkdir -p $@

header:
	@echo 'Compile Arch: '$(COMPILE_ARCH)
	@echo 'ERL_INCLUDE_PATH: '$(ERL_INCLUDE_PATH)
	@echo 'CC: '$(CC)
	@echo 'CFLAGS: '$(CFLAGS)
	@echo 'SOURCES: '$(SOURCES)
	@echo

clean:
	rm -rf $(PREFIX)
