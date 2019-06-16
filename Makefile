CC=clang
CFLAGS=-Isrc -g -Wall
SOURCE=$(wildcard src/*.c)
TEST=$(patsubst test/%.c, build/bin/%, $(wildcard test/*.c))
BUILDDIRS=build/bin build/images

.PHONY: all clean test

all: $(TEST)

clean:
	rm -rf $(BUILDDIRS)

test: $(TEST)
	time ./build/bin/rgb2ycbcr images/zorg.ppm build/images/zorg-YCbCr.ppm
	time ./build/bin/ycbcr2rgb build/images/zorg-YCbCr.ppm build/images/zorg-RGB.ppm

$(BUILDDIRS):
	mkdir -p $@

$(TEST): build/bin/%: test/%.c $(SOURCE) $(BUILDDIRS)
	$(CC) $(CFLAGS) -o $@ $< $(SOURCE)

