CC=clang
CFLAGS=-Isrc -g -Wall
SOURCE=$(wildcard src/*.c)
TEST=$(patsubst test/%.c, build/bin/%, $(wildcard test/*.c))
BUILDDIRS=build/bin

all: $(TEST)

clean:
	rm -rf $(BUILDDIRS)

$(BUILDDIRS):
	mkdir -p $@

$(TEST): build/bin/%: test/%.c $(BUILDDIRS)
	$(CC) $(CFLAGS) -o $@ $< $(SOURCE)

