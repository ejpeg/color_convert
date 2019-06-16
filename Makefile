CC=clang
CFLAGS=-Isrc -g
COLOR_CONVERT=src/color_convert.c
RGB2YCBCR=./build/bin/rgb2ycbcr
YCBCR2RGB=./build/bin/ycbcr2rgb

all: $(RGB2YCBCR) $(YCBCR2RGB)

$(RGB2YCBCR): $(COLOR_CONVERT) test/rgb2ycbcr.c
	$(CC) $(CFLAGS) -o $@ $^

$(YCBCR2RGB): $(COLOR_CONVERT) test/ycbcr2rgb.c
	$(CC) $(CFLAGS) -o $@ $^

