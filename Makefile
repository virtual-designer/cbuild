CC = gcc
GLOBAL_FLAGS = -g
# CPPFLAFS = -DNDEBUG
BIN = cbuild
SUBDIRS = lib src

all: subdirs
	mv -f src/cbuild .

subdirs:
	@for d in $(SUBDIRS); do \
		$(MAKE) -C $$d; \
	done

clean:
	@for d in $(SUBDIRS); do \
		$(MAKE) -C $$d clean; \
	done
